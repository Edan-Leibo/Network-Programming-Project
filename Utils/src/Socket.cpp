/*
 * Socket.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#include "Socket.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include <inttypes.h>
#include <strings.h>

using namespace std;

Socket::Socket(int type) {
	fd = socket (AF_INET, type, 0);
	connected=false;
}
Socket::Socket(){
	connected=false;
}

int Socket::bind(int port) {
		struct sockaddr_in  s_in;
		bzero((char *) &s_in, sizeof(s_in));
		s_in.sin_family = (short)AF_INET;
		s_in.sin_addr.s_addr = htonl(INADDR_ANY);
		s_in.sin_port = htons(port);

		if (::bind(fd, (struct sockaddr *)&s_in, sizeof(s_in))<0){
			cout<<"Error naming channel"<<endl;
			return -1;
		}
		return 1;
}

int Socket::connect(string ip, int port){
	bzero((char *) &remote, sizeof(remote));

//setting the address
	remote.sin_family = (short) AF_INET;
	remote.sin_addr.s_addr = inet_addr(ip.data());
	remote.sin_port = htons((u_short) port);

	if (::connect(fd, (sockaddr*) &remote, sizeof(remote)) < 0) {
		perror("Error creating connection!");
		::close(fd);
		connected=false;
		return -1;
	}
	connected=true;
	return 1;
}

int Socket::getPort() const{
	struct sockaddr_in localAddress;
	unsigned int addressLength=sizeof(localAddress);
	bzero(&localAddress, sizeof(localAddress));
	getsockname(fd, (struct sockaddr*)&localAddress, &addressLength);
	return (int) ntohs(localAddress.sin_port);
}

char * Socket::getIP() const{
	struct sockaddr_in localAddress;
	unsigned int addressLength=sizeof(localAddress);
	bzero(&localAddress, sizeof(localAddress));
	getsockname(fd, (struct sockaddr*)&localAddress, &addressLength);
	return inet_ntoa(localAddress.sin_addr);
}


string Socket::getIPport() const {
	char buff[100];
	sprintf(buff, "%s:%d", this->getIP(), this->getPort());
	return buff;
}

void Socket::close(){
	shutdown(fd,SHUT_RDWR);
	::close(fd);
	connected=false;
}

Socket::~Socket() {
}

bool Socket::isConnected() const {
	return connected;
}
