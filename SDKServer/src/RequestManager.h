/*
 * RequestManager.h
 *
 *  Created on: Jul 6, 2017
 *      Author: user
 */

#ifndef REQUESTMANAGER_H_
#define REQUESTMANAGER_H_
#include "MThread.h"
#include "MultipleTCPSocketsListener.h"
#include "User.h"
#include "FileManager.h"
#include "Server.h"
namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RequestManager class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>> This class handles all the requests that the server receives from the client >>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class RequestManager:public MThread ,public ServerHandler{

private:
	bool flag;
	vector<TCPSocket*> unidentifiedUsers;
	vector<User*> users;
	FileManager* fileManager;
	pthread_mutex_t usersMutex;
	pthread_mutex_t unidentifiedUsersMutex;

public:
	/*
	 * This is a constructor for RequestManager.
	 * fileManager - the class that handles all file related actions.
	 */
	RequestManager(FileManager* fileManager);

	/*
	 * This function defines the way that the RequestManager handles a new connected peer.
	 * It adds the TCP socket to the unidentified users list.
	 * peer - a pointer to a TCP socket object.
	 */
	virtual void handlePeer(TCPSocket* peer); 		//ServerHandler Method

	/*
	 * This function the heart of the listening procedure. It listens simultaneously to several sockets
	 * in a time. It reads the requested command and activates the relevant function.
	 */
	virtual void run();

	/*
	 * This function stops the main loop of the listening thread and ends up the running
	 * of the request manager.
	 */
	void close();

	/*
	 * This is a destructor for FileManager.
	 */
	virtual ~RequestManager();

private:

	/*
	 * This function splits a string by the given delimiter.
	 * returns: a vector of the separated values.
	 * str - the string to split.
	 * delimiter - the char to split by.
	 */
	vector<string> split(string str, char delimiter);

	/*
	 * This function reads data from a peer.
	 * returns: the string sent by the peer.
	 * peer - a pointer to a TCP socket object.
	 */
	string readDataFromPeer(TCPSocket * peer);

	/*
	 * This function reads commands sent by a peer.
	 * returns: the number of the command sent by the peer.
	 * peer - a pointer to a TCP socket object.
	 */
	int readCommandFromPeer(TCPSocket* peer);

	/*
	 * This function sends a command to a peer (when sending to peer, command means a response).
	 * peer - a pointer to a TCP socket object.
	 * command - the number of the command to be sent.
	 */
	void sendCommandToPeer(TCPSocket* peer, int command);

	/*
	 * This function sends data to a peer.
	 * peer - a pointer to a TCP socket object.
	 * msg - the string to be sent.
	 */
	void sendDataToPeer(TCPSocket* peer, string msg);

	//REQUESTS

	/*
	 * This function handles a user's request to register with a username:password string.
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void registerUserReq(TCPSocket* readyPeer);

	/*
	 * This function handles a user's request to login with a username:password string.
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void loginUserReq(TCPSocket* readyPeer);

	/*
	 * This function handles a user's request to present the list of available users.
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void showUsersReq(TCPSocket* readyPeer);

	/*
	 * This function handles a user's request to ask another user for a game (specified or "random").
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void askForGameReq(TCPSocket* readyPeer);

	/*
	 * This function handles a user's request to answer a game offer made by another user.
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void AnswerRemoteOfferReq(TCPSocket* readyPeer);

	/*
	 * This function handles a user's request to display the hall of fame (a list of users and their scores).
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void displayHallOfFameReq(TCPSocket* readyPeer);

	/*
	 * This function handles a user's request to add him back to the available users list.
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void makeMeAvailable(TCPSocket* readyPeer);

	/*
	 * This function handles a user's request to disconnect him from the server.
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void closeMyClientReq(TCPSocket* readyPeer);

	/*
	 * This function handles a user's request to end the current game. It notifies the server that
	 * the game is over and sends it the score of the peer.
	 * readyPeer - a pointer to the TCP socket object that sent the request.
	 */
	void endGameReq(TCPSocket* readyPeer);

	/*
	 * This function returns a vector of all the logged in users.
	 * returns: a vector of logged-in usernames
	 */
	vector<TCPSocket*> getAllSocketsFromUsers();

	/*
	 * This function deletes the socket of the peer from the unidentified users list.
	 * unidentifiedToRemove - a pointer to the TCP socket object to delete.
	 */
	void removePeerFromUnidentified(TCPSocket* unidentifiedToRemove);

	/*
	 * This function takes out the socket of the peer from the unidentified users list.
	 * Notice that it doesn't delete the socket that is in the unidentifiedList, it just takes it out of the list.
	 * unidentifiedToTakeOut - a pointer to the TCP socket object to take out.
	 */
	void takeOutPeerFromUnidentified(TCPSocket* unidentifiedToTakeOut);

	/*
	 * This function deletes the socket of the peer from the users list (for example, when the user disconnects).
	 * socket - a pointer to the TCP socket object to delete.
	 */
	void removePeerFromUsers(TCPSocket* socket);

	/*
	 * This function checks if the user exists in the users list (i.e -if the user is logged in)
	 * returns: true if the user exists in the list, false otherwise.
	 * name - the username to search in the list.
	 */
	bool isExistsInUsers(string name);

	/*
	 * This function returns the name of the username associated with the given TCP socket.
	 * returns: the username that matches the socket.
	 * tcpSocket - a pointer to the socket to search in the list.
	 */
	string TCP2Name(TCPSocket* tcpSocket);

	/*
	 * This function returns the TCP socket of a user to play with (specified or "random").
	 * returns: a pointer to the TCP socket of the requested user.
	 * name - the username to play with/ "random" (lets the system choose a user)
	 * readtPeerName - the user that wants to play.
	 */
	TCPSocket* findFromUsers(string name, string readyPeerName);

	/*
	 * This function changes the status of the user from available to unavailable and vice versa unavailable
	 * peerToUpdate - a pointer to a TCP socket of the user to update.
	 * status - true if the user is playing, false if the user is available for game offers.
	 */
	void updateIsUserPlaying(TCPSocket* peerToUpdate, bool status);

	/*
	 * This function checks the status of the user, if he's playing or not.
	 * Returns true if the is available false otherwise
	 * nameToCheck - the name of the user to check if he is available
	 */
	bool isUserPlaying(string nameToCheck);
};

} /* namespace npl */

#endif /* REQUESTMANAGER_H_ */
