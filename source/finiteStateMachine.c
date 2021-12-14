/*!******************************************************************************************
   File Name           : finiteStateMachine.c
   Author Name         : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Author email id     : ande9392@colorado.edu
   IDE used for Coding : MCUXpresso
   Compiler            : GCC
   Date                : 13th December 2021

   Info on Code obtained from other sources:

*******************************************************************************************/
/*header files*/
#include "led.h"
#include <stdio.h>
#include <MKL25Z4.H>
#include <stdio.h>
#include <math.h>
#include "gpio_defs.h"
#include "i2c.h"
#include "mma8451.h"
#include "delay.h"
#include "touch.h"
#include "sysclock.h"
#include "uart.h"
#include <stdlib.h>
#include <stdbool.h>
#include "switch.h"
#include "finiteStateMachine.h"

/*enum*/
typedef enum
{
	init_peripherals = 0,
	user_input,
	calibrate_zero_degrees,
	compute_tilt_angle,
	illuminate_led
} state;

/*structure*/
typedef struct fsmElements
{
	state currentState;
	long inputAngle;
	float calibrateAngle;
	float measuredAngle;
	bool redLedOn;
	bool greenLedOn;
	bool blueLedOn;
} fsmParameters;

/**********************************************************************
 * accumulates the input characters fed over UART into a string
 *
 * Parameters:
 *   ipStrPtr --> pointer to input string that gets created
 *   size     --> the maximum size of input buffer
 *
 * Returns:
 *   void
 *********************************************************************/
void accumulateLine(char *ipStrPtr, int size)
{
	char ch;
	int i = 0;

	do
	{
		ch = getchar();

		/*!echo the character*/
		printf("%c",ch);

		/*!handle the backspace*/
		if((ch == '\b') && (i > 0))
		{
			printf(" ");
			printf("\b");
			i--;
		}
		else
		{
			/*!to store input characters for further parsing*/
			ipStrPtr[i] = ch;
			i++;
		}

	} while((ch != '\r') && (i < (size - 1)));

	/*append null termination character at the end of string*/
	ipStrPtr[i] = '\0';

	printf("\r\n");
}

/**********************************************************************
 * initialise all the peripherals necessary for digital angle gauge
 *
 * Parameters:
 *   fsm --> pointer to structure object containing fsm parameters
 *
 * Returns:
 *   void
 *********************************************************************/
static void handleInitPeripheralsState(fsmParameters *fsm)
{
	/*initialise peripherals*/
	rgbInit();
	touchInit();
	initSwitch();
	initializeGPIOInterrupt();

	setSwitchState(false);

	/*update the fsm state to that of next state*/
	fsm->currentState = user_input;
}

/**********************************************************************
 * obtain angle input from user
 *
 * Parameters:
 *    fsm --> pointer to structure object containing fsm parameters
 *
 * Returns:
 *   void
 *********************************************************************/
static void handleUserInputState(fsmParameters *fsm)
{
	int size = 100;
	char ipStr[size];
	char *ptr;

	printf("\r\nPlease input angle of your choice in degrees(0-180 deg): \r\n");
	accumulateLine(ipStr, size);

	/*converting the input value in string to integer type*/
	fsm->inputAngle = strtol(ipStr, &ptr, 10);
	printf("the input angle is %ld degrees\r\n", fsm->inputAngle);

	setSwitchState(false);

	/*update the fsm state to that of next state*/
	fsm->currentState = calibrate_zero_degrees;
}

/**********************************************************************
 * calibrate for zero degree position from user via touch
 *
 * Parameters:
 *    fsm --> pointer to structure object containing fsm parameters
 *
 * Returns:
 *   void
 *********************************************************************/
static void handleCalibrateZeroDegreesState(fsmParameters *fsm)
{
	static int touchRetVal = 0;
	static bool printedOnce = false;

	/*in order to print these logs only once*/
	if(false == printedOnce)
	{
		printf("\r\nplace the digital angle gauge at your convenience \r\n");
		printf("calibrate for zero degree reference by touch on capacitive slider\r\n");
		printedOnce = true;
	}

	/*checking if touch was detected*/
	if(touchRetVal < 100)
	{
		touchRetVal = touchScanLH();
	}
	else
	{
		/*read angle at the instance of calibration here*/
		read_full_xyz();
		fsm->calibrateAngle = computeTiltAngle();
		printf("zero reference angle i.e angle at calibration = %d degrees\r\n", (int)fsm->calibrateAngle);

		/*updating the fsm state to next state*/
		fsm->currentState = compute_tilt_angle;

		/*resetting the static variables for next angle input*/
		touchRetVal = 0;
		printedOnce = false;
	}
}

