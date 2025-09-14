#pragma once

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UARTdriver.h"
#include "SRAMdriver.h"
#include "ADC.h"


#ifndef USBMULTI_DRIVER_H_
#define USBMULTI_DRIVER_H_

enum direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};
	
struct joystick_pos{
	volatile int8_t x;
	volatile int8_t y;
	};
	

void USBmulti_init();
enum direction USB_joystickDirection();
struct joystick_pos USB_joystickPosition();
int8_t USB_leftSliderPosition();
int8_t USB_rightSliderPosition();
int joystick_button_pressed();

void OLED_write_command(char command);
void OLED_init();
void OLED_goto_column(uint8_t col);
void OLED_pos(uint8_t page, uint8_t col);
void OLED_write_data(char data);
void OLED_goto_page(uint8_t page);
void OLED_write_char(char character);
void OLED_print(char string[]);
void OLED_choose_menu();
void menu_items_print(void);
void OLED_clearScreen();


#endif /* USBMULTI_DRIVER_H_ */