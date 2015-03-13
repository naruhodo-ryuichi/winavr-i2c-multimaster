/*
 * serial.h
 *
 *  Created on: 18/07/2011
 *      Author: Administrator
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <avr/io.h>

void RS232_Init(void);
void printb( char dato );

#endif /* SERIAL_H_ */
