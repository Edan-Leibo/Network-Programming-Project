/*
 * LoginTest.h
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#ifndef LOGINTEST_H_
#define LOGINTEST_H_
#include "SDKClient.h"

namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> LoginTest class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> This class tests the login during the test >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class LoginTest {
private:
	SDKClient* sdkClient;
public:
	/*
	 * This is a constructor for LoginTest.
	 * sdkClient - a pointer to the sdkClient used in the test.
	 */
	LoginTest(SDKClient* sdkClient):sdkClient(sdkClient){};

	/*
	 * This function runs the actual test, SUCCESS and FAIL will be printed according to the success of the actions:
	 * sdkClient will try to login using username "reut" and password "1111".
	 */
	void test();

	/*
	 * This is a destructor for LoginTest.
	 */
	virtual ~LoginTest();
};

} /* namespace npl */

#endif /* LOGINTEST_H_ */
