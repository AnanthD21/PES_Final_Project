/*!******************************************************************************************
  File Name           :  led.c
  Author Name         : Ananth Deshpande
                        Professional Masters in Embedded Systems
                        Fall 2021, UCB.
  Author email id     : ande9392@colorado.edu
  IDE used for Coding : MCUXpresso IDE
  Compiler            : GCC
  Date                : 13th December 2021

  Info on Code obtained from other sources:

  https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
  https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense/TSI

  above links have been referred to write below code.

*******************************************************************************************/

/*header files*/
#include "MKL25Z4.h"
#include "led.h"
#include <stdbool.h>
#include <stdio.h>
#include "delay.h"

/*Macros*/
#define MASK(x) (1UL << (x))
#define RED_LED_SHIFT   (18)	/* on port B */
#define GREEN_LED_SHIFT (19)	/* on port B */
#define BLUE_LED_SHIFT  (1)		/* on port D */

/* global flags*/
bool redLedOn = false;
bool greenLedOn = false;
bool blueLedOn = false;

/***************************************************************************
* initialize RGB leds on the board
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void rgbInit()
{
	/* Enable clock to Port B and Port D */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	/* Make 3 pins GPIO */
	PORTB->PCR[RED_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_SHIFT] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_SHIFT] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_SHIFT] |= PORT_PCR_MUX(1);
}

/***************************************************************************
* turn on the red led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOnRedLed()
{
	static bool setOutputPort = false;

	/*!red led is located on Port B*/
	if(false == setOutputPort)
	{
		PTB->PDDR |= MASK(RED_LED_SHIFT);
		setOutputPort = true;
	}
	PTB->PCOR = MASK(RED_LED_SHIFT);
}

/***************************************************************************
* turn off the red led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffRedLed()
{
	/*!
	 since it is active high logic, setting the register turns off
	 the respective Led
	 */
	PTB->PSOR = MASK(RED_LED_SHIFT);
}

/***************************************************************************
* turn on the Green led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOnGreenLed()
{
	static bool setOutputPort = false;

	/*!green led is located on Port B*/
	if(false == setOutputPort)
	{
		PTB->PDDR |= MASK(GREEN_LED_SHIFT);
		setOutputPort = true;
	}
	PTB->PCOR = MASK(GREEN_LED_SHIFT);
}

/***************************************************************************
* turn off the green led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffGreenLed()
{
	PTB->PSOR = MASK(GREEN_LED_SHIFT);
}

/***************************************************************************
* turn on the blue led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOnBlueLed()
{
	static bool setOutputPort = false;

	/*!blue led is located on Port D*/
	if(false == setOutputPort)
	{
		PTD->PDDR |= MASK(BLUE_LED_SHIFT);
		setOutputPort = true;
	}
	PTD->PCOR = MASK(BLUE_LED_SHIFT);
}

/***************************************************************************
* turn off the blue led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffBlueLed()
{
	PTD->PSOR = MASK(BLUE_LED_SHIFT);
}

/***************************************************************************
* turn on the white(Red, green and blue) led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOnWhiteLed()
{
	/*white led is combination of Red green and blue colors*/
	turnOnRedLed();
	turnOnGreenLed();
	turnOnBlueLed();
}

/***************************************************************************
* turn off the white led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffWhiteLed()
{
	turnOffRedLed();
	turnOffGreenLed();
	turnOffBlueLed();
}

/***************************************************************************
* test rgb leds according to the pattern mentioned in assignment 3
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void testRgbLed()
{
	turnOnRedLed();
	delay(FIVEHUNDREDMS);
	turnOffRedLed();
	delay(HUNDREDMS);

	turnOnGreenLed();
	delay(FIVEHUNDREDMS);
	turnOffGreenLed();
	delay(HUNDREDMS);

	turnOnBlueLed();
	delay(FIVEHUNDREDMS);
	turnOffBlueLed();
	delay(HUNDREDMS);

	turnOnWhiteLed();
	delay(HUNDREDMS);
	turnOffWhiteLed();
	delay(HUNDREDMS);

	turnOnWhiteLed();
	delay(HUNDREDMS);
	turnOffWhiteLed();
	delay(HUNDREDMS);
}

/***************************************************************************
* turn on or off red green or blue leds depending on the flags
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void driveLed()
{

	if(true == redLedOn)
	{
		turnOnRedLed();
	}
	else
	{
		turnOffRedLed();
	}

	if(true == greenLedOn)
	{
		turnOnGreenLed();
	}
	else
	{
		turnOffGreenLed();
	}

	if(true == blueLedOn)
	{
		turnOnBlueLed();
	}
	else
	{
		turnOffBlueLed();
	}
}

/***************************************************************************
* turn off all the leds
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffAllLeds()
{
  redLedOn = false;
  greenLedOn = false;
  blueLedOn = false;
  driveLed();
}

/**************************************end of file******************************************/
