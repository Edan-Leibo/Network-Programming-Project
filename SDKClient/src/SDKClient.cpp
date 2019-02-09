/*
 * SDKClient.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: user
 */

#include "SDKClient.h"
#include "SDKProtocol.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>



namespace npl {

SDKClient::SDKClient(SDKClientHandler* handler){
	remotePeerIP = "";
	remotePeerPort = -1;
	this->handler = handler;
	tcpSocket = NULL;
	udpConnector = NULL;
	activeServer = false;
	activePeer = false;
	loggedIn=false;
	myUsername="NoName";
	lastOneOffered=NULL;
}

bool SDKClient::connect(string ip) {
	if (activeServer){
		disconnect();
	}
	//creating TCP connection to server
	tcpSocket = new TCPSocket(ip, SERVER_PORT);
	if (tcpSocket == NULL || !tcpSocket->isConnected())
		return false;
	start();
	activeServer = true;
	//creating an unconnected UDP connection
	activePeer=false;
	udpConnector=new UDPConnector(tcpSocket->getPort(),handler,this);

	udpConnector->start();
	return true;
}

bool SDKClient::registerUser(string username, string password)  {
	if (!isActiveServer() || containsSpaces(username)|| containsSpaces(password)||username=="random"){
		return false;
	}
	char buff[100];
	sprintf(buff, "%s:%s", username.c_str(), password.c_str());
	return sendCommand(REGISTER, buff) > -1;
}

bool SDKClient::loginUser(string username, string password) {
	if (loggedIn || !isActiveServer() || containsSpaces(username)|| containsSpaces(password)||username=="random")
		return false;
	myUsername=username;
	char buff[100];
	sprintf(buff, "%s:%s", username.c_str(), password.c_str());
	return sendCommand(LOGIN, buff) > -1;
}

bool SDKClient::showUsers()  {
	if (!activeServer || !loggedIn) return false;
	return sendCommand(SHOW_USERS, NULL)>-1;
}

bool SDKClient::askForGame(string name) {
	if (!isActiveServer() || isActivePeer() || myUsername==name || !loggedIn ) return false;
	return (sendCommand(ASK_FOR_GAME, name.c_str()) > -1);

}

bool SDKClient::AnswerRemoteOffer(string remoteName, string answer) {
	//You can only answer the last one asked
	if ((!isActiveServer()) ||(lastOneOffered==NULL)|| (lastOneOffered!=NULL && remoteName!= *lastOneOffered) || isActivePeer() || ((answer != "YES") && (answer != "NO")) || (!loggedIn))
		return false;
	if (answer == "YES") {
		if (lastOneOffered!=NULL) delete lastOneOffered;
		lastOneOffered=NULL;
		activePeer=true;
	}
	else activePeer=false;
	return sendCommand(ANSWER_REMOTE_OFFER, (remoteName+":"+answer).c_str()) > -1;
}

bool SDKClient::endGame(int score) {
	if (!isActiveServer()|| !loggedIn) return false;
	//activePeer=false;
	char* buff=new char[100];
	sprintf(buff,"%d",score);
	bool res= sendCommand(END_GAME,buff) > -1;
	delete buff;
	return res;
}

bool SDKClient::displayHallOfFame() {
	if (!isActiveServer() || !loggedIn) return false;
	return sendCommand(DISPLAY_HALL_OF_FAME, NULL) > -1;
}

bool SDKClient::sendData(const char* data) {
	if (!loggedIn || !activePeer) return false;
	return udpConnector->sendData(data);
}

void SDKClient::disconnect() {
	if (isActivePeer() && isActiveServer()){
		sendData("Quit");
	}
	if (udpConnector != NULL) {
		udpConnector->close();
		udpConnector->waitForThread();
		delete udpConnector;
		udpConnector = NULL;
	}
	activePeer=false;
	loggedIn=false;
	if (isActiveServer())
		sendCommand(CLOSE_MY_CLIENT, NULL);
	if (tcpSocket != NULL) {
		tcpSocket->close();
		this->waitForThread();
		delete tcpSocket;
		tcpSocket = NULL;
	}
	activeServer=false;
}


void SDKClient::run() {
	while (recvCommand());
	activeServer=false;
	disconnect();
	handler->onServerClosed();
}

bool SDKClient::isActiveServer() const{
	return activeServer;
}

bool SDKClient::isActivePeer() const {
	return activePeer;
}

/******************
 * PRIVATE METHODS
 *****************/

int SDKClient::sendCommand(int cmd, const char* buff) {
	if (!isActiveServer())
		return -1;
	int cmdNet = htonl(cmd);
	if (tcpSocket==NULL) return -1;
	int res = tcpSocket->write((char*) &cmdNet, 4);
	if (res < 4) {
		return -1;
	}
	if (buff != NULL) {
		int len = strlen(buff) + 1;
		int cmdNet = htonl(len);
		res = tcpSocket->write((char*) &cmdNet, 4);
		if (res < 4) {
			return -1;
		}
		res = tcpSocket->write(buff, len);
		if (res < len) {
			return -1;
		}
	}
	return res;
}

struct Comparator {
	vector<string> split(string str, char delimiter) {
		vector<string> internal;
		stringstream ss(str);
		string tok;

		while (getline(ss, tok, delimiter)) {
			internal.push_back(tok);
		}
		return internal;
	}
	bool operator()(string s1, string s2) {
		int score1= atoi((split(s1, ' ')[1]).data());
		int score2= atoi((split(s2, ' ')[1]).data());
		return (score1 > score2);
	}
};

bool SDKClient::recvCommand() {
	int cmd;
	int rc = tcpSocket->read((char*) &cmd, 4);
	if (rc <= 0)
		return false;
	int cmdNet = ntohl(cmd);
	string message;
	vector<string> afterSplit;
	vector<string> spiltMessage;
	switch (cmdNet) {
	case (REGISTER_RESPONSE):						//DATA: "fail"\"success"
		message=readMessageFromServer();
		handler->onRegisterResponse(message);
		break;
	case (LOGIN_RESPONSE):							//DATA: "fail"\"success"
		message=readMessageFromServer();
		if (message=="success"){
			loggedIn=true;
		}
		else{
			loggedIn=false;
		}
		handler->onLoginResponse(message);
		break;
	case (SHOW_USERS_RESPONSE):						//DATA: [player1]: ... :[playerN]
		message=readMessageFromServer();
		spiltMessage= split(message, ':');
		handler->onShowUsersResponse(spiltMessage);
		break;
	case (ASK_FOR_GAME_RESPONSE):					//DATA: "fail"\"success":[remote_user_UDP_IP]:[remote_user_UDP_PORT]
		message=readMessageFromServer();
		if (message=="fail") {
			activePeer=false;
			handler->onAskForGameResponse(message);
		}
		else {
			activePeer=true;
			spiltMessage= split(message, ':');
			remotePeerIP= spiltMessage[1];
			remotePeerPort= atoi(spiltMessage[2].c_str());
			udpConnector->connect(remotePeerIP, remotePeerPort);
			handler->onAskForGameResponse("success");
		}
		break;
	case (REMOTE_OFFER):							//DATA: [remote_name]:[remote_user_UDP_IP]:[remote_user_UDP_PORT]
		message=readMessageFromServer();
		spiltMessage= split(message, ':');
		lastOneOffered=new string(spiltMessage[0]);			//remember the last one asked, he is the only one I can answer to
		handler->onRemoteOffer(spiltMessage[0]);
		remotePeerIP= spiltMessage[1];			//remember the last one IP and PORT
		remotePeerPort= atoi(spiltMessage[2].c_str());
		udpConnector->connect(remotePeerIP, remotePeerPort);
		break;
	case (DISPLAY_HALL_OF_FAME_RESPONSE):			//DATA: [player1] [score1]: ... :[playerN] [scoreN]
		message=readMessageFromServer();
		spiltMessage= split(message, ':');
		std::sort (spiltMessage.begin(), spiltMessage.end(), Comparator());
		handler->onDisplayHallOfFameResponse(spiltMessage);
		break;
	case(EMPTY):
		handler->onEmptyResponse();
		break;
	case (SERVER_CLOSED):							//NO DATA
		loggedIn=false;
		activePeer=false;
		activeServer=false;
		handler->onServerClosed();
		break;
	}
	return true;
}




string SDKClient::readMessageFromServer() {
	char* msg = NULL;
	int sizeNet = 0;
	int sizeOfmessage = 0;
	int rc = tcpSocket->read((char*) &sizeOfmessage, sizeof(int));
	sizeNet = ntohl(sizeOfmessage);
	if (rc <= 0)
		return "";
	msg = new char[sizeNet+1];
	memset(msg, 0, sizeNet+1);
	for (int i = 0; i < sizeNet; i++) {
		rc = tcpSocket->read(&msg[i], sizeof(char));
		if (rc <= 0) {
			delete msg;
			return "";
		}
	}
	string ans(msg);
	delete msg;
	return ans;
}

vector<string> SDKClient::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

bool SDKClient::containsSpaces(const string& str){
	  for (unsigned int i=0; i<str.length(); ++i){
	    if ((str[i]==' ')||(str[i]=='\t')) return true;
	  }
	  return false;
}


bool SDKClient::returnToAvailableStatus(){
	activePeer=false;
	if (!isActiveServer()||tcpSocket==NULL) return false;
	return sendCommand(MAKE_ME_AVAILABLE_AGAIN, NULL)>0;
}

SDKClient::~SDKClient(){
	if (lastOneOffered!=NULL) delete lastOneOffered;
	lastOneOffered=NULL;
}

} /* namespace npl */

