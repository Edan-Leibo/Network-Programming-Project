#ifndef UDPSOCKETTEST_H_
#define UDPSOCKETTEST_H_

#include "UDPSocket.h"
#include "MThread.h"

class UDPSocketTest {
public:
	UDPSocketTest();
	virtual ~UDPSocketTest();
	bool test();
};

#endif /* UDPSOCKETTEST_H_ */
