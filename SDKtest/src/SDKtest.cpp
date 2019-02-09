//============================================================================
// Name        : SDKtest.cpp
// Author      : Leibovitz Edan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

using namespace std;

#include <iostream>
#include <string>
#include "SDKClient.h"
#include "FileManager.h"
#include "RequestManager.h"
#include "Server.h"
#include "ClientHandler.h"
#include "RegisterTest.h"
#include "SDKProtocol.h"
#include "LoginTest.h"
#include "ShowUsersTest.h"
#include "HallOfFameTest.h"
#include "DataTransferTest.h"
using namespace npl;

int main() {
	cout << "== Welcome to SDK Automatic Test ==" << endl;

	//---------SET UP---------

	//Building the server
	FileManager* fileManager = new FileManager();
	RequestManager* requestManager = new RequestManager(fileManager);
	Server* server = new Server(requestManager);
	requestManager->start();
	server->start();
	//Server is running at this point

	sleep(2);
	//Connecting client 1
	ClientHandler* handler = new ClientHandler();
	SDKClient* sdk1 = new SDKClient(handler);
	cout << "Connecting user 1 to server" << endl;
	if (!sdk1->connect("127.0.0.1")) {
		cout << "Connection of user 1 to server: FAIL" << endl;
	} else {
		cout << "Connection of user 1 to server: SUCCESS" << endl;
	}

	//-------TESTING----------
	//Register Test
	RegisterTest registerTest(sdk1);
	registerTest.test();

	//Login Test
	LoginTest loginTest(sdk1);
	loginTest.test();

	//ShowUsers Test
	ShowUsersTest showUsersTest(sdk1);
	showUsersTest.test();

	//HallOfFame Test
	HallOfFameTest hallOfFameTest(sdk1);
	hallOfFameTest.test();



	//Connecting the second client
	SDKClient* sdk2 = new SDKClient(handler);
	cout << "Connecting 2 to server" << endl;
	if (!sdk2->connect("127.0.0.1")) {
		cout << "Connection of user 2 to server: FAIL" << endl;
	} else {
		cout << "Connection of user 2 to server: SUCCESS" << endl;
	}
	//DataTransfer Test
	DataTransferTest dataTransferTest(sdk1,sdk2);
	dataTransferTest.test();


	//---------TEAR DOWN---------

	//Deleting created files
	sleep(2);
	if (remove(PASSWORDS_PATH) != 0)
		cout << "Deleting Password file: FAIL" << endl;
	else
		cout << "Deleting Password file: SUCCESS" << endl;
	if (remove(HALL_OF_FAME_PATH) != 0)
		cout << "Deleting Hall Of fame file: FAIL" << endl;
	else
		cout << "Deleting Hall Of fame file: SUCCESS" << endl;


	sdk1->disconnect();
	sdk2->disconnect();
	delete handler;
	delete sdk1;
	delete sdk2;

	//Closing the server
	server->close();
	requestManager->close();
	delete fileManager;
	delete requestManager;
	delete server;
	cout << "===== TEST IS DONE =====" << endl;
	return 0;
}

