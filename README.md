# :computer: Final Project - Network Programming :satellite:
A final project of a Network Programming course which implents a system of a hybrid P2P and a client-server gaming platform including a game that uses this platform.

## :video_game: Overview :two_men_holding_hands:
This project is a platform for creating 2-player games across the web. It is implemented by a hybrid architecture which combines P2P interactions and a central server.
When creating a connection between two endpoints across the web the main challenge is to locate each other and exchange IPs. In order to address this issue, I used a main server which its job is to manage all the players who seek an opponent and to couple them into pairs. Each user must register or login into the system in order to play, and once he does that his information is saved in a file in case he'll play the game again in the future. Saving the credentials also allows the server to keep an accumulating score for each user.
Each connected user can request the list of all other available opponents, then he can select one of them and send him an offer to play. Once the other player agrees the game starts and the communication is then conducted between the two users without any intervention by the server.
At the end of the game, each player informs the server that the game has ended and sends it his score. The server then puts the players back on the available opponents list and updates their score.

**_Note:_ A lock sign in the following schemes indicates a Mutex which enables synchronic access to a common resource.
Mutex is required in order to prevent two different threads from writing to the same resource at the same time, causing an unexpected behavior.**

## :point_right: SDK server :point_left:
**The SDK module is responsible for the server side and is composed of three main components: Server, Request Manager and File Manager.**
![alt text](https://i.imgur.com/DKuAIA2.png)

### Server :man:
Initializes a task on a new thread which its job is to listen to new connections and accept them. Any new incoming socket is passed on to the Request Manager for further handling.

### Request Manager :pray:
Holds two data structures for socket managing: the first is used to handle the unidentified incoming sockets mentioned above, and the second for handling identified sockets (i.e. after user registration/login) which are then referred to as users.
The Request Manager initializes a task on a new thread which listens simultaneously to both unidentified and identified users through a single socket. Once an unidentified socket tries to login into the system, the Request Manager requests the File Manager to authenticate the user credentials, and if the user indeed exists in the system, it encapsulates the socket in a new object named "user" and initializes a flag which indicates that the user is available to play.

### File Manager :open_file_folder:
The File Manager is not a live object, and is only responsible for two things:
1.	Managing users' credentials and authenticating login requests, using the passwords.txt file.
2.	Managing the different scores for the users, using the halloffame.txt file.
As mentioned before, the access to these files is synchronized using two different Mutexes.

## Game start scenario :runner:
Following is a simple explanation about the way a new game begins.
![alt text](https://i.imgur.com/1XYbHpj.jpg)

1.	The first user sends a request to the server with the name of the other opponent.
2.	The server forwards the request to the second user including the name of the first user, its IP and port.
3.	By that time, the second user can receive multiple requests and choose which offer to accept. He answers the server with the name of the player he wants to play against.
4.	The server forwards the answer to the first user along with the IP and port of the second user.

At this point, both players have acquired each other's IP and port, and they can now connect in P2P manner. The server then changes the state of their flags to "unavailable for playing".

**_Any developer who seeks to use this system needs to look at the different interfaces and essentially implement the interaction between the two players (i.e. the game itself). As an example, I implemented a simple guessing game in which a number is randomly chosen by the system and the players need to guess it. The first player to guess the number – wins. Fewer guesses reward the player with a higher score._**

## Game end scenario :checkered_flag:
The following scheme shows the messages exchange which leads to the end of the game.
![alt text](https://i.imgur.com/ai67NGI.jpg)

When the game ends each player sends the server a massage which indicates that the game has ended, along with his score. Afterwards they send an additional request to the server to put them back on the available opponents list. The server then persists the score to the halloffame.txt file and updates the flag of each user to an "available state".


**_Developed by Edan Leibovitz_**

**_edan.leibo@gmail.com_**

**:smile: Feel free to use it at will with attribution of source. :bowtie:**

**:astonished: If you find any typos, errors, inconsistencies etc. please do not hesitate to contact me for any issue. :mailbox:**



