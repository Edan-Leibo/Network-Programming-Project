#include "UDPSocketTest.h"

using namespace std;
using namespace npl;
UDPSocketTest::UDPSocketTest() {}

UDPSocketTest::~UDPSocketTest() {}

bool UDPSocketTest::test() {
	bool flag = true;
	//create UDP server
	UDPSocket* server = new UDPSocket(4467);

	//create UDP client
	UDPSocket* client = new UDPSocket(4468);

	//send a message from the client to the server
	string msg="hello";
	string ip = "127.0.0.1";
	//client->sendTo(msg, ip, 4467);
	client->connect("127.0.0.1", 4467);
	server->connect("127.0.0.1", 4468);

	client->write(msg.data(), msg.length()+1);
	// read the message by the server
	char buff[256];
	server->read(buff, 10);

	// compare the message sent with the message received
	if (!(strcasecmp(msg.data(), buff) == 0))
		flag = false;

	//Sending Other way around

	string msg2="Whatsup";
	server->write(msg2.data(), msg2.length()+1);
	// read the message by the server
	char buff2[256];
	client->read(buff2, 10);

	// compare the message sent with the message received
	if (!(strcasecmp(msg2.data(), buff2) == 0))
		flag = false;


	//old test
/*	server->reply(msg2);
	client->recv(buff2, 10);

	if (!(strcasecmp(msg2.data(), buff2) == 0))
		flag = false;

	//from address
	string fromAddr = server->fromAddr();
	if (!(strcasecmp(ip.data(), fromAddr.data()) == 0))
		flag = false;*/

	//close all sockets
	server->close();
	client->close();

	//clear memory
	delete server;
	delete client;

	return flag;
}
