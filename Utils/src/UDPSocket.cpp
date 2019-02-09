/*
 * UDPSocket.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Eliav Menachi
 */

#include "UDPSocket.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

using namespace npl;

UDPSocket::UDPSocket(int port):Socket(SOCK_DGRAM){
	bind(port);
}
//~~~~~~~~~~~~~~~~~DO NOT DELETE COMMENTED LINES YET!!~~~~~~~~~~~~~~~~~~~
int UDPSocket::recv(char* buffer, int length){
	//printf("UDP server receive ...\n");
	socklen_t fromSize = sizeof(remote);
	int rc = recvfrom(fd, buffer, length, 0,(sockaddr*)&remote,&fromSize);
	return rc;
}

//<<<<<<<< they work together >>>>>>>>>>>>>

int UDPSocket::reply(const string& msg){
	//cout<<"reply "<<msg<<" "<< endl;
	socklen_t fromSize = sizeof(remote);
	int rc = sendto(fd,msg.c_str(), msg.length(),0,(struct sockaddr *)&remote,fromSize);
	return rc;
}
/*int UDPSocket::sendTo(const string& msg,const string& ip, int port){
	struct sockaddr_in  s_in;
	bzero((char *) &s_in, sizeof(s_in));
	s_in.sin_family = (short)AF_INET;
	s_in.sin_addr.s_addr = inet_addr(ip.c_str());
	s_in.sin_port = htons(port);

	int rc = sendto(socket_fd,msg.c_str(), msg.length(),0,(struct sockaddr *)&s_in,sizeof(s_in));
	return rc;
}*/


string UDPSocket::fromAddr(){
	return inet_ntoa(remote.sin_addr);
}



