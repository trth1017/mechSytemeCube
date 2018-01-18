/*
 * CControlComp.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: vmuser
 */

#include "CControlComp.h"

CControlComp::CControlComp():mx1(0.00059961),cx1(-0.1879), mx2(0.00059562),cx2(- 0.0477), my1(0.00059779), cy1(0.1157), my2(0.00059863), cy2(0.0445)\
							,rs1(0.14), rs2(0.061), adcm(4.836), adcc(- 9854.9826  +18), mGyro(-0.00106) ,alpha_filter(0.98), T_filter(0.02)\
							, K1(1.488), K2(0.1093), K3(0.0004)
{
	//Init Filter with 0
	mpu_cube_filter.Phi_filter_old = 0;
	torque_test = 0;
	adc_cube = 0;
	adc_cube_calib = 0;
	//Phi Offset found out with debugger
	Phi_offset = -0.01365;
}

void CControlComp::init()
{
//	cubeHardware.enableMotor();
//	cubeHardware.setTorque(-0.0083*2);
}

void CControlComp::run()
{

	struct timeval timebegin, timemid, timeend;
	time_t seconds,useconds;



	while(true)
	{

		gettimeofday(&timebegin, (struct timezone *)0);

		cubeHardware.fetchValues(adc_cube, mpu_cube, mpu2_cube);

		gettimeofday(&timemid, (struct timezone *)0);
		seconds = timemid.tv_sec - timebegin.tv_sec;
		useconds = timemid.tv_usec - timebegin.tv_usec;
		useconds += 1000*1000*seconds;

//		cout<<"fetch dauert: "<<useconds<<" usec"<<endl;



		//Write Data into CCotainer
		CexchangeContainer.writeADCValue(adc_cube);
		CexchangeContainer.writeTorqueValue(torque_test);
		CexchangeContainer.writeSensor1Data(mpu_cube);
		CexchangeContainer.writeSensor2Data(mpu2_cube);
		CexchangeContainer.writeStateData(vectordata_test);

		//calibrate
		CControlComp::calibrate();

		//Calculate
		CControlComp::calculate();

		//Filter
		CControlComp::filter();

		//Regler
		CControlComp::regler();

		//Set Motor Values
		CControlComp::motor();

		//Give Semaphore to signal Sensorvalues are ready to read
		CexchangeContainer.signalReader();



		gettimeofday(&timeend, (struct timezone *)0);
		seconds = timeend.tv_sec - timebegin.tv_sec;
		useconds = timeend.tv_usec - timebegin.tv_usec;
		useconds += 1000*1000*seconds;



//		cout<<"Zyklus dauert: "<<useconds<<" usec"<<endl;

		//usleep(20000-useconds);
		//usleep(10000-useconds);
		usleep(20000- useconds);

	}


}

CControlComp::~CControlComp()
{
	cubeHardware.disableMotor();
}




void CControlComp::calibrate()
{
	mpu_cube_calib.mX_dd_calib = mx1*mpu_cube.mX__dd + cx1;
	mpu_cube_calib.mY_dd_calib = my1*mpu_cube.mY__dd + cy1;
	mpu2_cube_calib.mX_dd_calib = mx2*mpu2_cube.mX__dd + cx2;
	mpu2_cube_calib.mY_dd_calib = my2*mpu2_cube.mY__dd + cy2;

	adc_cube_calib = adcm*adc_cube + adcc;

	mpu_cube_calib.mPhi__d_calib = mpu_cube.mPhi__d*(mGyro);//(-0.000018497*8.0);
	mpu2_cube_calib.mPhi__d_calib = mpu2_cube.mPhi__d*(mGyro);//(-0.000018497*8.0);
}


void CControlComp::calculate()
{
	double alpha_calc =  rs1 / rs2;		//rs1/rs2
	mpu_cube_calc.Phi_calc =(-1)*atan((mpu_cube_calib.mX_dd_calib - alpha_calc*mpu2_cube_calib.mX_dd_calib)/\
								(mpu_cube_calib.mY_dd_calib - alpha_calc*mpu2_cube_calib.mY_dd_calib)) + Phi_offset;

}



void CControlComp::filter()
{
	double phi__d_Gyro = (mpu_cube_calib.mPhi__d_calib + mpu2_cube_calib.mPhi__d_calib) / 2.0;

	mpu_cube_filter.Phi_filter = alpha_filter*(mpu_cube_filter.Phi_filter_old + T_filter * phi__d_Gyro) + (1.0-alpha_filter) * mpu_cube_calc.Phi_calc;
	mpu_cube_filter.Phi_filter_old = mpu_cube_filter.Phi_filter;

	cout<<"Phi filtered: "<<mpu_cube_filter.Phi_filter*180/3.141;
}

void CControlComp::regler()
{


	//Reglerparameter
//	double K1 = 1.488;//0.881161311781517;
//	double K2 = 0.1093;//0.077876495055501;
//	double K3 = 0.0004;//0.0002000781698380463;

	double phi__d_Gyro = (mpu_cube_calib.mPhi__d_calib + mpu2_cube_calib.mPhi__d_calib) / 2;

	//use phi, phi_d, psi_d
	cube_control_param.mControlsTorque = K1*mpu_cube_filter.Phi_filter + K2*phi__d_Gyro + K3*adc_cube_calib*2*3.141/60;

	cout<<"\tPhi_d_Gyro: "<<phi__d_Gyro;
	cout<<"\tPsi_d: "<<adc_cube_calib*2*3.141/60;
	cout<<"\tDrehzahl: "<<adc_cube_calib;
	cout<<"\tDrehmoment: "<<cube_control_param.mControlsTorque<<endl;

}

void CControlComp::motor()
{
	//Wenn Cube zwischen +- 10 Grad
	if ((mpu_cube_filter.Phi_filter * 180 / (3.141)) > -10 && (mpu_cube_filter.Phi_filter * 180 / (3.141)) < 10)
	{
			cubeHardware.enableMotor();
			cubeHardware.setTorque(-cube_control_param.mControlsTorque);
	}
	else{
		cubeHardware.disableMotor();
	}
}


