/*
 * UDPSocket.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Eliav Menachi
 */

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include <netinet/in.h>
#include <inttypes.h>
#include <strings.h>
#include <stdio.h>
#include <iostream>
#include "Socket.h"
using namespace std;
namespace npl{

class UDPSocket:public Socket{


public:
	UDPSocket(int port = 9999);

	/*
	 * receives a buffer of data from the socket
	 * @param buffer the buffer to read to it
	 * @param length the amount of bytes to read to it
	 */
	int recv(char* buffer, int length);

	/*
	 * sends a reply to the saved socket
	 * @param msg the message to send as reply
	 */
	int reply(const string& msg);
	/**
	 * returns the address of the connected peer
	 */
	string fromAddr();
};

}
#endif /* UDPSOCKET_H_ */
