/*
 * FileTest.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#include "FileTest.h"
#include "File.h"
bool FileTest::test() {
	File file;
	file.openForWrite("TestFile.txt");
	string sent("Jack abd2:David ghy56:Danna gr65j:John fed58:Anne 85fe");
	file.write(sent.c_str(),sent.length());
	file.close();
	file.openForRead("TestFile.txt");
	char buffer[sent.length()+1];
	file.read(buffer, sent.length());
	file.close();
	buffer[sent.length()]='\0';
	return (sent==string(buffer));
}

FileTest::FileTest() {
}

FileTest::~FileTest() {
	// TODO Auto-generated destructor stub
}

