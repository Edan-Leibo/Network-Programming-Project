/*
 * SDKClient.h
 *
 *  Created on: Jul 5, 2017
 *      Author: user
 */

#ifndef SRC_SDKCLIENT_H_
#define SRC_SDKCLIENT_H_
using namespace std;
#include <iostream>
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "MThread.h"
#include <vector>
#include <string>
#include <sstream>
#include "SDKClientHandler.h"
#include "UDPConnector.h"

namespace npl {

/*
 * Forward declaration of UDP connector.
 */
class UDPConnector;
/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SDKClient class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>> The client side of the SDK. It defines the functionality of creating a new game >>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>> The connection to the server will be over TCP while the game itself will be over UDP >>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> directly with the other peer >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class SDKClient: public MThread{
private:
	string* lastOneOffered;
	string myUsername;
	string remotePeerIP;
	int remotePeerPort;
	SDKClientHandler* handler;
	bool activeServer;		//indicates if that there is an active connection to the server
	bool activePeer;		//indicates if that there is an active peer
	bool loggedIn;
	TCPSocket* tcpSocket;
	UDPConnector* udpConnector;
public:

	/*
	 * This function is a constructor for SDKClient. It creates a new client-side game application.
	 * handler- a class that the APK needs to inherit and define what
	 * 			to do on each response that we get from the server.
	 */
	SDKClient(SDKClientHandler* handler);

	/*
	 * This function connects the TCP socket to the server. The server's port number is defined in SDKProtocol.h
	 * returns: true - if the request was successfully sent, false - otherwise.
	 * ip - the ip address of the new TCP socket.
	 */
	bool connect(string ip);

	/*
	 * This function checks the validity of the username and password, and sends a REGISTER request to the server.
	 * returns: true - if the request was successfully sent, false - otherwise.
	 * username - the username to register.
	 * password - the password to register.
	 */
	bool registerUser(string username, string password);

	/*
	 * This function checks the validity of the username and password, and sends a LOGIN request to the server.
	 * returns: true - if the request was successfully sent, false - otherwise.
	 * username - the username.
	 * password - the password.
	 */
	bool loginUser(string username, string password);

	/*
	 * This function sends a request to the server to display all the available users.
	 * You can only activate this function after you're connected and logged in
	 * returns: true - if the request was successfully sent, false - otherwise.
	 */
	bool showUsers();

	/*
	 * This function sends a request to the server to ask the given username for a game.
	 * In case name is "random" a request to a random user will be sent.
	 * You can only activate this function after you're connected and logged in
     * returns: true - if the request was successfully sent.
     * 		    false - in case you ask to play with yourself or you're on a game with other one
	 * name - the name of the user you want to play with.
	 */
	bool askForGame(string name);

	/*
	 * This function sends your response for a game offer to the server.
	 * You can only answer the last peer that asked you
	 * returns: true - if the request was successfully sent, false - otherwise.
	 * remoteName - the name of the user who offered to play.
	 * answer - "YES" or "NO".
	 */
	bool AnswerRemoteOffer(string remoteName, string answer);

	/*
	 * This function sends a request to the server to display the hall of fame.
	 * You can only activate this function after you're connected and logged in
	 * returns: true - if the request was successfully sent, false - otherwise.
	 */
	bool displayHallOfFame();

	/*
	 * This function sends data to the peer, using UDP.
	 * Sending when you're not in not a game will cause no effect and make the function return false
	 * returns: true - if the data was successfully sent, false - otherwise.
	 */
	bool sendData(const char* data);

	/*
	 * This function checks if there is a connection with the server.
	 * returns: true - if there is a connection with the a server, false - otherwise.
	 */
	bool isActiveServer() const;

	/*
	 * This function checks if there is a connection with a another peer.
	 * returns: true - if there is a connection with another peer, false - otherwise.
	 */
	bool isActivePeer() const;

	/*
	 * This function sends a request to the server to end the game and update the score.
	 * returns: true - if the request was successfully sent, false - otherwise.
	 * score - the score to update.
	 */
	bool endGame(int score);

	/*
	 * This function is used to notify that remote peer disconnected and now
	 * it lets the server know that we are available for a game again.
	 * return true if there is a server connected and the message was sent, false otherwise
	 */
	bool returnToAvailableStatus();

	/*
	 * This client sends the server and other peer a closing message and closes all its connections.
	 */
	void disconnect();

	/*
	 * This is a destructor for SDKClient.
	 */
	virtual ~SDKClient();

private:

	virtual void run();

	/*
	 * This function sends a command to the server.
	 * returns: the length of the data sent. If the sending was not successful then a negetive number is returned.
	 * cmd - the command number.
	 * buff - the data to send with the command.
	 */
	int sendCommand(int cmd, const char* buff);

	/*
	 * This function receives a command from the server.
	 * returns: true - if the command was received successfully, false - otherwise.
	 */
	bool recvCommand();

	/*
	 * This function receives messages from the server.
	 * returns: the message received from the server.
	 */
	string readMessageFromServer();

	/*
	 * This function splits a string by the given delimiter.
	 * returns: a vector of the separated values.
	 * str - the string to split.
	 * delimiter - the char to split by.
	 */
	vector<string> split(string str, char delimiter);

	/*
	 * This function checks if the srting contains white spaces.
	 * returns: true - if the string contains spaces, false - otherwise.
	 * str - the address of the string to check.
	 */
	bool containsSpaces(const string& str);

};

}/* namespace npl */

#endif /* SRC_SDKCLIENT_H_ */
