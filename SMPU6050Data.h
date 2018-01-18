/**
 * @author	Michael Meindl
 * @date	5.12.2016
 * @brief	Structure to hold the relevant MPU-Values
 */
#ifndef SMPU6050DATA_H
#define SMPU6050DATA_H
#include "Global.h"

struct SMPU6050Data
{
public:
	Int16 mX__dd;		//! Sensor  X-Acceleration []
	Int16 mY__dd;		//! Sensor  Y-Acceleration []
	Int16 mPhi__d;		//! Sensor  Z-Angular Velocity []
	Int16 mPadding;
};

struct SMPU6050_calibrated_data
{
public:
	double mX_dd_calib;
	double mY_dd_calib;
	double mPhi__d_calib;
};

struct SMPU6050_calculated_data
{
public:
	double Phi_calc;
};


struct SMPU6050_filtered_data
{
public:
	double Phi_filter_old;
	double Phi_filter;
};


#endif
