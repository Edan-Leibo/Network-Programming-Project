/*
 * FileManager.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: user
 */

#include "FileManager.h"
#include "File.h"
#include <cstdlib>
#include <arpa/inet.h>
#include <sstream>
#include <algorithm>
#include <string>
#include "Guard.h"
#include "SDKProtocol.h"

using namespace std;


namespace npl {

FileManager::FileManager() {
	passwordsMutex=PTHREAD_MUTEX_INITIALIZER;
	hallOfFameMutex=PTHREAD_MUTEX_INITIALIZER;
}

bool FileManager::tryToAdd(string username, string password) {
	vector<string> allUsers = getAllUsername();
	string hashedPassword = hash(password);
	string newData = "";
	File userPassword;
	if (allUsers.size() == 0) {
		newData = username + " " + hashedPassword;
	} else {
		//First we check if username already exist in DB
		if (std::find(allUsers.begin(), allUsers.end(), username)!= allUsers.end()) {
			return false;
		}
		Guard guard(&passwordsMutex);
		//READ DATA
		userPassword.openForRead(PASSWORDS_PATH);
		newData = readDataFromFile(&userPassword) + ":" + username + " "+ hashedPassword;
		userPassword.close();
	}
	//WRITE DATA
	userPassword.openForWrite(PASSWORDS_PATH);
	writeDataToFile(&userPassword, newData);
	userPassword.close();
	return true;
}

bool FileManager::tryToLogin(string username, string password) {//Thread safe
	string hashedPassword = hash(password);
	string recordToSearchFor = username + " " + hashedPassword;
	vector<string> allRecords = getAllUsernamePasswords();
	if (std::find(allRecords.begin(), allRecords.end(), recordToSearchFor)!= allRecords.end()) {
		return true;
	}
	return false;
}

string FileManager::getHallOfFame() {						//Thread safe
	Guard guard(&hallOfFameMutex);
	File hallOfFameFile;
	hallOfFameFile.openForRead(HALL_OF_FAME_PATH);
	string ans = readDataFromFile(&hallOfFameFile);
	hallOfFameFile.close();
	return ans;
}

bool FileManager::updateScore(string name, int score) {		//Thread safe
	string newHOF = "";
	bool found = false;
	int counter = 0;
	vector<string> usersScores = getAllUsernameScores();	//Thread safe call
	if (usersScores.size() == 0) {
		string strScore = static_cast<ostringstream*>(&(ostringstream()<< score))->str();
		newHOF = name + " " + strScore;
	} else {
		for (std::vector<string>::iterator iter = usersScores.begin();iter != usersScores.end(); ++iter) {
			counter++;
			vector<string> oneUserOneScore = split(*iter, ' ');
			if (oneUserOneScore[0] == name) {
				int currentScore=atoi(oneUserOneScore[1].c_str());
				currentScore+=score;
				string strCurrentScore = static_cast<ostringstream*>(&(ostringstream()<< currentScore))->str();
				if (counter == 1) {
					newHOF = name + " " + strCurrentScore;
				} else {
					newHOF = newHOF + ":" + name + " " + strCurrentScore;
				}
				found = true;
			}
			else{
				if (counter == 1) {
					newHOF = oneUserOneScore[0] + " " + oneUserOneScore[1];
				} else {
					newHOF = newHOF + ":" + oneUserOneScore[0] + " " + oneUserOneScore[1];
				}
			}
		}
		if (found == false) {
			string strScore = static_cast<ostringstream*>(&(ostringstream()<< score))->str();
			newHOF = newHOF + ":" + name + " " + strScore;
		}
	}
	Guard guard(&hallOfFameMutex);
	File userScore;
	userScore.openForWrite(HALL_OF_FAME_PATH);
	writeDataToFile(&userScore, newHOF);
	userScore.close();
	return true;
}

vector<string> FileManager::getAllUsernamePasswords() {		//Thread safe
	Guard guard(&passwordsMutex);
	File passwords;
	passwords.openForRead(PASSWORDS_PATH);
	string data = readDataFromFile(&passwords);
	passwords.close();
	vector<string> allUserPasswords = split(data, ':');
	return allUserPasswords;
}

vector<string> FileManager::getAllUsername() {				//Thread safe
	vector<string> result, allUserPassword;
	allUserPassword = getAllUsernamePasswords();//getAllUsernamePasswords is Threadsafe function
	for (std::vector<string>::iterator iter = allUserPassword.begin();
			iter != allUserPassword.end(); ++iter) {
		vector<string> oneUserOnePassword = split(*iter, ' ');
		result.push_back(oneUserOnePassword[0]);
	}
	return result;
}

string FileManager::hash(string oldString) {
	reverse(oldString.begin(), oldString.end());
	return oldString;
}

vector<string> FileManager::getAllUsernameScores() {		//Thread safe
	Guard guard(&hallOfFameMutex);
	File hof;
	hof.openForRead(HALL_OF_FAME_PATH);
	string data = readDataFromFile(&hof);
	hof.close();
	vector<string> allUsersScores = split(data, ':');
	return allUsersScores;
}

vector<string> FileManager::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

/*
string FileManager::getFileContent(string path) {
	File file;
	file.openForRead(path);
	string content = readDataFromFile(&file);
	file.close();
	return content;
}
*/

string FileManager::readDataFromFile(FileBase* file) {
	string msg;
	char buff[1500];
	int msgLen;
	file->read((char*) &msgLen, 4);
	msgLen = ntohl(msgLen);
	int totalrc = 0;
	int rc;
	while (totalrc < msgLen) {
		rc = file->read((char*) &buff[totalrc], msgLen - totalrc);
		if (rc > 0) {
			totalrc += rc;
		} else {
			break;
		}
	}
	if (rc > 0 && totalrc == msgLen) {
		buff[msgLen] = 0;
		msg = buff;
	} else {
		file->close();
	}
	return msg;
}

int FileManager::writeDataToFile(FileBase* file, string msg) {
	int msgLen = msg.length();
	msgLen = htonl(msgLen);
	file->write((char*) &msgLen, 4);
	return file->write(msg.data(), msg.length()) + 4;
}

FileManager::~FileManager() {
}

} /* namespace npl */