/**********************************************************************
 * compute the tilt angle
 *
 * Parameters:
 *    fsm --> pointer to structure object containing fsm parameters
 *
 * Returns:
 *   void
 *********************************************************************/
static void handleComputeTiltAngleState(fsmParameters *fsm)
{
	/*read acc x y and z values*/
	read_full_xyz();

	/*to compute the current tilt  angle*/
	fsm->measuredAngle = computeTiltAngle();

	/*calculate relative angle wrt angle at calibration*/
	float relativeAngle = fsm->measuredAngle - fsm->calibrateAngle;

	printf("Tilt angle = %d degrees\r\n", (int)relativeAngle);

	/*according to present angle of the board, illuminate respective LEDs*/

	/*
	 * Thus, illuminate Red led if current angle is lesser than that
	 * of user input angle
	 */
	if((int)relativeAngle < fsm->inputAngle)
	{
		fsm->redLedOn = true;
		fsm->greenLedOn = false;
		fsm->blueLedOn = false;
		printf("\r\nincrease the angle of gauge\r\n");
		fsm->currentState = illuminate_led;
	}
	/*
	 * illuminate Green led if current angle is equals that
	 * of user input angle
	 */
	else if((int)relativeAngle == fsm->inputAngle)
	{
		fsm->redLedOn = false;
		fsm->greenLedOn = true;
		fsm->blueLedOn = false;
		printf("\r\nhold on to current angle of gauge and press switch\r\n");
		fsm->currentState = illuminate_led;
	}
	/*
	 * illuminate Blue led if current angle is greater than that
	 * of user input angle
	 */
	else
	{
		fsm->redLedOn = false;
		fsm->greenLedOn = false;
		fsm->blueLedOn = true;
		printf("\r\ndecrease the angle of gauge\r\n");
		fsm->currentState = illuminate_led;
	}
}

/**********************************************************************
 * to illuminate LED on baord according to angle comparison
 *
 * Parameters:
 *    fsm --> pointer to structure object containing fsm parameters
 *
 * Returns:
 *   void
 *********************************************************************/
static void handleIlluminateLedState(fsmParameters *fsm)
{
	/*turn on ONLY Red led*/
	if(true == fsm->redLedOn)
	{
		turnOffBlueLed();
		turnOffGreenLed();
		turnOnRedLed();
	}
	/*turn on ONLY Green led*/
	else if (true == fsm->greenLedOn)
	{
		turnOffBlueLed();
		turnOffRedLed();
		turnOnGreenLed();

		/*
		 * If the switch is pressed, implies the user is satisfied with
		 * current angle of board and we can again resume with new input angle
		 * for future computation
		 */
		if(true == getSwitchState())
		{
			printf("Switch input detected!!!\r\n");
			fsm->currentState = user_input;
			setSwitchState(false);
			return;
		}
	}
	/*turn on ONLY Blue led*/
	else if(true == fsm->blueLedOn)
	{
		turnOffGreenLed();
		turnOffRedLed();
		turnOnBlueLed();
	}

	/*after glowing led, get back to computing tilt angle*/
	fsm->currentState = compute_tilt_angle;
}

/**********************************************************************
 * finite state machine for handling different states of digital
 * angle gauge
 *
 * Parameters:
 *    void
 *
 * Returns:
 *   void
 *********************************************************************/
void fsmLoop()
{
	fsmParameters fsm;

	/*intialise the fsm variables*/
	fsm.currentState = init_peripherals;
	fsm.calibrateAngle = 0;
	fsm.measuredAngle = 0;
	fsm.blueLedOn = false;
	fsm.greenLedOn = false;
	fsm.redLedOn = false;

	while(1)
	{
		switch(fsm.currentState)
		{
			case init_peripherals: 			handleInitPeripheralsState(&fsm);
											break;

			case user_input:				handleUserInputState(&fsm);
											break;

			case calibrate_zero_degrees:	handleCalibrateZeroDegreesState(&fsm);
											break;

			case compute_tilt_angle:		handleComputeTiltAngleState(&fsm);
											break;

			case illuminate_led :			handleIlluminateLedState(&fsm);
											break;
		}

		delay(100);
	}
}

/**************************************end of file******************************************/
