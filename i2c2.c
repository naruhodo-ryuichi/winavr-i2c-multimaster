/*
 * main.c
 *
 *  Created on: 18/07/2011
 *      Author: Administrator
 */

#include "ports.h"
#include "serial.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#include "globals.h"
#include "i2c.h"
#include "msg.h"
volatile uint8_t i2c_sta;

void printmsg(uint8_t *msgrcv) {
	printb(msgrcv[0]);
	printb(msgrcv[1]);
	printb(msgrcv[2]);
	printb(msgrcv[3]);
	printb(msgrcv[4]);
	printb(0xFF);
}

int main(void) {
	// Initiate RS232
	RS232_Init();
	//imprimimos nuestra direccion
	printb(MYADDR);
	// en modo esclavo recibir
	i2c_init();
	//permitimos las interrupciones
	sei();
	_delay_ms(100);
	msgsend(0x00,MYADDR,COMMAND,HBEAT,0x00);
	while (1) {
		if (i2c_sta == RCV_END) {
			i2c_sta = OFF;
			msgparse();
		}
	}
}
