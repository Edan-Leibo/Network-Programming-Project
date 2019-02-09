/*
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#include "HallOfFameTest.h"
#include <iostream>
using namespace std;

namespace npl {

void HallOfFameTest::test(){

	sleep(2);
	if (!sdkClient->endGame(2000)){
		cout << "Sending Update Score Request: FAIL" << endl;
	}else{
		cout << "Sending Update Score Request: SUCCESS" << endl;
	}

	sleep(2);
	if (!sdkClient->displayHallOfFame()){
		cout << "Sending display Hall Of Fame Request: FAIL" << endl;
	}else{
	cout << "Sending display Hall Of Fame Request: SUCCESS" << endl;
	}
}

HallOfFameTest::~HallOfFameTest() {
}

} /* namespace npl */
