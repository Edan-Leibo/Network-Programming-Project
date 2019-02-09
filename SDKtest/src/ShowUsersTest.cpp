/*
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#include "ShowUsersTest.h"

#include <iostream>
using namespace std;

namespace npl {

void ShowUsersTest::test(){
	sleep(2);
	if (!sdkClient->showUsers()) {
		cout << "Sending request to show all available users: FAIL" << endl;
		return;
	}
	cout << "Sending request to show all available users: SUCCESS" << endl;
}

ShowUsersTest::~ShowUsersTest() {
}

} /* namespace npl */
