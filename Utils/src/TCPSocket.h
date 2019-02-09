#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include "Socket.h"
using namespace std;

class TCPSocket: public Socket{

private:
	//struct sockaddr_in peerAddr;
	//struct sockaddr_in serverAddr;

	/**
	 * A constructor that creates socket to communicate with connected socket
	 */
	TCPSocket(int connected_sock,struct sockaddr_in serverAddr,struct sockaddr_in peerAddr);

public:
	/**
	 * A Constructor to create a TCP server socket
	 */
	TCPSocket(int port);

	/**
	 * Constructor that creates TCP client socket and connect it to the remote peer in the given ip and port
	 */
	TCPSocket(string peerIp, int port);

	/**
	 * Perform listen and accept on server socket
	 * returns a new TCPSocket object to communicate over the incoming session
	 */
	TCPSocket* listenAndAccept();

	/**
	 * return the address of the connected peer
	 */
	string fromAddr();
	/*
	 * Returns the from port number
	 */
	int fromPort();
	/*
	 * Returns the from addr:port number
	 */
	string fromAddrPort();
};

#endif
