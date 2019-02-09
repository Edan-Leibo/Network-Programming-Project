/*
 * UDPConnector.cpp
 *
 *  Created on: Jul 8, 2017
 *      Author: user
 */

#include "UDPConnector.h"
#include "SDKProtocol.h"
namespace npl {


UDPConnector::UDPConnector(int port,SDKClientHandler* handler,SDKClient* sdkClient){
	udpSocket = new UDPSocket(port);
	this->handler = handler;
	this->sdkClient=sdkClient;
}

bool UDPConnector::sendData(const char* data) const{
	return udpSocket->write(data, BUFF_SIZE);
}

void UDPConnector::connect(string remotePeerIP,int remotePeerPort) const{
	udpSocket->connect(remotePeerIP,remotePeerPort);
}

void UDPConnector::close() {
	udpSocket->close();
	delete udpSocket;
	udpSocket=NULL;
}

void UDPConnector::run() {
	while (receiveData());
}

bool UDPConnector::receiveData() {
	char buff[BUFF_SIZE];
	int result = udpSocket->read(buff, BUFF_SIZE);
	if (result<=0)
		return false;
	if (string(buff)=="Quit"){
		sdkClient->returnToAvailableStatus();
		handler->onGameCanceled();
		return true;
	}
	this->handler->onDataReceived(buff);
	return true;
}

UDPConnector::~UDPConnector() {
}

} /* namespace npl */
