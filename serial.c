/*
 * serial.c
 *
 *  Created on: 18/07/2011
 *      Author: Administrator
 */

#include "serial.h"

void RS232_Init(void)
{	// Turn on the transmission and reception circuitry:
	UCSR0B |= (1 << TXEN0);
	// Use 8-bit character sizes:
	UCSR0C |= (3 << UCSZ00);
	// Load lower 8-bits of the baud rate value into the low byte
	// of the UBRR register:
	UBRR0L = BAUD_PRESCALE;
	// Load upper 8-bits of the baud rate value into the high byte
	// of the UBRR register:
	UBRR0H = (BAUD_PRESCALE >> 8);
}

/* Send some data to the serial port */

void printb( char dato )
{
      while (!(UCSR0A & (1 <<UDRE0)));
      	  UDR0 = dato;
}
