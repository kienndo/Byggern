#pragma once

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "SPI_driver.h"
#include "USBmulti_driver.h"

typedef struct can_message{
	uint16_t id;
	int8_t data[8];
	uint8_t dlc;
}can_message;

uint8_t CAN_init();
void CAN_transmit(can_message message);
can_message CAN_recieve();
void CAN_send_joystick_position(void);
