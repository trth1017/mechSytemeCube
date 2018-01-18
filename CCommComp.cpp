/*
 * CCommComp.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: vmuser
 */


#include "CCommComp.h"


void CCommcomp::run()
{
	for(int i = 0; i<1000; i++)
	{
		CexchangeContainer.getContent(true, outputContent);
		myServer.transmitMessage(outputContent);
	}


//	while(true)
//	{
//
//		if(CexchangeContainer.getContent(true, outputContent)){
//			cout<<" ADC Value: "<<outputContent.mADCValue\
//				<<"\n Torque Value: "<<outputContent.mMotorTorque	\
//				<<"\n Sensor1 Padding: "<<outputContent.mSensor1Data.mPadding\
//				<<"\n Sensor1 mPhi__d: "<<outputContent.mSensor1Data.mPhi__d\
//				<<"\n Sensor1 mX__dd: "<<outputContent.mSensor1Data.mX__dd\
//				<<"\n Sensor1 mY__dd: "<<outputContent.mSensor1Data.mY__dd\
//				<<"\n Sensor2 Padding: "<<outputContent.mSensor2Data.mPadding\
//				<<"\n Sensor2 mPhi__d: "<<outputContent.mSensor2Data.mPhi__d\
//				<<"\n Sensor2 mX__dd: "<<outputContent.mSensor2Data.mX__dd\
//				<<"\n Sensor2 mY__dd: "<<outputContent.mSensor2Data.mY__dd\
//				<<"\n StateData.mPhi_A: "<<outputContent.mStateData.mPhi_A\
//				<<"\n StateData.mPhi_C: "<<outputContent.mStateData.mPhi_C\
//				<<"\n StateData.mPhi_G: "<<outputContent.mStateData.mPhi_G\
//				<<"\n StateData.mPhi__d: "<<outputContent.mStateData.mPhi__d\
//				<<"\n StateData.mPsi__d: "<<outputContent.mStateData.mPsi__d\
//				<<"\n––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"
//				<<endl;
//		}
//		myServer.transmitMessage(outputContent);


}

void CCommcomp::init()
{
	myServer.init();
	cout<<"Wait for client connect..."<<endl;
	myServer.waitForClient();
	cout<<"Connected with client"<<endl;
}
