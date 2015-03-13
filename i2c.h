/*
 * i2c.h
 *
 *  Created on: 20/07/2011
 *      Author: Administrator
 */

#ifndef I2C_H_
#define I2C_H_
#include "globals.h"
#include <compat/twi.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// default bitrate
#define MAX_TRIES 50
#define BUSYCHECKS 10
#define I2C_MODE    (_BV(TWIE) | _BV(TWEA) | _BV(TWEN) | _BV(TWINT)) /* Master and slave */
#define I2C_PRESCALER           1 /* either 1, 4, 16 or 64 */
#define I2C_TWSR                0x00 /* corresponds to 0, 1, 2 or 3 */
#define I2C_TWBR                (((F_CPU/1000UL)/I2C_SCL_FREQ_KHZ) -16) / (2 * I2C_PRESCALER)

extern volatile uint8_t i2c_sta;
void i2c_send(uint8_t msg[]);
void i2c_init(void);
uint8_t i2cs_rcv(void);
void i2cs_getdata( uint8_t* msg );
void i2c_start(void);
void i2c_reset(void);
#define OFF	0x00
#define SND_ON	0x02
#define RCV_ON	0x03
#define SND_END	0x04
#define RCV_END	0x05

#endif /* I2C_H_ */


