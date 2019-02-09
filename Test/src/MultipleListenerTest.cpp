/*
 * MultipleListenerTest.cpp
 *
 *  Created on: Jul 21, 2017
 *      Author: user
 */

#include "MultipleListenerTest.h"
namespace npl {

void MultipleListenerTest::run() {
	connect_socket = server->listenAndAccept();
	msp.addSocket(connect_socket);
	//Now we listen to the connected socket on the msp
}

bool MultipleListenerTest::test() {

	connect_socket = NULL;
	bool result = true;
	string ip = "127.0.0.1";
	int port = 1234;
	server = new TCPSocket(port);

	//First Activate the server
	start();
	//Making sure that server was established
	sleep(1);
	client = new TCPSocket(ip, port);
	waitForThread();

	string msg = "hello";
	client->write(msg.data(), msg.length());

	char buffer[256];
	bzero(buffer, 256);
	TCPSocket* readySocket = msp.listenToSocket(5);
	if (readySocket == NULL) {
		result = false;
	} else {

		readySocket->read(buffer, 255);

		if (!strcasecmp(msg.data(), buffer) == 0)
			result = false;

		string fromAddr = readySocket->fromAddr();
		if (!strcasecmp(ip.data(), fromAddr.data()) == 0)
			result = false;
	}

	client->close();
	connect_socket->close();
	sleep(1);
	server->close();

	delete client;
	delete connect_socket;
	sleep(1);
	delete server;

	return result;
}

MultipleListenerTest::~MultipleListenerTest() {
}

} /* namespace npl */
