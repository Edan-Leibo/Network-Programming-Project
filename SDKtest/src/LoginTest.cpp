/*
 * LoginTest.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#include "LoginTest.h"
#include <iostream>
using namespace std;

namespace npl {

void LoginTest::test(){
	sleep(2);
	if (!sdkClient->loginUser("reut", "1111")){
		cout << "Sending Login Request of a registered user 1: FAIL" << endl;
		return;
	}
	cout << "Sending Login Request of a registered user 1: SUCCESS" << endl;

}

LoginTest::~LoginTest() {
}

} /* namespace npl */
