#include <iostream>
#include "UDPSocketTest.h"
#include "TCPSocketTest.h"
#include "FileTest.h"
#include "MultipleListenerTest.h"

using namespace std;
using namespace npl;

/*
 * This file runs all the tests for modules in Utils static library
 */
int main() {
	cout << "..................................." << endl;
	cout << "   Testing Utils static library" << endl;
	cout << "..................................." << endl;

	bool res = false;
	string sTest;

	//	Test UDPSocket
	UDPSocketTest* test1 = new UDPSocketTest();
	res = test1->test();
	sTest = "Test UDPSocket";
	if (res == true)
		cout << sTest << " PASS" << endl;
	else
		cout << sTest << " FAIL!!!" << endl;
	//

	res = false;
	//	Test TCPSocket
	TCPSocketTest* test2 = new TCPSocketTest();
	res = test2->test();
	sTest = "Test TCPSocket";
	if (res == true)
		cout << sTest << " PASS" << endl;
	else
		cout << sTest << " FAIL!!!" << endl;

	res = false;
	//	Test File
	FileTest* test3 = new FileTest();
	res = test3->test();
	sTest = "Test File";
	if (res == true)
		cout << sTest << " PASS" << endl;
	else
		cout << sTest << " FAIL!!!" << endl;

	res = false;

	//	Test MultipleTCPSocketListener
	MultipleListenerTest* test4 = new MultipleListenerTest();
	res = test4->test();
	sTest = "Test MultipleTCPSocketListener";
	if (res == true)
		cout << sTest << " PASS" << endl;
	else
		cout << sTest << " FAIL!!!" << endl;


	delete test1;
	delete test2;
	delete test3;
	delete test4;
	return 0;
}

