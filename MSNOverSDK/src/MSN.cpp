//============================================================================
// Name        : Mines.cpp
// Author      : Leibovitz Edan
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================


using namespace std;



#include <iostream>
#include <string>
#include <cstdlib>
#include "SDKClientHandler.h"
#include "SDKClient.h"


using namespace std;
using namespace npl;

/*********************************************************************/
 /* This .cpp file contains a MAUNAL test for the SDK
 * The APK in this case is simply a messenger application
 * Here you can test the functionality of transferring text data
 * YOU MUST RUN A SERVER SEPERATLY BEFORE YOU START THIS TEST
 */
/*********************************************************************/


class ClientHandler:public SDKClientHandler{
public:
	//Responses to requests
	virtual void onRegisterResponse(string result);
	virtual void onLoginResponse(string result);
	virtual void onShowUsersResponse(vector<string> users);
	virtual void onAskForGameResponse(string answer);
	virtual void onDisplayHallOfFameResponse(vector<string> hallOfFame);
	virtual void onEmptyResponse();

	//Asynchronized notifications from server
	virtual void onRemoteOffer(string name);
	virtual void onServerClosed();

	//Data from other player
	virtual void onDataReceived(char* data);
	/*
	 * Other user disconnected
	 */
	virtual void onGameCanceled();

	virtual ~ClientHandler(){};
};



void printInstructions(){
	cout<<"To connect: c <server ip>"<<endl;
	cout<<"To register: r <username:password>"<<endl;
	cout<<"To login: l <username:password>"<<endl;
	cout<<"To show users: show"<<endl;
	cout<<"To ask for game: ask <remote name>"<<endl;
	cout<<"To answer remote offer: ans <remoteName:answer>"<<endl;
	cout<<"To set score: set <score>"<<endl;
	cout<<"To display hall of fame: hof"<<endl;
	cout<<"To send message to remote user: s <message>"<<endl;
	cout<<"To disconnect: d"<<endl;
}

void printVector(vector<string> svect){
	for(unsigned int i = 0; i < svect.size(); ++i ){
	    cout << svect[i] <<endl;
	}
}

int main(){
	cout<<"Welcome to MSNOverSDK Manual Test"<<endl;
	printInstructions();
	ClientHandler* handler=new ClientHandler();
	SDKClient* sdk= new SDKClient(handler);
	while(true){
		string msg;
		string command;
		cin >> command;
		if(command == "c"){
			string ip;
			cin >> ip;
			cout<<"connecting to server..."<<endl;
			if (!sdk->connect(ip)) cout<<"Connection failed..."<<endl;
			else cout<<"Connection established..."<<endl;
		}else if(command == "r"){
			string usernamePassword;
			cin >> usernamePassword;
			string username = usernamePassword.substr(0,usernamePassword.find_first_of(":"));
			string password = usernamePassword.substr(usernamePassword.find_first_of(":") + 1);
			cout<<"Trying to register an new username... "<<endl;
			cout<<"Username: "<<username<<endl;
			cout<<"Password: "<<password<<endl;
			if (!sdk->registerUser(username, password))	cout<<"Illegal Action"<<endl;
		}else if(command == "l"){
			string usernamePassword;
			cin >> usernamePassword;
			string username = usernamePassword.substr(0,usernamePassword.find_first_of(":"));
			string password = usernamePassword.substr(usernamePassword.find_first_of(":") + 1);
			cout<<"Trying to login... "<<endl;
			cout<<"Username: "<<username<<endl;
			cout<<"Password: "<<password<<endl;
			if (!sdk->loginUser(username, password))	cout<<"Illegal Action"<<endl;
		}else if(command == "show"){
			cout<<"Showing free users... "<<endl;
			if (!sdk->showUsers()) cout<<"Action Failed"<<endl;
		}else if(command == "ask"){
			string wantToPlayWithHim;
			cin >> wantToPlayWithHim;
			cout<<"Asking "<< wantToPlayWithHim<<" if she/he wants to play with you..."<<endl;
			if (!sdk->askForGame(wantToPlayWithHim)) cout<<"Action Failed"<<endl;
		}else if(command == "ans"){
			string remoteName_answer;
			cin >> remoteName_answer;
			string remoteName = remoteName_answer.substr(0,remoteName_answer.find_first_of(":"));
			string answer = remoteName_answer.substr(remoteName_answer.find_first_of(":") + 1);
		    cout<<"Sending "<<answer<<" to "<<remoteName<<"... "<<endl;
			if (!sdk->AnswerRemoteOffer(remoteName, answer)) cout<<"Illegal Action"<<endl;
		}else if(command == "set"){
			cout<<"Setting score"<<endl;
			string score;
			cin >> score;
			int intScore=atoi(score.c_str());
			if (!sdk->endGame(intScore)) cout<<"Action Failed"<<endl;
		}else if(command == "hof"){
			cout<<"Show HALL OF FAME..."<<endl;
			if (!sdk->displayHallOfFame()) cout<<"Action Failed"<<endl;
		}else if(command == "s"){
			string data;
			cin >> data;
			cout<<"Sending data... "<<endl;
			if (!sdk->sendData(data.c_str())) cout<<"Illegal Action"<<endl;
		}else if(command == "d"){
			cout<<"Closing and disconnecting..."<<endl;
			sdk->disconnect();
			break;
		}else{
			cout<<"wrong input"<<endl;
			printInstructions();
		}
	}
	cout<<"Mines was closed"<<endl;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//////////		ClientHandler 		implementation		/////////////////////
/////////////////////////////////////////////////////////////////////////////

void ClientHandler::onRegisterResponse(string result){
	cout<<"onRegisterResponse "<<result<<endl;
}

void ClientHandler::onLoginResponse(string result){
	cout<<"onLoginResponse "<<result<<endl;
}

void ClientHandler::onShowUsersResponse(vector<string> users){
	cout<<"onShowUsersResponse "<<endl;
	if (users[0]=="NONE"){
		cout<<"No free users"<<cout;
	}
	else{
		printVector(users);
	}
}

void ClientHandler::onAskForGameResponse(string answer){
	cout<<"onAskForGameResponse "<<answer<<endl;
}

void ClientHandler::onDisplayHallOfFameResponse(vector<string> hallOfFame){
	cout<<"onDisplayHallOfFameResponse "<<endl;
	printVector(hallOfFame);
}

void ClientHandler::onRemoteOffer(string name){
	cout<<"onRemoteOffer "<<name<<endl;
}

void ClientHandler::onServerClosed(){
	cout<<"onServerClosed "<<endl;
}

void ClientHandler::onDataReceived(char* data){
	cout<<"onDataReceived "<<string(data)<<endl;
}

void ClientHandler::onEmptyResponse(){
	cout<<"Nothing to show"<<endl;
}

void ClientHandler::onGameCanceled(){
	cout<<"Other user disconnected"<<endl;
}

