/*
 * CControlComp.h
 *
 *  Created on: Dec 13, 2017
 *      Author: vmuser
 */

#ifndef CCONTROLCOMP_H_
#define CCONTROLCOMP_H_

#include "CContainer.h"
#include "IRunnable.h"
#include "CBBBHardware.h"
#include "SParameter.h"
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

using namespace std;

extern CContainer CexchangeContainer;

class CControlComp : public IRunnable
{
public:
	void run();
	void init();
	CControlComp();
	~CControlComp();

	void calibrate();
	void calculate();
	void filter();
	void regler();
	void motor();

private:
	CBBBHardware cubeHardware;
	UInt16 adc_cube;
	float torque_test;
	SMPU6050Data mpu_cube;
	SMPU6050Data mpu2_cube;
	SStateVectorData vectordata_test;

//	SParameter cube_Parameter;

	SMPU6050_calibrated_data mpu_cube_calib;
	SMPU6050_calibrated_data mpu2_cube_calib;
	double adc_cube_calib;

	SMPU6050_calculated_data mpu_cube_calc;

	SMPU6050_filtered_data mpu_cube_filter;

	SControlParameter cube_control_param;

	//Ausgleichsgeraden Parameter
	const double mx1,cx1, mx2,cx2, my1, cy1, my2, cy2;
	const double adcm, adcc;
	//Abstaende der Gyros
	const double rs1, rs2;
	const double mGyro;

	//Filterparam
	const double alpha_filter;
	const double T_filter;

	//Contorller param
	const double K1, K2, K3;

	double Phi_offset;

};




#endif /* CCONTROLCOMP_H_ */
