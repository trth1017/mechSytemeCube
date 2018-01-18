/*
 * CCommComp.h
 *
 *  Created on: Dec 13, 2017
 *      Author: vmuser
 */

#ifndef CCOMMCOMP_H_
#define CCOMMCOMP_H_

#include "CContainer.h"
#include <iostream>
#include "IRunnable.h"
#include "CServer.h"

using namespace std;

extern CContainer CexchangeContainer;

class CCommcomp: public IRunnable
{
public:
	void run();
	void init();

private:
	SContent outputContent;
	CServer myServer;
};




#endif /* CCOMMCOMP_H_ */
