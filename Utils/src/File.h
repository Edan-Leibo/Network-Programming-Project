/*
 * File.h
 *
 *  Created on: Jun 12, 2017
 *      Author: user
 */

#ifndef SRC_FILE_H_
#define SRC_FILE_H_
#include <iostream>
#include "FileBase.h"
using namespace std;

class File: public FileBase{
public:
	/*a constructor that opens a file with the given path
	 * @param path the path
	 */
	File();
	/*
	 * closes the file
	 */
	int openForWrite(string path);
	int openForRead(string path);
	virtual void close();
	virtual ~File();
};

#endif /* SRC_FILE_H_ */
