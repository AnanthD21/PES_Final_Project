/*!******************************************************************************************
  File Name           :  mma8451.h
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

#ifndef MMA8451_H_
#define MMA8451_H_

#include <stdint.h>

#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)

extern float roll, pitch;
extern int16_t acc_X, acc_Y, acc_Z;

/***************************************************************************
* initialize mma8451 sensor
*
* Parameters:
*   void
*
* Returns: success value
**************************************************************************/
int init_mma(void);

/***************************************************************************
* read acc values from mma8451 sensor
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void read_full_xyz(void);

/***************************************************************************
* read acc values from mma8451 sensor
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void read_xyz(void);

/***************************************************************************
* compute tilt angle using accelero values
*
* Parameters:
*   void
*
* Returns: the tilt angle computed
**************************************************************************/
float computeTiltAngle(void);

/***************************************************************************
* Verify accelerometer readings.
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void self_test(void);

#endif /* MMA8451_H_ */

/**************************************end of file******************************************/
