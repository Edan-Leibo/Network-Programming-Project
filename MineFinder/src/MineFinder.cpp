//============================================================================
// Name        : MineFinder.cpp
// Author      : Leibovitz Edan
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

using namespace std;

#include <iostream>
#include <string>
#include <cstdlib>
#include "MineFinder.h"

using namespace npl;

void MineFinder::start() {
	cout << "~~~ Welcome to Mines game ~~~" << endl;
	cout << "~~~ This game was written by Leibovitz Edan  ~~~" << endl;

	Responder responder;
	responder.setMineFinder(this);
	sdk = new SDKClient(&responder);
	while (true) {
		printInstructions();
		string msg;
		string command;
		cin >> command;
		if (command == "c") {
			string ip;
			cin >> ip;
			if (!checkContains(ip, ".")){
				cout<< "Please enter a valid IP address"<<endl;
				continue;
			}
			cout << "Trying to connect to server..." << endl;
			if (!sdk->connect(ip)){
				cout << "Connection failed..." << endl;
				serverConnection=false;
			}else{
				cout << "Connection established" << endl;
				serverConnection=true;
			}
		} else if (command == "r") {
			string usernamePassword;
			cin >> usernamePassword;
			if (!checkContains(usernamePassword, ":")){
				cout<< "Please enter a valid input, you forgot a colon. (For example- John:1234)"<<endl;
				continue;
			}
			string username = usernamePassword.substr(0,usernamePassword.find_first_of(":"));
			string password = usernamePassword.substr(usernamePassword.find_first_of(":") + 1);
			cout << "Trying to register a new username... " << endl;
			cout << "Username: " << username << endl;
			cout << "Password: " << password << endl;
			if (!sdk->registerUser(username, password))
				cout << "Illegal Action" << endl;
		} else if (command == "l") {
			string usernamePassword;
			cin >> usernamePassword;
			if (!checkContains(usernamePassword, ":")){
				cout<< "Please enter a valid input, you forgot a colon. (For example- John:1234)"<<endl;
				continue;
			}
			string username = usernamePassword.substr(0,
					usernamePassword.find_first_of(":"));
			string password = usernamePassword.substr(
					usernamePassword.find_first_of(":") + 1);
			cout << "Trying to login... " << endl;
			cout << "Username: " << username << endl;
			cout << "Password: " << password << endl;
			if (!sdk->loginUser(username, password))
				cout << "Illegal Action" << endl;
		} else if (command == "show") {
			cout << "Showing free users... " << endl;
			if (!sdk->showUsers())
				cout << "Illegal Action" << endl;
		} else if (command == "ask") {
			myPlayerChar='A';
			otherPlayerChar='B';
			cin >> remoteName;
			cout << "Asking " << remoteName<< " if she/he wants to play with you..." << endl;
			if (!sdk->askForGame(remoteName)) cout << "Action Failed" << endl;
		} else if (command == "ans") {
			string remoteName_answer;
			cin >> remoteName_answer;
			if (!checkContains(remoteName_answer, ":") || (!checkContains(remoteName_answer, "YES")&&!checkContains(remoteName_answer, "NO")) ){
				cout<< "Please enter a valid input (For example- John:YES or David:NO)"<<endl;
				continue;
			}
			remoteName = remoteName_answer.substr(0,remoteName_answer.find_first_of(":"));
			string answer = remoteName_answer.substr(remoteName_answer.find_first_of(":") + 1);
			cout << "Sending " << answer << " to " << remoteName << "... "<< endl;
			if (!sdk->AnswerRemoteOffer(remoteName, answer)) {
				cout << "Illegal Action" << endl;
				continue;
			}
			if (answer=="YES"){
				setMyturn(true);
				myPlayerChar='B';
				otherPlayerChar='A';
				cout<<"<<<<<< GAME STARTED >>>>>>"<<endl;
				randomBoard();
				displayBoard(board);
			}
		} else if (command == "hof") {
			cout << "Show HALL OF FAME..." << endl;
			if (!sdk->displayHallOfFame()) cout << "Action Failed" << endl;
		} else if (command == "try") {
			int position;
			cin >> position;
			if(cin.fail()) {
				cout << "Wrong input"<<endl;;
				cin.clear();
				continue;
			}
			if (!sdk->isActivePeer()){
				cout<< "Can't try a guess, there is no one on the other side"<<endl;
				continue;
			}
			if (!myturn || position<0 || position >=BOARD_SIZE || (board[position]!='X' && board[position]!='O')){
				cout << "Illegal Action" << endl;
				continue;
			}
			if (board[position]=='O'){
				cout<<"! ! ! Hallelujah ! ! !"<<endl;
				board[position]=myPlayerChar; //Making the move on the board
			}
			else{
				cout<<"YOU MISSED!"<<endl;
			}
			bool gameOver=isGameOver();
			if (gameOver){
				int myScore=getPlayerScore(myPlayerChar);
				sdk->endGame(myScore);
			}
			cout << "Sending "<< remoteName <<" the updated board..." << endl;
			if (!sdk->sendData(board)){
				cout << "Problem with sending the board" << endl;
			}
			setMyturn(false);
			if (gameOver){
				sdk->returnToAvailableStatus();
				displayFinalScore();
			}
		} else if (command == "d") {
			cout << "Disconnecting..." << endl;
			sdk->disconnect();
			break;
		} else {
			cout << "wrong input" << endl;
		}
	}
	cout << "Mine Finder was closed" << endl;
}

