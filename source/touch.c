 /*!******************************************************************************************
   File Name           :  touch.c
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
#include "touch.h"
#include <stdio.h>

//variation of the capacitance from 90 to 700
#define TOUCH_OFFSET 550  // offset value to be subtracted
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)//macro for extracting the count from data register

/***************************************************************************
 * initialise the touch on board
 *
 * Parameters:
 *   void
 *
 * Returns: void
 **************************************************************************/
void touchInit()
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // enabling the clock

	TSI0->GENCS = TSI_GENCS_MODE(0u) | //operating in non-noise mode
								TSI_GENCS_REFCHRG(0u) | //reference oscillator charge and discharge value 500nA
								TSI_GENCS_DVOLT(0u) | //oscillator voltage rails set to default
								TSI_GENCS_EXTCHRG(0u) | //electrode oscillator charge and discharge value 500nA
								TSI_GENCS_PS(0u) |  // frequency clcok divided by one
								TSI_GENCS_NSCN(31u) | //scanning the electrode 32 times
								TSI_GENCS_TSIEN_MASK | //enabling the TSI module
								TSI_GENCS_EOSF_MASK; // writing one to clear the end of scan flag
}

/***************************************************************************
 * scan the touch on board
 *
 * Parameters: returns the scanned value devoid of offset
 *
 * Returns: void
 **************************************************************************/
int touchScanLH(void)
{
	unsigned int scan = 0;
	TSI0->DATA = 	TSI_DATA_TSICH(10u);
	TSI0->DATA |= TSI_DATA_SWTS_MASK; //software trigger to start the scan
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )) // waiting for the scan to complete 32 times
	;
	scan = TOUCH_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; //writing one to clear the end of scan flag
	return scan- TOUCH_OFFSET;
}

/**************************************end of file******************************************/
