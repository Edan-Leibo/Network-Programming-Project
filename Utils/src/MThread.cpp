

#include "MThread.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>


using namespace std;


void* worker(void* arg){
	MThread* threadObj = (MThread*)arg;
	threadObj->run();
	//threadObj->threadId = -1;
	threadObj->isDone=true;
	return NULL;
}

MThread::MThread(){
	threadId=-1;
	isDone=true;
}


void MThread::start(){
	pthread_create(&threadId,NULL,worker,(void*)this);
}

void MThread::waitForThread(){
	pthread_join(threadId,NULL);
}

MThread::~MThread(){
	if (!isDone){
		//kills the thread if exist
		pthread_cancel(threadId);
		printf("Thread was canceled\n");
	}
}

