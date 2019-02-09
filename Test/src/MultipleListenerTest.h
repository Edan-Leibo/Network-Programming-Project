/*
 * MultipleListenerTest.h
 *
 *  Created on: Jul 21, 2017
 *      Author: user
 */

#ifndef MULTIPLELISTENERTEST_H_
#define MULTIPLELISTENERTEST_H_
#include "MThread.h"
#include <iostream>
#include "TCPSocket.h"
#include "MultipleTCPSocketsListener.h"

namespace npl {

class MultipleListenerTest: public MThread{
private:
	TCPSocket* server;
	TCPSocket* connect_socket;
	TCPSocket* client;
	MultipleTCPSocketsListener msp;

	bool stop;
public:
	MultipleListenerTest():server(NULL),connect_socket(NULL),client(NULL),stop(false){};
	bool test();
	void run();
	virtual ~MultipleListenerTest();
};

} /* namespace npl */

#endif /* MULTIPLELISTENERTEST_H_ */
