/*!******************************************************************************************
   File Name           : delay.c
   Author Name         : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Author email id     : ande9392@colorado.edu
   IDE used for Coding : MCUXpresso
   Compiler            : GCC
   Date                : 13th December 2021

   Info on Code obtained from other sources:

*******************************************************************************************/

#include <MKL25Z4.H>

/*****************************************************************
 * generate delay according to input value
 *
 * Parameters:
 *   dly --> amount of delay
 *
 * Returns:
 *   none
 ****************************************************************/
void delay (uint32_t dly)
{
  volatile uint32_t t;

	for (t=dly*10000; t>0; t--)
		;
}

/**************************************end of file******************************************/
