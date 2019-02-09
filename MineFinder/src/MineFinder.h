#ifndef SRC_MINEFINDER_H_
#define SRC_MINEFINDER_H_

#include <vector>
#include "SDKClientHandler.h"
#include "SDKClient.h"
#include <string>
using namespace std;
using namespace npl;
#define BOARD_SIZE 5
#define AMOUNT_OF_MINES 2

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MineFinder class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>> This class is the game application that uses the SDK client side >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class MineFinder{
public:

	/*
	 * This is a constructor for MineFinder.
	 */
	MineFinder():myturn(false),serverConnection(false),myPlayerChar('-'),otherPlayerChar('-'), sdk(NULL){};

	/*
	 * This function initiates the game, and contains the full loop of the interaction with the player of the MineFinder game
	 */
	void start();

	/*
	 * This function updates the turn of the player.
	 * myturn - true if it is his turn, false otherwise.
	 */
	void setMyturn(bool myturn);

	/*
	 * This function is called upon when the game is over, and it sends the player's score to update it in the hall of fame.
	 * returns: true - if the score was sent successfully, false - otherwise.
	 */
	bool endGame();

	/*
	 * This function lets the players know the final score of the game and declares the winner.
	 */
	void displayFinalScore();

	/*
	 * This function updates the current board according to the given board
	 * newBoard - a pointer to the board to copy
	 */
	void updateBoard(char* newBoard);

	/*
	 * This function checks the board game to see if the game is over.
	 * returns: true - if there are no more moves, false - otherwise.
	 */
	bool isGameOver();

	/*
	 * This function updates the player's status to available after the game is over.
	 */
	void makeMeAvailable();

	/*
	 * This function displays the current board to the player.
	 * displayBoard - a pointer to the board to display
	 */
	void displayBoard(char* displayBoard);
	/*
	 * This function is a getter for server connection
	 */
	bool getServerConnection() const;

	/*
	 * * This function is a setter for server connection
	 */
	void setServerConnection(bool serverConnection);

private:

	/*
	 * This function prints the options that the client can use throughout the game.
	 */
	void printInstructions();

	/*
	 * This function checks if it is the turn of a player.
	 * returns: true - if it is his turn, false - otherwise.
	 */
	bool isMyturn() const;

	/*
	 * This function generates a new board.
	 */
	void randomBoard();

	/*
	 * This function calculates the score of the player according to the board status.
	 * returns: the score
	 * player - the char associated with mines revealed by the player.
	 */
	int getPlayerScore(char player);

	/*
	 * This function checks if s1 contains s2
	 * returns: true if s1 contains s2, false otherwise
	 * s1- the containing string
	 * s2- the contained string
	 */
	bool checkContains(const string& s1, const string& s2);


	bool myturn;
	bool serverConnection;
	char myPlayerChar;
	char otherPlayerChar;
	char board[BOARD_SIZE];
	string remoteName;
	SDKClient* sdk;
};

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Responder class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> This class handles the responses made by the server >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class Responder:public SDKClientHandler{
public:
	//Responses to requests

	/*
	 * This function is called whenever the server responds on registration.
	 * It will display the registration status.
	 * result - the status of the registration.
	 */
	virtual void onRegisterResponse(string result);

	/*
	 * This function is called whenever the server responds on login.
	 * It will display the login status.
	 * result - the status of the login.
	 */
	virtual void onLoginResponse(string result);

	/*
	 * This function is called whenever the server responds on showUsers.
	 * It will display a list of available users. In case there are
	 * no users available it will display "No free users".
	 * users - a vector of the available users.
	 */
	virtual void onShowUsersResponse(vector<string> users);

	/*
	 * This function is called whenever the server responds to askForGame.
	 * It will display whether the other player accepts the offer or not.
	 * answer - the response of the other player.
	 */
	virtual void onAskForGameResponse(string answer);

	/*
	 * This function is called whenever the server responds on displatHallOfFame.
	 * It will display a list of users and their scores.
	 * no users available it will display "No free users".
	 * hallOfFame - a vector of username-score couples.
	 */
	virtual void onDisplayHallOfFameResponse(vector<string> hallOfFame);

	/*
	 * This function is called whenever the server's response is an empty list.
	 */
	virtual void onEmptyResponse();

	//Asynchronized notifications from server

	/*
	 * This function is called whenever the server notifies that an offer for a game was
	 * received from a remote player.
	 * name - the name of the player who made the offer.
	 */
	virtual void onRemoteOffer(string name);

	/*
	 * This function is called whenever the connected server is closed.
	 * It will disconnect the client
	 */
	virtual void onServerClosed();

	//Data from other player

	/*
	 * This function handles the board game after each move.
	 * data - a pointer to the data received.
	 */
	virtual void onDataReceived(char* data);

	/*
	 * This function is called when the other player has disconnected.
	 * It updates the status of the remaining player to be available for game offers.
	 */
	virtual void onGameCanceled();

	/*
 	 * 	This function is a setter for the mineFinder
 	 * 	mineFinfer - the mineFinder to set
 	 */
	void setMineFinder(MineFinder* mineFinder);

	/*
	 * This is a destructor for Responder.
	 */
	virtual ~Responder() {};

private:
	/*
	 * This function displays any vector it receives.
	 * svect - the vector to display.
	 */
	void printVector(vector<string> svect);
	MineFinder* mineFinder;
};

#endif
