#include "TCPSocketTest.h"

using namespace std;


TCPSocketTest::~TCPSocketTest() {
}

void TCPSocketTest::run() {
	connect_socket = server->listenAndAccept();
}

bool TCPSocketTest::test() {
	connect_socket=NULL;
	bool isTheSame = true;
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
	bzero(buffer,256);
	connect_socket->read(buffer, 255);
	//buffer[i] = 0;
	if (!strcasecmp(msg.data(), buffer) == 0)
		isTheSame = false;

	string fromAddr = connect_socket->fromAddr();
	if (!strcasecmp(ip.data(), fromAddr.data()) == 0)
		isTheSame = false;

	client->close();
	connect_socket->close();
	sleep(1);
	server->close();

	delete client;
	delete connect_socket;
	sleep(1);
	delete server;

	return isTheSame;
}
