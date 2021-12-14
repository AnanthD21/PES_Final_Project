/*!******************************************************************************************
   File Name           : GPIO_defs.h
   Author Name         : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Author email id     : ande9392@colorado.edu
   IDE used for Coding : MCUXpresso
   Compiler            : GCC
   Date                : 13th December 2021

   Info on Code obtained from other sources:

*******************************************************************************************/

#ifndef GPIO_DEFS_H_
#define GPIO_DEFS_H_

// basic light switch
#define LED1_POS (1)	// on port A
#define LED2_POS (2)	// on port A
#define SW1_POS (5)		// on port A

#define MASK(x) (1UL << (x))

// Speaker output
#define SPKR_POS (0) 	// on port C

#endif /* GPIO_DEFS_H_ */

/**************************************end of file******************************************/
