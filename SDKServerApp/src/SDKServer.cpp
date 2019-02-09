//============================================================================
// Name        : SDKServer.cpp
// Author      : Leibovitz Edan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "FileManager.h"
#include "RequestManager.h"
#include "Server.h"

using namespace npl;
using namespace std;

/*
 * This is the CLI part of the SDK Server side
 */
int main() {

	FileManager* fileManager=new FileManager();
	RequestManager* requestManager= new RequestManager(fileManager);
	Server* server= new Server(requestManager);
	requestManager->start();
	server->start();
	cout << "*****************************" << endl;
	cout << "*** Welcome to SDK Server ***" << endl;
	cout << "*****************************" << endl;
	cout << "~ ~ ~  Press x to exit  ~ ~ ~" << endl;

	while(true){
		string command;
		cin >> command;
		if(command == "x"){
			cout << "PERFORMING EXIT" << endl;
			break;
		}else{
			cout << "Wrong input" << endl;
			cout << "Press x to exit" << endl;
		}
	}
	server->close();
	requestManager->close();

	delete fileManager;
	delete requestManager;
	delete server;
	cout<<"Server was closed"<<endl;
	return 0;
}
