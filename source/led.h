/*!******************************************************************************************
  File Name           :  led.h
  Author Name         : Ananth Deshpande
                        Professional Masters in Embedded Systems
                        Fall 2021, UCB.
  Author email id     : ande9392@colorado.edu
  IDE used for Coding : MCUXpresso IDE
  Compiler            : GCC
  Date                : 13th December 2021

*******************************************************************************************/

#ifndef LED_H_
#define LED_H_

/*Macros*/
#define HUNDREDMS       100
#define FIVEHUNDREDMS   500
#define THOUSANDMS      1000
#define TWOTHOUSANDMS   2000
#define THREETHOUSANDMS 3000

/***************************************************************************
* initialise RGB leds on the board
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void rgbInit();

/***************************************************************************
* turnon the red led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOnRedLed();

/***************************************************************************
* turnoff the red led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffRedLed();

/***************************************************************************
* turnon the green led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOnGreenLed();

/***************************************************************************
* turnoff the green led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffGreenLed();

/***************************************************************************
* turnon the blue led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOnBlueLed();

/***************************************************************************
* turnoff the blue led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffBlueLed();

/***************************************************************************
* turnon the white led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOnWhiteLed();

/***************************************************************************
* turnoff the white led
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffWhiteLed();

/***************************************************************************
* test rgb leds according to the pattern mentioned in assignment 3
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void testRgbLed();

/***************************************************************************
* turn on or off red green or blue leds depending on the flags
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void driveLed();

/***************************************************************************
* turn off all the leds
*
* Parameters:
*   void
*
* Returns: void
**************************************************************************/
void turnOffAllLeds();

#endif /* LED_H_ */

/**************************************end of file******************************************/
