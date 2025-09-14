/*
 * GccApplication1.c
 *
 * Created: 29.08.2023 09:13:40
 * Author : kiennd
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#define F_CPU 4915200
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "UARTdriver.h"
#include "SRAMdriver.h"
#include "ADC.h"
#include "USBmulti_driver.h"
#include "SPI_driver.h"
#include "CAN_driver.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void)
{
	//Initialize
	USART_init(MYUBRR);
 	SRAM_init();
 	USBmulti_init();
 	OLED_init();
	CAN_init();
	
	//Print menu on display
	OLED_pos(0x00, 0x00);
	OLED_clearScreen();
	menu_items_print();
	
	//Choose menu
 	OLED_choose_menu(); //Contains a while-loop, must choose a menu to proceed
	
	//For testing CAN
// 	can_message message;
// 	message.id = 0x55;
// 	message.dlc = 0x8;
// 	message.data[0] = 0x5;
//  	for (uint8_t i = 0; i < message.dlc; i++) {
//  		message.data[i] = (15 + i);
//  	}
	
	
	while (1)
	{
		 CAN_send_joystick_position();
	}
	
	return 0;
}