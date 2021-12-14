/*!******************************************************************************************
   File Name           : switch.h
   Author Name         : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Author email id     : ande9392@colorado.edu
   IDE used for Coding : MCUXpresso IDE
   Compiler            : GCC
   Date                : 13th December 2021
*******************************************************************************************/

#ifndef SWITCH_H_
#define SWITCH_H_

/***************************************************************************
 * provides the status of GPIO switch
 *
 * Parameters:
 *   void
 *
 * Returns: bool depending on status of GPIO switch
 **************************************************************************/
bool getSwitchState();

/***************************************************************************
 * sets the status of GPIO switch. This has been used to reset the static
 * global variable buttonPressedForCrossWalk, in order to accomodate new
 * crosswalk requests
 *
 * Parameters:
 *   bool --> either make switch closed or open
 *
 * Returns: void
 **************************************************************************/
void setSwitchState(bool input);

/***************************************************************************
 * intialises the 3rd pin of PORTD in order to use it as input GPIO pin
 * in interrupt mode
 *
 * Parameters:
 *   void
 *
 * Returns: void
 **************************************************************************/
void initSwitch();

/***************************************************************************
 * Enables the PORTD GPIO interrupt
 *
 * Parameters:
 *   void
 *
 * Returns: void
 **************************************************************************/
void initializeGPIOInterrupt();

#endif /* SWITCH_H_ */

/**************************************end of file******************************************/
