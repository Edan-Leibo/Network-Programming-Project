/*
 * server.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: user
 */

#include "Server.h"
#include "SDKProtocol.h"
namespace npl {

void Server::run() {
	tcpServerSocket=new TCPSocket(SERVER_PORT);
	cout<<"> TCP server binding..."<<endl;

	while (flag) {
		TCPSocket* peerSocket = NULL;
		cout<<"> Listening for connections..."<<endl;
		peerSocket=tcpServerSocket->listenAndAccept();
		if (peerSocket==NULL) break;
		cout << "> New peer connected: " << peerSocket->fromAddr()<<":"<<peerSocket->fromPort()<< endl;
		handler->handlePeer(peerSocket);
	}
	cout<<"> Closing socket"<<endl;
}

void Server::close() {
	flag = false;
	tcpServerSocket->close();
	this->waitForThread();
	delete tcpServerSocket;
}
} /* namespace npl */
