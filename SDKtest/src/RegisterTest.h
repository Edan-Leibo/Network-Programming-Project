/*
 * RegisterTest.h
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#ifndef REGISTERTEST_H_
#define REGISTERTEST_H_
#include "SDKClient.h"

namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RegisterTest class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> This class handles the registration during the test >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class RegisterTest {
private:
	SDKClient* sdkClient;
public:

	/*
	 * This is a constructor for RegisterTest.
	 * sdkClient - a pointer to the sdkClient used in the test.
	 */
	RegisterTest(SDKClient* sdkClient):sdkClient(sdkClient){};

	/*
	 * This function runs the actual test, SUCCESS and FAIL will be printed according to the success of the actions:
	 * sdkClient will try to register using username "reut" and password "1111".
	 */
	void test();

	/*
	 * This is a destructor for RegisterTest.
	 */
	virtual ~RegisterTest();
};

} /* namespace npl */

#endif /* REGISTERTEST_H_ */
