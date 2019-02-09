/*
 * RequestManager.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: user
 */

#include "RequestManager.h"
#include <cstdlib>
#include <sstream>
#include "SDKProtocol.h"
#include "Guard.h"
#include "FileManager.h"

using namespace std;

namespace npl {

RequestManager::RequestManager(FileManager* fileManager) {
	this->fileManager = fileManager;
	flag = false;
	usersMutex= PTHREAD_MUTEX_INITIALIZER;
	unidentifiedUsersMutex= PTHREAD_MUTEX_INITIALIZER;
}

void RequestManager::run() {
	cout << "> Requests manager started" << endl;
	flag=true;
	while (flag) {
		MultipleTCPSocketsListener msp;

		vector<TCPSocket*> allSockets =getAllSocketsFromUsers();
		{
			Guard unidentifiedGuard(&unidentifiedUsersMutex);
			allSockets.insert(allSockets.end(),unidentifiedUsers.begin(),unidentifiedUsers.end());
		}
		msp.addSockets(allSockets);
		TCPSocket* readyPeer = msp.listenToSocket(2);
		if (flag == false) {
			break;
		}
		if (readyPeer == NULL) continue;

		string data;
		int command = this->readCommandFromPeer(readyPeer);
		switch (command) {
		case (REGISTER):
			registerUserReq(readyPeer);
			break;
		case (LOGIN):
			loginUserReq(readyPeer);
			break;
		case (SHOW_USERS):
			showUsersReq(readyPeer);
			break;
		case (ASK_FOR_GAME):
			askForGameReq(readyPeer);
			break;
		case (ANSWER_REMOTE_OFFER):
			AnswerRemoteOfferReq(readyPeer);
			break;
		case (DISPLAY_HALL_OF_FAME):
			displayHallOfFameReq(readyPeer);
			break;
		case (END_GAME):
			endGameReq(readyPeer);
			break;
		case (MAKE_ME_AVAILABLE_AGAIN):
			makeMeAvailable(readyPeer);
			break;
		case (CLOSE_MY_CLIENT):
			closeMyClientReq(readyPeer);
			break;

		default:
			cout << "Client disconnected ungracefully" << endl;
			closeMyClientReq(readyPeer);
		}
	}
	cout << "> Requests manager ended" << endl;
}

string RequestManager::readDataFromPeer(TCPSocket * peer) {
	string msg;
	char buff[1500];
	int msgLen;
	peer->read((char*) &msgLen, 4);
	msgLen = ntohl(msgLen);
	int totalrc = 0;
	int rc;
	while (totalrc < msgLen) {
		rc = peer->read((char*) &buff[totalrc], msgLen - totalrc);
		if (rc > 0) {
			totalrc += rc;
		} else {
			break;
		}
	}
	if (rc > 0 && totalrc == msgLen) {
		buff[msgLen] = 0;
		msg = buff;
	} else {
		peer->close();
	}
	return msg;
}

int RequestManager::readCommandFromPeer(TCPSocket* peer) {
	int command = 0;
	int rt = peer->read((char*) &command, 4);
	if (rt < 1)
		return rt;
	command = ntohl(command);
	return command;
}

void RequestManager::sendCommandToPeer(TCPSocket* peer, int command) {
	command = htonl(command);
	peer->write((char*) &command, 4);
}

void RequestManager::sendDataToPeer(TCPSocket* peer, string msg) {
	int msgLen = msg.length();
	msgLen = htonl(msgLen);
	peer->write((char*) &msgLen, sizeof(int));
	peer->write(msg.data(), msg.length());
}

vector<string> RequestManager::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

//This part handles the different requests
void RequestManager::registerUserReq(TCPSocket* readyPeer) {	//thread safe
	cout<<"> Got a registration request from: "<<readyPeer->fromAddrPort()<<endl;;
	vector<string> afterSplit;

	string data = readDataFromPeer(readyPeer);
	afterSplit = split(data, ':');
	bool result = false;
	result = fileManager->tryToAdd(afterSplit[0], afterSplit[1]);

	sendCommandToPeer(readyPeer, REGISTER_RESPONSE);
	if (result == true)
		sendDataToPeer(readyPeer, "success");
	else
		sendDataToPeer(readyPeer, "fail");

}

void RequestManager::loginUserReq(TCPSocket* readyPeer) {	//thread safe
	cout<<"> Got a login request from: "<<readyPeer->fromAddrPort()<<endl;
	vector<string> afterSplit;
	bool result = false;

	string data = readDataFromPeer(readyPeer);
	sendCommandToPeer(readyPeer, LOGIN_RESPONSE);
	afterSplit = split(data, ':');
	if (isExistsInUsers(afterSplit[0])){
		sendDataToPeer(readyPeer, "fail");
		return;
	}
	result = fileManager->tryToLogin(afterSplit[0], afterSplit[1]);
	if (result == true) {
		takeOutPeerFromUnidentified(readyPeer);
		{
			Guard guard(&usersMutex);
			users.push_back(new User(afterSplit[0], afterSplit[1], readyPeer));
		}
		sendDataToPeer(readyPeer, "success");
	} else {
		sendDataToPeer(readyPeer, "fail");
	}

}

void RequestManager::showUsersReq(TCPSocket* readyPeer) {	//thread safe
	cout<<"> Got a show users request from: "<<readyPeer->fromAddrPort()<<endl;
	string ans = "";
	Guard* guard= new Guard(&usersMutex);

	for (std::vector<User*>::iterator iter = users.begin(); iter != users.end(); ++iter) {
		if ((*iter)->getIsPlaying()==true) continue;
		ans = ans + ":" + (*iter)->getName();
	}
	delete guard;
	if (ans==""){
		sendCommandToPeer(readyPeer, EMPTY);
	}
	else{
		sendCommandToPeer(readyPeer, SHOW_USERS_RESPONSE);
		ans.erase(ans.begin());	// deletes the :
		sendDataToPeer(readyPeer, ans);
	}
}

void RequestManager::askForGameReq(TCPSocket* readyPeer) {	//thread safe
	cout<<"> Got a ask for game request from: "<<readyPeer->fromAddrPort()<<endl;
	string readyPeerName = TCP2Name(readyPeer);
	string peerToPlayName = readDataFromPeer(readyPeer);
	//if peerToPlayName is "random" the find will give us a random peer
	TCPSocket* peerToPlaySocket = findFromUsers(peerToPlayName, readyPeerName);
	if (peerToPlaySocket==NULL) {
		//Peer is not in Users list OR There are no other peers
		sendCommandToPeer(readyPeer, ASK_FOR_GAME_RESPONSE);
		sendDataToPeer(readyPeer, "fail");
	}
	else{
		sendCommandToPeer(peerToPlaySocket, REMOTE_OFFER);
		sendDataToPeer(peerToPlaySocket, readyPeerName+":"+readyPeer->fromAddrPort());
	}
}

void RequestManager::AnswerRemoteOfferReq(TCPSocket* readyPeer) {	//thread safe
	cout<<"> Got an answer remote offer request from: "<<readyPeer->fromAddrPort()<<endl;

	string data = readDataFromPeer(readyPeer);
	vector<string> afterSplit = split(data, ':');
	string askingPeerName=afterSplit[0];

	TCPSocket* askingPeerSocket=findFromUsers(askingPeerName, "");

	//In case the asking user started a game don't bother him
	//Game will be started at the asked side, and no response to his moves will be given
	if (isUserPlaying(askingPeerName) || (askingPeerSocket==NULL)){
		if (afterSplit[1]=="YES") updateIsUserPlaying(readyPeer, true);
		return;
	}

	sendCommandToPeer(askingPeerSocket, ASK_FOR_GAME_RESPONSE);
	if (afterSplit[1]=="NO"){
		sendDataToPeer(askingPeerSocket, "fail");
	}
	else if (afterSplit[1]=="YES"){
		updateIsUserPlaying(askingPeerSocket, true);
		updateIsUserPlaying(readyPeer, true);
		sendDataToPeer(askingPeerSocket, "success:"+readyPeer->fromAddrPort());
	}
}

void RequestManager::displayHallOfFameReq(TCPSocket* readyPeer) { //thread safe
	cout<<"> Got a display Hall Of Fame request from: "<<readyPeer->fromAddrPort()<<endl;

	string hof=fileManager->getHallOfFame();
	if (hof==""){
		sendCommandToPeer(readyPeer, EMPTY);
		return;
	}
	sendCommandToPeer(readyPeer,DISPLAY_HALL_OF_FAME_RESPONSE);
	sendDataToPeer(readyPeer, hof);
}

void RequestManager::makeMeAvailable(TCPSocket* readyPeer){
	cout<<"> Got a make me available request from: "<<readyPeer->fromAddrPort()<<endl;
	updateIsUserPlaying(readyPeer, false);
}

void RequestManager::closeMyClientReq(TCPSocket* readyPeer) {	//thread safe
	cout<<"> Closing the client: "<<readyPeer->fromAddrPort()<<endl;

	readyPeer->close();
	removePeerFromUsers(readyPeer);
	removePeerFromUnidentified(readyPeer);
}

void RequestManager::endGameReq(TCPSocket* readyPeer) {		//thread safe
	cout<<"> Got an end game request from: "<<readyPeer->fromAddrPort()<<endl;
	string data=readDataFromPeer(readyPeer);
	int score=atoi(data.c_str());
	fileManager->updateScore(TCP2Name(readyPeer), score);
	//updateIsUserPlaying(readyPeer, false);
}

string RequestManager::TCP2Name(TCPSocket* tcpSocket) {	 	//thread safe
Guard guard(&usersMutex);
for (std::vector<User*>::iterator iter = users.begin(); iter != users.end();++iter) {
	if ((*iter)->getTcpSocket() == tcpSocket) {
		return (*iter)->getName();
	}
}
return "";
}

bool RequestManager::isExistsInUsers(string name) {		//thread safe
Guard guard(&usersMutex);
for (std::vector<User*>::iterator iter = users.begin(); iter != users.end(); ++iter) {
	if (((*iter)->getName() == name) ) {
		return true;
	}
}
return false;
}

TCPSocket* RequestManager::findFromUsers(string name, string readyPeerName) {		//thread safe
Guard guard(&usersMutex);
if (name == "random") {
	for (std::vector<User*>::iterator iter = users.begin(); iter != users.end();++iter) {
		if (((*iter)->getName() != readyPeerName) && ((*iter)->getIsPlaying()==false)){
			return (*iter)->getTcpSocket();
		}
	}
	return NULL;
}

for (std::vector<User*>::iterator iter = users.begin(); iter != users.end(); ++iter) {
	if (((*iter)->getName() == name) && ((*iter)->getIsPlaying()==false)) {
		return (*iter)->getTcpSocket();
	}
}
return NULL;
}

void RequestManager::updateIsUserPlaying(TCPSocket* peerToUpdate, bool status){		//thread safe
	Guard guard(&usersMutex);
	for (std::vector<User*>::iterator iter = users.begin(); iter != users.end();++iter) {
		if ((*iter)->getTcpSocket() == peerToUpdate) {
			(*iter)->setIsPlaying(status);
			break;
		}
	}
}

void RequestManager::removePeerFromUnidentified(TCPSocket* unidentifiedToRemove) {
	Guard guard(&unidentifiedUsersMutex);
	for (std::vector<TCPSocket*>::iterator iter = unidentifiedUsers.begin();iter != unidentifiedUsers.end(); ++iter) {
	if (*iter == unidentifiedToRemove) {
		delete (*iter);
		unidentifiedUsers.erase(iter);
		break;
	}
}
}

void RequestManager::takeOutPeerFromUnidentified(TCPSocket* unidentifiedToTakeOut) {
	Guard guard(&unidentifiedUsersMutex);
	for (std::vector<TCPSocket*>::iterator iter = unidentifiedUsers.begin();iter != unidentifiedUsers.end(); ++iter) {
	if (*iter == unidentifiedToTakeOut) {
		unidentifiedUsers.erase(iter);
		break;
	}
}
}

void RequestManager::removePeerFromUsers(TCPSocket* socket) {		//thread safe
Guard guard(&usersMutex);
for (std::vector<User*>::iterator iter = users.begin(); iter != users.end();++iter) {
	if ((*iter)->getTcpSocket()== socket) {
		delete (*iter);
		users.erase(iter);
		break;
	}
}
}

vector<TCPSocket*> RequestManager::getAllSocketsFromUsers() {			//thread safe
	Guard guard(&usersMutex);
	vector<TCPSocket*> ans;
	for (std::vector<User*>::iterator iter = users.begin(); iter != users.end();++iter) {
		ans.push_back(((*iter)->getTcpSocket()));
	}
	return ans;
}

void RequestManager::close(){			//thread safe
	flag=false;
	waitForThread();
	Guard* guard=new Guard(&unidentifiedUsersMutex);
	for (std::vector<TCPSocket*>::iterator iter = unidentifiedUsers.begin(); iter != unidentifiedUsers.end();++iter) {
		sendCommandToPeer((*iter), SERVER_CLOSED);
		(*iter)->close();
		delete (*iter);
	}
	delete guard;
	Guard guard2(&usersMutex);
	for (std::vector<User*>::iterator iter = users.begin(); iter != users.end(); ++iter) {
		TCPSocket* socket= (*iter)->getTcpSocket();
		sendCommandToPeer(socket, SERVER_CLOSED);
		socket->close();
		delete (*iter);
	}
}

void RequestManager::handlePeer(TCPSocket* peer){
	Guard guard(&unidentifiedUsersMutex);
	unidentifiedUsers.push_back(peer);
}

bool RequestManager::isUserPlaying(string nameToCheck) {
	Guard guard(&usersMutex);
	for (std::vector<User*>::iterator iter = users.begin(); iter != users.end();++iter) {
		if ((*iter)->getName() == nameToCheck){
			return ((*iter)->getIsPlaying());
		}
	}
	return false;
}

RequestManager::~RequestManager() {
}
} /* namespace npl */

