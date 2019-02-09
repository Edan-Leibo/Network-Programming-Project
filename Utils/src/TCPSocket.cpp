#include "TCPSocket.h"
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

TCPSocket::TCPSocket(int connected_sock,struct sockaddr_in serverAddr,struct sockaddr_in peerAddr):Socket(){
	this->fd = connected_sock;
	//local is the server address
	this->local = serverAddr;
	this->remote = peerAddr;
}

TCPSocket::TCPSocket(int port):Socket(SOCK_STREAM){
	int optval;
	optval = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
	bind(port);
}

TCPSocket::TCPSocket(string peerIp, int port):Socket(SOCK_STREAM){
	connect(peerIp, port);
}

TCPSocket* TCPSocket::listenAndAccept(){
		int check = listen(fd, 1);
		if (check<0){
			return NULL;
		}
		socklen_t len=sizeof(remote);
		bzero((char *) &remote, sizeof(remote));
		int connectedClient = accept(fd, (sockaddr*)&remote,&len);
		if (connectedClient<0){
			return NULL;
		}

		//Once we got a new connection
		return new TCPSocket(connectedClient, local, remote);
}


string TCPSocket::fromAddr(){
	return inet_ntoa(remote.sin_addr);
}

int TCPSocket::fromPort(){
	return (int) ntohs(remote.sin_port);
}

string TCPSocket::fromAddrPort(){
	char buff[100];
	sprintf(buff, "%s:%d", inet_ntoa(remote.sin_addr), fromPort());
	return buff;
}