void MineFinder::displayFinalScore(){
	int myScore=getPlayerScore(myPlayerChar);
	int hisScore=getPlayerScore(otherPlayerChar);
	cout<<">>>>>> GAME ENDED <<<<<<"<<endl;
	cout<<" Your score: "<<myScore<<endl;
	cout<<" His score: "<<hisScore<<endl;

	if (myScore>hisScore){
		cout<<"YOU WIN!!"<<endl;
	}else if (myScore==hisScore){
		cout<<"IT'S A TIE!!"<<endl;
	}
	else{
		cout<<"YOU LOSE!!"<<endl;
	}
}

bool MineFinder::endGame() {
	cout << "Sending player " << myPlayerChar << " score to the server"<< endl;
	int score =getPlayerScore(myPlayerChar);
	if (!sdk->endGame(score)) cout << "Action Failed" << endl;
	return true;
}

int MineFinder::getPlayerScore(char player){
	int count=0;
	for(int i=0;i<BOARD_SIZE;++i){
		if (board[i]==player) count+=20;
	}
	return count;
}

void MineFinder::printInstructions() {
	cout << "To connect: c <server ip>" << endl;
	cout << "To register: r <username:password>" << endl;
	cout << "To login: l <username:password>" << endl;
	cout << "To show Available users: show" << endl;
	cout << "To ask for game: ask <remote name>" << endl;
	cout << "To answer remote offer: ans <remoteName:answer>" << endl;
	cout << "To display hall of fame: hof" << endl;
	cout << "To choose a position on the board: try <position>" << endl;
	cout << "To disconnect: d" << endl;
}


void MineFinder::displayBoard(char* displayBoard){
	for(int i=0;i<BOARD_SIZE;++i){
		if (displayBoard[i]=='O'){
			cout<<"[X] ";
		}
		else{
			cout<<"["<<displayBoard[i]<<"] ";
		}
	}
	cout<<endl;
}

bool MineFinder::isGameOver(){
	bool ans=true;
	for(int i=0;i<BOARD_SIZE;++i){
		if (board[i]=='O') ans=false;
	}
	return ans;
}

void MineFinder::randomBoard(){
	int count=0;
	for(int i=0;i<BOARD_SIZE;++i){
		board[i]='X';
	}

	while (count<(AMOUNT_OF_MINES)){
		int r = rand()%BOARD_SIZE;
		if (board[r]=='O') continue;
		board[r]='O';
		count++;
	}
}

void MineFinder::makeMeAvailable(){
	if (sdk->returnToAvailableStatus()){
		cout << "Other user disconnected :-<" << endl;
		cout << "Making you available for game once again.."<<endl;
	}
}

void MineFinder::updateBoard(char* newBoard){
	for(int i=0;i<BOARD_SIZE;++i){
		board[i]=newBoard[i];
	}
}

bool MineFinder::checkContains(const string& s1, const string& s2){
	if (s1.find(s2) != std::string::npos) {
		return true;
	}
	return false;
}

bool MineFinder::isMyturn() const {
	return myturn;
}

void MineFinder::setMyturn(bool myturn) {
	this->myturn = myturn;
}

bool MineFinder::getServerConnection() const {
	return serverConnection;
}

void MineFinder::setServerConnection(bool serverConnection) {
	this->serverConnection = serverConnection;
}

/////////////////////////////////////////////////////////////////////////////
//////////		ClientHandler 		implementation		/////////////////////
/////////////////////////////////////////////////////////////////////////////

void Responder::onRegisterResponse(string result) {
	cout<<"*Server Replies*"<<endl;
	cout << "Registration status: " << result << endl;
}

void Responder::onLoginResponse(string result) {
	cout<<"*Server Replies*"<<endl;
	cout << "Login status: "<< result << endl;
}

void Responder::onShowUsersResponse(vector<string> users) {
	cout<<"*Server Replies*"<<endl;
	cout << "---ONLINE USERS--- " << endl;
	printVector(users);
}

void Responder::onAskForGameResponse(string answer) {
	cout<<"*Server Replies*"<<endl;
	cout << "Answer for your request: ";

	if (answer=="success"){
		cout<< "PEER AGREED" << endl;
		mineFinder->setMyturn(false);
		cout<<"<<<<<< GAME STARTED >>>>>>"<<endl;
		cout<<"Waiting for other player to make the first move"<<endl;
	}
	else{
		cout<<"DENIED"<<endl;
	}
}

void Responder::onDisplayHallOfFameResponse(vector<string> hallOfFame) {
	cout<<"*Server Replies*"<<endl;
	cout << "---HALL OF FAME--- " << endl;
	printVector(hallOfFame);
}

void Responder::onRemoteOffer(string name) {
	cout<<"*Server Update*"<<endl;
	cout << "You got a remote offer from " << name << endl;
}

void Responder::onServerClosed() {
	if (mineFinder->getServerConnection()){
		cout<< "Connection with server was closed"<<endl;
	}
	mineFinder->setServerConnection(false);
}

void Responder::onDataReceived(char* data) {
	mineFinder->setMyturn(true);
	cout<<"*Peer Message*"<<endl;
	cout << "Other player has made a move: " <<endl;
	mineFinder->updateBoard(data);
	mineFinder->displayBoard(data);
	if (mineFinder->isGameOver()){
		mineFinder->endGame();
		mineFinder->displayFinalScore();
		mineFinder->makeMeAvailable();
	}
}

void Responder::onEmptyResponse() {
	cout<<"*Server Replies*"<<endl;
	cout << "(-: Empty list :-)" << endl;
}

void Responder::onGameCanceled() {
	cout << "Game with remote peer was canceled" << endl;
}

void Responder::setMineFinder(MineFinder* mineFinder) {
	this->mineFinder = mineFinder;
}
void Responder::printVector(vector<string> svect) {
	for (unsigned int i = 0; i < svect.size(); ++i) {
		cout << svect[i] << endl;
	}
}
