/*
 * UDPConnector.h
 *
 *  Created on: Jul 8, 2017
 *      Author: user
 */

#ifndef UDPCONNECTOR_H_
#define UDPCONNECTOR_H_
#include "MThread.h"
#include "UDPSocket.h"
#include "SDKClientHandler.h"
#include "SDKClient.h"


namespace npl {

/*
 * forward declaration of SDKClient.
 */
class SDKClient;

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> UDPConnector class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> This class handles the UDP connections with the clients >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class UDPConnector: public MThread{
public:

	/*
	 * This is a constructor for UDPConnector.
	 */
	UDPConnector(int port,SDKClientHandler* handler, SDKClient* sdkClient);

	/*
	 * This function sends data to the remote peer over UDP.
	 * returns: true - if the data was sent successfully, false - otherwise.
	 * data - a pointer to the data to send.
	 */
	bool sendData(const char* data) const;

	/*
	 * This function connects a UDP socket according to its IP and Port adresses.
	 * remotePeerIP - the IP address of the UDP socket
	 * remotePeerPort - the port of the UDP socket
	 */
	void connect(string remotePeerIP,int remotePeerPort) const;

	/*
	 * This function reads data from the UDP connection. This function will run on a separate thread.
	 */
	virtual void run();

	/*
	 * This function closes the UDP socket.
	 */
	void close();

	/*
	 * This is a destructor for UDPConnector.
	 */
	virtual ~UDPConnector();
private:
	UDPSocket* udpSocket;
	SDKClient* sdkClient;
	SDKClientHandler* handler;

	/*
	 * This function reads data from a UDP connection and pass it on the handler.
	 * returns: true - if the data was received successfully, false - otherwise.
	 */
	bool receiveData();
};
}
#endif
