 /*!******************************************************************************************
   File Name           :  touch.h
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

#ifndef TOUCH_H_
#define TOUCH_H_

/***************************************************************************
 * initialise the touch on board
 *
 * Parameters:
 *   void
 *
 * Returns: void
 **************************************************************************/
void touchInit();

/***************************************************************************
 * scan the touch on board
 *
 * Parameters: returns the scanned value devoid of offset
 *
 * Returns: void
 **************************************************************************/
int touchScanLH(void);

#endif /* TOUCH_H_ */

/**************************************end of file******************************************/
