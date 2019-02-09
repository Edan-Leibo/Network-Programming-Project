/*
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#ifndef SHOWUSESERSTestTEST_H_
#define SHOWUSESERSTestTEST_H_
#include "SDKClient.h"

namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ShowUsersTest class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> This class handles display the available users list the test >>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class ShowUsersTest {
private:
	SDKClient* sdkClient;
public:

	/*
	 * This is a constructor for ShowUsersTest.
	 * sdkClient - a pointer to the sdkClient used in the test.
	 */
	ShowUsersTest(SDKClient* sdkClient):sdkClient(sdkClient){};

	/*
	 * This function runs the actual test, SUCCESS and FAIL will be printed according to the success of the actions:
	 * sdkClient will send a request to display the available users list.
	 * Later on, when the available list users will be accepted its content will be checked
	 */
	void test();

	/*
	 * This is a destructor for ShowUsersTest.
	 */
	virtual ~ShowUsersTest();
};

} /* namespace npl */

#endif /* LOGINTEST_H_ */
