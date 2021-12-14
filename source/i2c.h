/*!******************************************************************************************
   File Name           : i2c.h
   Author Name         : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Author email id     : ande9392@colorado.edu
   IDE used for Coding : MCUXpresso
   Compiler            : GCC
   Date                : 13th December 2021

   Info on Code obtained from other sources:

   1.Chapter 8 of Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers
   by Alexander Dean
*******************************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN			I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC				I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 			i2c_wait();

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           I2C0->C1 &= ~I2C_C1_TXAK_MASK

/*****************************************************************
 * initialise the I2C driver
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 ****************************************************************/
void i2c_init(void);

/*****************************************************************
 * send the start sequence
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 ****************************************************************/
void i2c_start(void);

/*****************************************************************
 * send device and register addresses
 *
 * Parameters:
 *  dev --> device adress
 *  address --> register address
 *
 * Returns:
 *   void
 ****************************************************************/
void i2c_read_setup(uint8_t dev, uint8_t address);

/*****************************************************************
 * read a byte and ack/nack as appropriate
 *
 * Parameters:
 *  isLastRead --> to send NACK accordingly
 *
 * Returns:
 *   void
 ****************************************************************/
uint8_t i2c_repeated_read(uint8_t);

/*****************************************************************
 * read a byte using I2C
 *
 * Parameters:
 *  dev --> device adress
 *  address --> register address
 *
 * Returns:
 *   void
 ****************************************************************/
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);

/*****************************************************************
 * write a byte using I2C
 *
 * Parameters:
 *  dev --> device adress
 *  address --> register address
 *
 * Returns:
 *   void
 ****************************************************************/
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* I2C_H_ */

/**************************************end of file******************************************/
