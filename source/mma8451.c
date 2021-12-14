/*!******************************************************************************************
  File Name           :  mma8451.c
  Author Name         : Ananth Deshpande
                        Professional Masters in Embedded Systems
                        Fall 2021, UCB.
  Author email id     : ande9392@colorado.edu
  IDE used for Coding : MCUXpresso IDE
  Compiler            : GCC
  Date                : 13th December 2021

  Info on Code obtained from other sources:

     1.Chapter 8 of Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers
   by Alexander Dean

*******************************************************************************************/

/*header files*/
#include <MKL25Z4.H>
#include "mma8451.h"
#include "i2c.h"
#include "delay.h"
#include <math.h>
#include <stdio.h>

/*global variables*/
int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

/*mma data ready*/
extern uint32_t DATA_READY;

/*macros*/
#define ON 1
#define OFF 0
#define ACC_X_REF 181
#define ACC_Y_REF 255
#define ACC_Z_REF 1680
#define STANDBY_MODE 0X00
#define SELF_TEST_MODE 0X80
#define ACTIVE_MODE 0X01
#define REG_CTRL1  0x2A
#define REG_CTRL2  0x2B

/***************************************************************************
* initialize mma8451 sensor
*
* Parameters:
*   void
*
* Returns: success value
**************************************************************************/
int init_mma()
{
	/* set active mode, 14 bit samples and 800 Hz ODR */
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/***************************************************************************
* read acc values from mma8451 sensor
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void read_full_xyz()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

	/* Read five bytes in repeated mode */
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}
	/* Read last byte ending repeated mode */
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	/* Align for 14 bits */
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;

}

/***************************************************************************
* read acc values from mma8451 sensor
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void read_xyz(void)
{
	/*sign extend byte to 16 bits - need to cast to signed since function*/
	/*returns uint8_t which is unsigned*/
	acc_X = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);
	delay(100);
	acc_Y = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);
	delay(100);
	acc_Z = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);
}

/***************************************************************************
* compute tilt angle using accelero values
*
* Parameters:
*   void
*
* Returns: the tilt angle computed
**************************************************************************/
float computeTiltAngle(void)
{
	float tilt = 0;
	float resultant = 0;

	float ax = acc_X/COUNTS_PER_G,
				ay = acc_Y/COUNTS_PER_G,
				az = acc_Z/COUNTS_PER_G;

	roll = atan2(ay, az)*180/M_PI;
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;

	resultant = sqrt((ax * ax) + (ay * ay) + (az * az));

	tilt = acos(az / resultant) * 180/M_PI;

	return tilt;
}

/***************************************************************************
* Verify accelerometer readings.
*
* Parameters:
*   state --> to enable or disable selt_test mode
*
* Returns: void
**************************************************************************/
void self_test_enable(int state)
{
	if(state)
	{
		i2c_write_byte(MMA_ADDR, REG_CTRL1, STANDBY_MODE); /*Standby mode*/
		delay(5);
		i2c_write_byte(MMA_ADDR, REG_CTRL2, SELF_TEST_MODE); /*Self-test mode*/
		delay(5);
		i2c_write_byte(MMA_ADDR, REG_CTRL1, ACTIVE_MODE); /*Active mode*/
		delay(5);
	}
	else if(!state)
	{
		i2c_write_byte(MMA_ADDR, REG_CTRL1, STANDBY_MODE); /*Standby mode*/
		delay(5);
		i2c_write_byte(MMA_ADDR, REG_CTRL2, STANDBY_MODE); /*Coming out of Self-test mode*/
		delay(5);
		i2c_write_byte(MMA_ADDR, REG_CTRL1, ACTIVE_MODE); /*Active mode*/
		delay(5);
	}
}

/***************************************************************************
* Verify accelerometer readings.
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void self_test(void)
{
	printf("\n\r executing accelerometer self test");
	int acc_x_values[10], acc_y_values[10], acc_z_values[10];
	int acc_x_sum = 0, acc_y_sum = 0, acc_z_sum = 0;

	/*obtain 10 samples to verify our output*/
	for(int i = 0; i < 10; i++)
	{
		/*Switch on Self test mode*/
		self_test_enable(ON);
		read_full_xyz();
		acc_x_values[i] = acc_X;
		acc_y_values[i] = acc_Y;
		acc_z_values[i] = acc_Z;

		/*Switch off Self test mode*/
		self_test_enable(OFF);
		read_full_xyz();
		acc_x_values[i] -= acc_X;
		acc_y_values[i] -= acc_Y;
		acc_z_values[i] -= acc_Z;

		acc_x_sum += acc_x_values[i];
		acc_y_sum += acc_y_values[i];
		acc_z_sum += acc_z_values[i];
	}

	/*Compare the average with the accelerometer reference values along x, y and z axes*/
	if((acc_x_sum/10 > ACC_X_REF) && (acc_y_sum/10 > ACC_Y_REF) && (acc_z_sum/10 > ACC_Z_REF))
	{
		printf("\n\rAccelerometer Self test has passed.\r\n");
	}
	else
	{
		printf("\n\rAccelerometer Self test has failed.\r\n");
	}
}
/**************************************end of file******************************************/
