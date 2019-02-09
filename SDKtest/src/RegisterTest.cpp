/*
 * RegisterTest.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#include "RegisterTest.h"
#include <iostream>
using namespace std;

#define REGISTER_FILE "Password.txt"

namespace npl {


void RegisterTest::test() {
	sleep(2);
	if (!sdkClient->registerUser("reut", "1111")){
		cout << "Sending Registration Request for user1: FAIL" << endl;
		return;
	}
	cout << "Sending Registration Request for user1: SUCCESS" << endl;
}

RegisterTest::~RegisterTest() {
}

} /* namespace npl */
