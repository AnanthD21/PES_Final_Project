/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/*!******************************************************************************************
   File Name           : tilt_angle_Acc_MKL25Z128xxx4_Project.c
   Author Name         : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Author email id     : ande9392@colorado.edu
   IDE used for Coding : MCUXpresso IDE
   Compiler            : GCC
   Date                : 13th December 2021

   Info on Code obtained from other sources:

   1. Chapter 8 of Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers
      by Alexander Dean

   above links have been referred to write below code.

*******************************************************************************************/

/*header files*/
#include "finiteStateMachine.h"
#include "led.h"
#include "test_cbfifo.h"
#include <stdio.h>
#include "sysclock.h"
#include "uart.h"
#include "i2c.h"
#include "mma8451.h"
/*
 * @brief   Application entry point.
 */
int main(void)
{
	/*
	 * To test cbfifo utilised in UART,
	 * leds and MMA8451 Accelerometer
	 * sensor in debug mode at the start
	 */
#ifdef DEBUG
	sysclock_init();
	initUart();
	test_cbfifo();
	printf("testing circular buffers...\r\n");

	printf("testing rgb leds...\r\n");
	rgbInit();
	testRgbLed();

	printf("Self-test of MMA8451 Acc sensor...\r\n");
	i2c_init();
	init_mma();
	self_test();

#endif

	/*enter finite state machine*/
	fsmLoop();

    return 0 ;
}

/**************************************end of file******************************************/
