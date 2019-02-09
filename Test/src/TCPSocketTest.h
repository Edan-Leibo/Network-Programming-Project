#ifndef TCPSOCKETTEST_H_
#define TCPSOCKETTEST_H_

#include "TCPSocket.h"
#include "MThread.h"
#include <iostream>

class TCPSocketTest : public MThread{
private:
	TCPSocket* server;
	TCPSocket* connect_socket;
	TCPSocket* client;
	bool stop;

public:
	TCPSocketTest():server(NULL),connect_socket(NULL),client(NULL),stop(false){};
	virtual ~TCPSocketTest();
	bool test();
	void run();
};
#endif /* TCPSOCKETTEST_H_ */
