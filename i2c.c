/*
 * i2c.c
 *
 *  Created on: 20/07/2011
 *      Author: Administrator
 */
 
#include "i2c.h"
#include "serial.h"
#include <stdlib.h>

static uint8_t wbuff[5];
static uint8_t rbuff[5];

void i2c_send(uint8_t msg[]) {
	//port answer to buffer
	uint8_t i;
	for (i = 0; i < DATASIZE; i++) {
		wbuff[i] = msg[i];
	}
	i2c_start();
}
inline void i2c_start(void) {
	_delay_ms(MYADDR/10);	//wait to be detected
	TWCR = _BV(TWSTA) | I2C_MODE; //send start
}

void i2c_init(void) {
	// Set the TWI slave address
	TWAR = MYADDR | _BV(TWGCE);
	//TWAMR = 0b11111110;
	// Set TWI bitrate
	TWBR = (uint8_t) I2C_TWBR;
	TWCR = I2C_MODE;
	//TWDR = 0xFF; // Default content = SDA released.
}

inline void i2c_reset(void) {
	TWCR = I2C_MODE;
}

void i2cs_getdata(uint8_t *msg) {
	uint8_t i;
	for (i = 0; i < DATASIZE; i++) {
		msg[i] = rbuff[i];
	}
	for (i = 0; i < DATASIZE; i++) {
		rbuff[i] = 0xFF;
	}
	i2c_sta = OFF;
}

ISR(TWI_vect)
{
	static uint8_t count;
	// Disable Global Interrupt
	cli();
	switch (TW_STATUS) {

	case TW_SR_STOP: // 0xA0: stop or repeated start condition rcvd while selected
		i2c_reset();
		if (count++ == DATASIZE)
			i2c_sta = RCV_END;
		break;

	case TW_SR_SLA_ACK: // 0x60: SLA+W rcvd, ACK returned
	case TW_SR_GCALL_ACK:
		count = 0;
	case TW_SR_DATA_ACK: // 0x80: data rcvd, ACK returned
	case TW_SR_GCALL_DATA_ACK:
		i2c_sta = RCV_ON;
		rbuff[count++] = TWDR;
		i2c_reset();
		break;

	case TW_START: // trx start condition
	case TW_REP_START: //trx restart condition
		count = 0;
		i2c_sta = SND_ON;
	case TW_MT_SLA_ACK: // address succesfully sent
	case TW_MT_DATA_ACK: //data trx success
		if (count == DATASIZE) {
			count = 0;
			i2c_sta = SND_END;
			TWCR = _BV(TWSTO) | I2C_MODE; //send stop
		} else {
			TWDR = wbuff[count++]; //load next byte from buffer
			i2c_reset();
		}
		break;
	case TW_MT_ARB_LOST: //bus busy
	case TW_SR_ARB_LOST_SLA_ACK:
	case TW_SR_ARB_LOST_GCALL_ACK:
		i2c_reset();
		break;
	case TW_MT_SLA_NACK: //addr trx, no ack
	case TW_ST_SLA_ACK: // 0xA8: SLA+R rcvd, ACK returned
	case TW_ST_DATA_ACK: // 0xB8: data transmitted, ACK rcvd
	case TW_ST_DATA_NACK: // 0xC0: data transmitted, NACK rcvd
	case TW_ST_LAST_DATA: // 0xC8: last data byte transmitted, ACK rcvd
	case TW_BUS_ERROR: // 0x00: illegal start or stop condition
	default:
		count = 0;
		i2c_reset();
	}

	// Enable Global Interrupt
	sei();

}

