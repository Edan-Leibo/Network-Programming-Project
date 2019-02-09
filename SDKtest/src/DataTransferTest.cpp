/*
 * DataTransferTest.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#include "DataTransferTest.h"
#include "SDKClient.h"
namespace npl {

void DataTransferTest::test() {
	sleep(2);
	if (!client2->registerUser("edan", "2222")) {
		cout << "Sending Registration Request for user 2: FAIL" << endl;
		return;
	}
	cout << "Sending Registration Request for user 2: SUCCESS" << endl;

	sleep(2);
	if (!client2->loginUser("edan", "2222")) {
		cout << "Sending Login Request of a registered user 2: FAIL" << endl;
	} else {
		cout << "Sending Login Request of a registered user 2: SUCCESS" << endl;
	}

	sleep(2);
	if (!client1->askForGame("edan")) {
		cout << "Sending Ask For Game Request user 1 --> user 2: FAIL" << endl;
	} else {
		cout << "Sending Ask For Game Request user 1 --> user 2: SUCCESS"
				<< endl;
	}

	sleep(2);
	if (!client2->AnswerRemoteOffer("reut", "YES")) {
		cout << "Sending Answer For Remote Game Request: FAIL" << endl;
	} else {
		cout << "Sending Answer For Remote Game Request: SUCCESS" << endl;
	}

	sleep(2);
	if (!client1->sendData("TEST")) {
		cout << "Sending Data From user 1 to user 2: FAIL" << endl;
	} else {
		cout << "Sending Data From user 1 to user 2: SUCCESS" << endl;
	}
}

DataTransferTest::~DataTransferTest() {
}

} /* namespace npl */
