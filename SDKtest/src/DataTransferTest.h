/*
 * DataTransferTest.h
 *
 *  Created on: Jul 18, 2017
 *      Author: user
 */

#ifndef DATATRANSFERTEST_H_
#define DATATRANSFERTEST_H_
#include "SDKClient.h"
namespace npl {

/*
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DataTransferTest class >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> This class handles the data transfer between clients >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
class DataTransferTest {
private:
	SDKClient* client1;
	SDKClient* client2;
public:

	/*
	 * This is a constructor for DataTransferTest.
	 * client 1&2 - pointers to SDKClient objects of the clients transfering data during the test.
	 */
	DataTransferTest(SDKClient* client1,SDKClient* client2):client1(client1),client2(client2){};

	/*
	 * This function runs the actual test, SUCCESS and FAIL will be printed according to the success of the actions:
	 * 1. edan registers with password 2222
	 * 2. edan logs in to the system
	 * 3. reut sends edan a game offer from
	 * 4. edan answers YES to reut
	 * 5. reut send the string "TEST" to edan
	 *
	 */
	void test();

	/*
	 * This is a detructor for DataTransferTest.
	 */
	virtual ~DataTransferTest();
};

} /* namespace npl */

#endif /* DATATRANSFERTEST_H_ */
