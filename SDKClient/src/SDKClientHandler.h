/*
 *
 *  Created on: Jul 8, 2017
 *      Author: user
 */

#ifndef SRC_SDKCLIENTHANDLER_H_
#define SRC_SDKCLIENTHANDLER_H_
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SDKClientHandler class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>> This class defines the different events that can be initiated on the client side by the server. >>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>> APK must inherit this class and implement its own behavior. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class SDKClientHandler {
public:
	/**** Responses to requests ****/

	/*
	 * A response from server on how the registration process went
	 * result- "success" in case registration was successful
	 * 		   "fail" otherwise
	 */
	virtual void onRegisterResponse(string result)=0;

	/*
	 * A response from server on how the login process went
	 * result- "success" in case registration was successful
	 * 		   "fail" otherwise
	 */
	virtual void onLoginResponse(string result)=0;

	/*
	 * A response from server for the show user request
	 * users- a vector of users that are available at the moment
	 */
	virtual void onShowUsersResponse(vector<string> users)=0;

	/*
	 * A response from server on ask for game request
	 * result- "YES" in case the other side agreed
	 * 		   "NO" otherwise
	 */
	virtual void onAskForGameResponse(string answer)=0;

	/*
	 * A response from server for the Display Hall Of Fame request
	 * users- a vector of users and their scores
	 */
	virtual void onDisplayHallOfFameResponse(vector<string> hallOfFame)=0;

	/*
	 * Notifies that an empty response was received
	 * For example: Hall of fame without any scores
	 */
	virtual void onEmptyResponse()=0;

	/**** synchronized notifications from server ****/

	/*
	 * Notifies that a remote offer was received from other peer.
	 * This notification comes from the server.
	 * data- the data that was accepted
	 */
	virtual void onRemoteOffer(string name)=0;

	/*
	 * Notifies that the server was closed
	 */
	virtual void onServerClosed()=0;

	/**** Notifications from other player ****/

	/*
	 * Notifies that new data receive from other peer
	 * data- the data that was accepted
	 */
	virtual void onDataReceived(char* data)=0;

	/*
	 * Notifies that other peer canceled the game
	 */
	virtual void onGameCanceled()=0;

	/*
	 * A destructor for SDKClientHandler
	 */
	virtual ~SDKClientHandler(){};
};

} /* namespace npl */

#endif /* SRC_SDKCLIENTHANDLER_H_ */
