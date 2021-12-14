/*!******************************************************************************************
   File Name           : switch.c
   Author Name         : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Author email id     : ande9392@colorado.edu
   IDE used for Coding : MCUXpresso IDE
   Compiler            : GCC
   Date                : 13th December 2021

   Info on Code obtained from other sources:

   1. https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
   2. https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense/TSI
   3. Chapter 7 of Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers
      by Alexander Dean
   4. GPIO part 1 and part 2 slides from Professor Howdy.

   above links have been referred to write below code.

*******************************************************************************************/
/*header files*/
#include "stdbool.h"
#include "switch.h"
#include "MKL25Z4.h"

/* SWITCH is connected to PORT D, pin 3*/
#define SWITCH_GPIO_PORT GPIOD
#define SWITCH_PIN_CTRL_REG PORTD->PCR[SWITCH_PIN]
#define SWITCH_SCGC5_MASK SIM_SCGC5_PORTD_MASK
#define SWITCH_PIN 3
#define MASK(x) (1UL << (x))
#define INTERRUPT_WHEN_ZERO 8

/*static global variables*/
static bool buttonPressedForCrossWalk = false;

/***************************************************************************
 * provides the status of GPIO switch
 *
 * Parameters:
 *   void
 *
 * Returns: bool depending on status of GPIO switch
 **************************************************************************/
bool getSwitchState()
{
	return buttonPressedForCrossWalk;
}

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
void setSwitchState(bool input)
{
	buttonPressedForCrossWalk = input;
}

/***************************************************************************
 * intialises the 3rd pin of PORTD in order to use it as input GPIO pin
 * in interrupt mode
 *
 * Parameters:
 *   void
 *
 * Returns: void
 **************************************************************************/
void initSwitch()
{
  SIM->SCGC5 |= SWITCH_SCGC5_MASK;
  SWITCH_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;
  SWITCH_PIN_CTRL_REG |= PORT_PCR_MUX(1);
  SWITCH_PIN_CTRL_REG |= PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_IRQC(10);
  SWITCH_GPIO_PORT->PDDR &= ~(1 << SWITCH_PIN);
  SWITCH_PIN_CTRL_REG |= PORT_PCR_IRQC(INTERRUPT_WHEN_ZERO);
}

/***************************************************************************
 * Enables the PORTD GPIO interrupt
 *
 * Parameters:
 *   void
 *
 * Returns: void
 **************************************************************************/
void initializeGPIOInterrupt()
{
	PORTD->ISFR = 0xFFFFFFFF;
	NVIC_SetPriority(PORTD_IRQn, 2);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);

	__enable_irq();
}

/***************************************************************************
 * PORTD interrupt handler
 *
 * Parameters:
 *   void
 *
 * Returns: void
 **************************************************************************/
void PORTD_IRQHandler(void)
{
	if((PORTD->ISFR & MASK(SWITCH_PIN)))
	{
		buttonPressedForCrossWalk = true;
	}

	PORTD->ISFR = 0xFFFFFFFF;
}

/**************************************end of file******************************************/
