/*
 * server.h
 *
 *  Created on: Jul 6, 2017
 *      Author: user
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "TCPSocket.h"
#include "MThread.h"
namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ServerHandler class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>> This class defines the functionality of a class that handles a new TCP socket that was just created >>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class ServerHandler{
public:

	/*
	 * Each class which inherits this class will define, while using this function, the way to handle a new TCP connection.
	 */
	virtual void handlePeer(TCPSocket* peer)=0;

	/*
	 * This is a destructor for ServerHandler.
	 */
	virtual ~ServerHandler(){};
};
/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Server class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>> This class is responsible for listening and accepting new TCP connections >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class Server: public MThread {
	ServerHandler* handler;
	TCPSocket* tcpServerSocket;
	bool flag;

	public:

	/*
	 * This is a constructor for Server.
	 * handler - the class that knows how to handle a new connected socket.
	 */
	Server(ServerHandler* handler):handler(handler),tcpServerSocket(NULL),flag(true){};

	/*
	 * This function runs in a loop inside a thread. It accepts and listens to new TCP
	 * connections, and it lets its handler to decide what to do with the new connections.
	 */
	virtual void run();

	/*
	 * This function gracefully closes the listening TCP socket.
	 */
	void close();

};
} /* namespace npl */

#endif /* SERVER_H_ */
