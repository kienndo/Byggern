
#pragma once
#ifndef MOTOR_H_
#define MOTOR_H_

#include "sam.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "TC.h"

//PIOD 
#define DIR PIO_PER_P10
#define EN PIO_PER_P9
#define SEL PIO_PER_P2
#define NOT_RST PIO_PER_P1
#define NOT_OE PIO_PER_P0

// PIOC
#define DO0 PIO_OER_P1
#define DO1 PIO_OER_P2
#define DO2 PIO_OER_P3
#define DO3 PIO_OER_P4
#define DO4 PIO_OER_P5
#define DO5 PIO_OER_P6
#define DO6 PIO_OER_P7
#define DO7 PIO_OER_P8

void DAC_init();
void joystick_to_speed(CAN_MESSAGE joystick_pos);
void motor_init();
uint16_t read_encoder();
void change_slider_pos(CAN_MESSAGE joystick_pos);
int PI_controller(int* errorsum);
void PID_to_speed(int* errorsum);

#endif /* MOTOR_H_ */