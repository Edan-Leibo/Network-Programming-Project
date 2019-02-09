/*
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */



#ifndef HOF_H_
#define HOF_H_
#include "SDKClient.h"


namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> HallOfFameTest class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> This class tests the hall of fame >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class HallOfFameTest{
private:
	SDKClient* sdkClient;
public:

	/*
	 * This is a constructor for HallOfFameTest.
	 * sdkClient - a pointer to the sdkClient used in the test.
	 */
	HallOfFameTest(SDKClient* sdkClient):sdkClient(sdkClient){};

	/*
	 * This function runs the actual test, SUCCESS and FAIL will be printed according to the success of the actions:
	 * 1. sdkClient asks to update the score 2000 to his username
	 * 2. sdkClient asks to view the hall of fame, later on,
	 *    when response will be accepted the hall of fame will be checked
	 */
	void test();

	/*
	 * This is a destructor for HallOfFameTest.
	 */
	virtual ~HallOfFameTest();
};

} /* namespace npl */

#endif /* HOF_H_ */
