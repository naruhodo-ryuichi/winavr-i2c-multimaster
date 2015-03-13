/*
 * 0: dest
 * 1: sender
 * 2: type
 * 3: key
 * 4: value
 *
 */

#include "msg.h"

void msgparse(void) {
	uint8_t msg[DATASIZE];
	i2cs_getdata(msg);
	if (msg[0] == MYADDR || msg[0] == 0x00) {
		switch (msg[2]) {//type
		case HBEAT: //GUARDAR EN LA LISTA
			break;
		case HBEAT_REQ:
			msgsend(msg[1], MYADDR, HBEAT, HBEAT_TIME, HBEAT_VALUE);
			break;
		}

	}
}

void msgsend(uint8_t dest, uint8_t orig, uint8_t type, uint8_t key,
		uint8_t value) {
	uint8_t msgsend[DATASIZE] = { dest | TW_WRITE, orig, type, key, value };
	i2c_send(msgsend);
}
