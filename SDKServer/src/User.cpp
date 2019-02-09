/*
 * User.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: user
 */

#include "User.h"

namespace npl {


string User::getName() const {
	return name;
}

void User::setName(string name) {
	this->name = name;
}

string User::getPassword() const {
	return password;
}

void User::setPassword(string password) {
	this->password = password;
}

TCPSocket* User::getTcpSocket() const {
	return tcpSocket;
}


void User::setTcpSocket(TCPSocket* tcpSocket) {
	this->tcpSocket = tcpSocket;
}
bool User::getIsPlaying() const {
	return isPlaying;
}

void User::setIsPlaying(bool isPlaying) {
	this->isPlaying = isPlaying;
}

User::~User() {
}

} /* namespace npl */
