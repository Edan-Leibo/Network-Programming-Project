/*
 *
 *  Created on: 
 *      Author: Edan
 */

#ifndef SDKPROTOCOL_H_
#define SDKPROTOCOL_H_

/**
 * SDK protocol:
 * all messages are of the format [Command 4 byte int]
 * and optionally data follows in the format [Data length 4 byte int][ Data ]
 */
#define SERVER_PORT 3346
#define BUFF_SIZE 256

//  	CLIENT --------> SERVER   
#define REGISTER				 	1		//DATA: [username]:[password]
#define LOGIN 						2		//DATA: [username]:[password]
#define SHOW_USERS					3		
#define ASK_FOR_GAME				4		//DATA: [peer_name]\"random"
#define ANSWER_REMOTE_OFFER			5		//DATA: [remote_peer_name]:"YES"\"NO"
#define DISPLAY_HALL_OF_FAME		6
#define END_GAME					7 		//DATA: [score]
#define CLOSE_MY_CLIENT				8
#define MAKE_ME_AVAILABLE_AGAIN     17

//  	SERVER --------> CLIENT    
#define REGISTER_RESPONSE			 	9		//DATA: "fail"\"success"
#define LOGIN_RESPONSE					10		//DATA: "fail"\"success"
#define SHOW_USERS_RESPONSE				11		//DATA: [player1]: ... :[playerN]
#define ASK_FOR_GAME_RESPONSE			12		//DATA: "fail"\"success":[remote_user_UDP_IP]:[remote_user_UDP_PORT]
#define REMOTE_OFFER					13		//DATA: [remote_name]:[remote_user_UDP_IP]:[remote_user_UDP_PORT]
#define DISPLAY_HALL_OF_FAME_RESPONSE	14		//DATA: [player1] [score1]: ... :[playerN] [scoreN]
#define SERVER_CLOSED					15		
#define EMPTY							16				




#endif 
