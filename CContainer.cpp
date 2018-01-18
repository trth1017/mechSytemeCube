/**
 * @file	CContainer.cpp
 * @author	Michael Meindl
 * @date	5.12.2016
 * @brief	Method definitions for the container.
 */
#include "CContainer.h"


CContainer::CContainer() : mReadSem(false, false)
{
	mContent.mADCValue = 0;
	mContent.mMotorTorque = 0.0;
	mContent.mPadding = 0;
	mContent.mSensor1Data.mPadding = 0;
	mContent.mSensor1Data.mPhi__d = 0;
	mContent.mSensor1Data.mX__dd = 0;
	mContent.mSensor1Data.mY__dd = 0;

	mContent.mSensor2Data.mPadding = 0;
	mContent.mSensor2Data.mPhi__d = 0;
	mContent.mSensor2Data.mX__dd = 0;
	mContent.mSensor2Data.mY__dd = 0;

	mContent.mStateData.mPhi_A = 0.0;
	mContent.mStateData.mPhi_C = 0.0;
	mContent.mStateData.mPhi_G = 0.0;
	mContent.mStateData.mPhi__d = 0.0;
	mContent.mStateData.mPsi__d = 0.0;
}
bool CContainer::getContent(bool waitForever,
							SContent& content)
{
	if(mReadSem.take(waitForever))
	{
		content = mContent;
		return true;
	}
	return false;
}
void CContainer::signalReader()
{
	mReadSem.give();
}
bool CContainer::writeADCValue(const UInt16 adcValue)
{
	mContent.mADCValue = adcValue;
	return true;
}
bool CContainer::writeTorqueValue(const float torque)
{
	mContent.mMotorTorque = torque;
	return true;
}
bool CContainer::writeSensor1Data(const SMPU6050Data& sensorData)
{
	mContent.mSensor1Data = sensorData;
	return true;
}
bool CContainer::writeSensor2Data(const SMPU6050Data& sensorData)
{
	mContent.mSensor2Data = sensorData;
	return true;
}
bool CContainer::writeStateData(const SStateVectorData& stateValue)
{
	mContent.mStateData = stateValue;
	return true;
}
