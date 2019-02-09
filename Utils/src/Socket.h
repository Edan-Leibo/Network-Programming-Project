/*
 * Socket.h
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include "Socket.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <inttypes.h>
#include<iostream>
#include "FileBase.h"
using namespace std;



class Socket:public FileBase {
protected:
	struct sockaddr_in local;
	struct sockaddr_in remote;
	bool connected;
	Socket();
public:
	/**
	 * Constructor create a socket depends on the given type
	 * @param type the type of socket to create
	 */
	Socket(int type);

	/*
	 * binds a socket
	 * @param port the port to bind to
	 */
	int bind(int port);

	/*
	 * connects the socket to a remote socket
	 * @param ip the remote ip
	 * @param port the remote port
	 */
	virtual int connect(string ip, int port);
	/*
	 * this function is a getter for the port number
	 */
	int getPort() const;
	/*
	 * this function is a getter for the port number
	 */
	char * getIP() const;
	/*
	 * this function is a getter for the ip:port
	 */
	string getIPport() const;
	/*
	 * closes the socket
	 */
	virtual void close();
	/*
	 * this function shows whether the socket is connected or not
	 */
	bool isConnected() const;
	/*
	 * A destructor for Socket class
	 */
	virtual ~Socket();
};

#endif /* SRC_SOCKET_H_ */
