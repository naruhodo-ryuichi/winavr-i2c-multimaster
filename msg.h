/*
 * msg.h
 *
 *  Created on: 10/08/2011
 *      Author: Administrator
 */

#ifndef MSG_H_
#define MSG_H_

#include "globals.h"
#include "i2c.h"
//type
#define COMMAND 0X00
#define STATUS 	0X01
#define TRIGGER 0X02
//key
#define HBEAT 		0X00
#define HBEAT_STOP 	0x01
#define HBEAT_REQ 	0x02

void msgparse(void);
void msgsend(uint8_t dest, uint8_t orig,uint8_t type,uint8_t key,uint8_t value);
#endif /* MSG_H_ */


