/*
 * ClientHandler.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: user
 */
/////////////////////////////////////////////////////////////////////////////
//////////		ClientHandler 		implementation		/////////////////////
/////////////////////////////////////////////////////////////////////////////
#include "ClientHandler.h"
using namespace npl;

void ClientHandler::onRegisterResponse(string result) {
	cout<<"Response from server to Registration request: ";

	if (result=="success"){
		//trying to register an existing user should fail!
		cout<<"SUCCCESS"<<endl;
		return;
	}
	cout<<"FAIL"<<endl;
}

void ClientHandler::onLoginResponse(string result) {
	cout<<"Response from server to Login request: ";
	if (result=="success"){
		//trying to register an existing user should fail!
		cout<<"SUCCCESS"<<endl;
		return;
	}
	cout<<"FAIL"<<endl;
}

void ClientHandler::onShowUsersResponse(vector<string> users) {
	cout<<"Response from server to show users ACCEPTED"<<endl;

	if (users[0]!="reut"){
		cout<<"Verifying that user is on available users list: FAIL"<<endl;
		return;
	}
	cout<<"Verifying that user is on available users list: SUCCESS"<<endl;
}

void ClientHandler::onAskForGameResponse(string answer) {
	cout<<"Response from server for Ask For Game ACCEPTED"<<endl;
}

void ClientHandler::onDisplayHallOfFameResponse(vector<string> hallOfFame) {
	cout << "Response from server to Login ACCEPTED" << endl;
	if (hallOfFame[0] == "reut 2000") {
		cout<< "Verifying that user has correct information in the Hall Of Fame file: SUCCESS"<< endl;
	} else {
		cout<< "Verifying that user has correct information in the Hall Of Fame file: FAIL"<< endl;
	}
}

void ClientHandler::onRemoteOffer(string name) {
	cout << "Remote offer ACCEPTED " << endl;
}

void ClientHandler::onServerClosed() {
	cout << "Server was closed " << endl;
}

void ClientHandler::onDataReceived(char* data) {
	if (string(data)!="TEST"){
		cout<<"Verifying that the data that was received is the same: FAIL"<<endl;
		return;
	}
	cout<<"Verifying that the data that was received is the same: SUCCESS"<<endl;

}

void ClientHandler::onEmptyResponse() {
	cout << "Got unexpected empty list: FAIL "  << endl;
}

void ClientHandler::onGameCanceled() {
}
