/*
 * main.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: vmuser
 */
#include <iostream>
#include "CCommComp.h"
#include "CControlComp.h"
#include "CContainer.h"
#include "CThread.h"

using namespace std;

CContainer CexchangeContainer;

int main()
{
	CCommcomp 		myCommunicator;
	CControlComp 	myController;

	CThread communicatorThread(&myCommunicator,CThread::PRIORITY_NORM);
	CThread controllerThread(&myController,CThread::PRIORITY_NORM);

	communicatorThread.start();
	controllerThread.start();



	communicatorThread.join();
//	controllerThread.join();


	return 0;
}
