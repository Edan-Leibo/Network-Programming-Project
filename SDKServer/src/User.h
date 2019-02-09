/*
 * User.h
 *
 *  Created on: Jul 6, 2017
 *      Author: user
 */

#ifndef USER_H_
#define USER_H_
using namespace std;
#include "TCPSocket.h"
#include <string>
namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> User class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>This class handles the users in the game >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class User{
private:
	string name;
	string password;
	TCPSocket* tcpSocket;
	bool isPlaying;

public:

	/*
	 * This is a constructor for User.
	 * name - the username
	 * password - the password of the user
	 * TCPSocket - a pointer to the socket on which the user connects from.
	 */
	User(string name, string password, TCPSocket* tcpSocket):name(name), password(password), tcpSocket(tcpSocket),isPlaying(false){};

	/*
	 * This is a destructor for User.
	 */
	virtual ~User();

	/*
	 * This function is a getter for the name of the user.
	 * returns: the username
	 */
	string getName() const;

	/*
	 * This function is a setter for the name of the user.
	 * name - the username.
	 */
	void setName(string name);

	/*
	 * This function is a getter for the password of the user.
	 * returns: the password
	 */
	string getPassword() const;

	/*
	 * This function is a setter for the password of the user.
	 * password - the password.
	 */
	void setPassword(string password);

	/*
	 * This function is a getter for the TCP socket of the user.
	 * returns: a pointer to a TCP socket object.
	 */
	TCPSocket* getTcpSocket() const;

	/*
	 * This function is a setter for the TCP socket of the user.
	 * TCPSocket - a pointer to a TCP socket object.
	 */
	void setTcpSocket(TCPSocket* tcpSocket);

	/*
	 * This function is a getter for the playing status of the user.
	 * returns: true - if the user is playing , false - otherwise.
	 */
	bool getIsPlaying() const;

	/*
	 * This function is a setter for the playing status of the user.
	 * isPlaying - true if the user is playing , false otherwise.
	 */
	void setIsPlaying(bool isPlaying);
};

} /* namespace npl */

#endif /* USER_H_ */
