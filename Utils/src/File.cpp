/*
 * File.cpp
 *
 *  Created on: Jun 12, 2017
 *      Author: user
 */

#include "File.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

File::File() {}

int File::openForWrite(string path) {
	fd = open(path.data(), O_CREAT|O_WRONLY|O_TRUNC , 0666);
	if (fd == -1){
		perror("Cannot open output file\n");
	}
	return fd;
}

int File::openForRead(string path) {
	fd = open(path.data(), O_CREAT|O_RDONLY , 0666);
	if (fd == -1){
		perror("Cannot open output file\n");
	}
	return fd;
}
void File::close() {
	::close(fd);
}

File::~File() {
}

