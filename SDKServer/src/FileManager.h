/*
 * FileManager.h
 *
 *  Created on: Jul 6, 2017
 *      Author: user
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_
#include <string>
#include <vector>
#include "FileBase.h"
using namespace std;

namespace npl {
/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> FileManager class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>> This class handles all the data read-write into file actions. It creates the files, reads from them and >>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> writes or manipulates the data within. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class FileManager {
public:
	/*
	 * This is a constructor for FileManager.
	 */
	FileManager();

	/*
	 * This function tries to add a user to the passwords file (defined in the protocol file).
	 * It checks if the username exists in the file, and if it doesn't then it adds it.
	 * returns: true - if the username and password were successfully added to the file, false otherwise.
	 * username - the string to look for and write to the file.
	 * password - the string to write to the file with the username.
	 */
	bool tryToAdd(string username, string password);

	/*
	 * This function checks if the given username and password exist as a couple in the password file.
	 * returns: true - if the username and password couple was found in the file, false otherwise.
	 * username - the string to look for in the file.
	 * password - the string to look for adjacent to the username.
	 */
	bool tryToLogin(string username, string password);

	/*
	 * This function reads the content of the HallOfFame file, while using the HallOfFame lock.
	 * returns: a string which contains username-score couples, separated by a colon.
	 */
	string getHallOfFame();

	/*
	 * This function updates the username's score stored in the HallOfFame file by adding the score from the
	 * current game to the stored score. If the username does not yet exist in the file, then it is added with the score.
	 * returns: true - if the score was updated (or the user was added), false otherwise.
	 * name - the username to look for in the file.
	 * score - the score to be added to the current score.
	 */
	bool updateScore(string name,int score);

	/*
	 * This is a destructor for FileManager.
	 */
	virtual ~FileManager();

private:
	pthread_mutex_t hallOfFameMutex;		// the HallOfFame lock
	pthread_mutex_t passwordsMutex;			// the passwords lock

	/*
	 * This function reads the content of the given file.
	 * returns: the string contained in the file.
	 * file - a pointer to a file object.
	 */
	string readDataFromFile(FileBase* file);

	/*
	 * This function writes the message to the given file.
	 * returns: number of bytes written to the file. In case of an error returns a negative number.
	 * file - a pointer to a file object.
	 * msg - the string to write to the file.
	 */
	int writeDataToFile(FileBase* file, string msg);

	/*
	 * This function activates hashing function on the given string.
	 * returns: the hashed string.
	 * oldString - the string to hash.
	 */
	string hash(string oldString);

	/*
	 * This function splits a string by the given delimiter.
	 * returns: a vector of the separated values.
	 * str - the string to split.
	 * delimiter - the char to split by.
	 */
	vector<string> split(string str, char delimiter);

	/*
	 * This thread-safe function reads the string in the passwords file and puts it into a vector,
	 * while using the passwords lock.
	 * returns: a vector of the username-password couples.
	 */
	vector<string> getAllUsernamePasswords();

	/*
	 * This function returns a list of all the users.
	 * returns: a vector of usernames.
	 */
	vector<string> getAllUsername();

	/*
	 * This function reads the data from the HallOfFame file and puts it into a vector, using the HallOfFame lock.
	 * returns: a vector of the username-score couples separated by colon.
	 */
	vector<string> getAllUsernameScores();
};

} /* namespace npl */

#endif /* FILEMANAGER_H_ */
