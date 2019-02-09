/*
 * ClientHandler.h
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#ifndef CLIENTHANDLER_H_
#define CLIENTHANDLER_H_
#include <string>
#include <iostream>
#include <cstdlib>
#include "SDKClientHandler.h"
#include "SDKClient.h"

namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ClientHandler class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>> This class will handle the client side actions during the test >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class ClientHandler: public SDKClientHandler {
public:
	//Responses to requests

	/*
	 * This function will be called when the server will respond to the registration request.
	 * It would print SUCCESS if the registration was successful, FAIL otherwise.
	 * result - the status of the registration.
	 */
	virtual void onRegisterResponse(string result);

	/*
	 * This function will be called when the server will respond to the login request.
	 * It would print SUCCESS if the login was successful, FAIL otherwise.
	 * result - the status of the login.
	 */
	virtual void onLoginResponse(string result);

	/*
	 * This function will be called when the server will respond to the request to show the users list.
	 * It would print that the users list was ACCEPTED from the server,
	 * and print SUCCESS if the logged in user name is indeed in that list, FAIL otherwise.
	 * users - a vector of the available users.
	 */
	virtual void onShowUsersResponse(vector<string> users);

	/*
	 * This function will be called when the server will respond to the request to ask for a game.
	 * It would print that the response from the server was ACCEPTED.
	 * answer - the response of the other player.
	 */
	virtual void onAskForGameResponse(string answer);

	/*
	 * This function will be called when the server will respond to the request to show the hall of fame.
	 * It would print that the hall of fame list was ACCEPTED from the server,
	 * and print SUCCESS if the data stored about the user is correct, FAIL otherwise.
	 * hallOfFame - a vector of username-score couples.
	 */
	virtual void onDisplayHallOfFameResponse(vector<string> hallOfFame);

	/*
	 * This function will be called if an unexpected list is received. This would print FAIL.
	 */
	virtual void onEmptyResponse();

	//Asynchronized notifications from server

	/*
	 * This function will be called when a remote offer is received.
	 * It would print ACCEPTED when that happens.
	 * name - the name of the player who made the offer.
	 */
	virtual void onRemoteOffer(string name);

	/*
	 * This function will be called when the connected server is closed.
	 * It would print server closed when that happens.
	 */
	virtual void onServerClosed();

	//Data from other player

	/*
	 * This function will make sure that data is received properly.
	 * It would print SUCCESS if the data is as expected, FAIL otherwise.
	 * data - a pointer to the data received.
	 */
	virtual void onDataReceived(char* data);

	/*
	 * This function is unused
	 */
	virtual void onGameCanceled();

	/*
	 * This is a destructor for ClientHandler.
	 */
	virtual ~ClientHandler() {};
};
} /* namespace npl */

#endif /* CLIENTHANDLER_H_ */
