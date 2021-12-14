/*!******************************************************************************************
   File Name           : delay.h
   Author Name         : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Author email id     : ande9392@colorado.edu
   IDE used for Coding : MCUXpresso
   Compiler            : GCC
   Date                : 13th December 2021

   Info on Code obtained from other sources:

*******************************************************************************************/

#ifndef DELAY_H_
#define DELAY_H_

/*****************************************************************
 * generate delay according to input value
 *
 * Parameters:
 *   dly --> amount of delay
 *
 * Returns:
 *   none
 ****************************************************************/
extern void delay(uint32_t dlyTicks);

#endif /* DELAY_H_ */

/**************************************end of file******************************************/
