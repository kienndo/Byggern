/*
 * PWM.h
 *
 * Created: 31.10.2023 09:07:17
 *  Author: kiennd
 */ 

#pragma once
#ifndef PWM_H_
#define PWM_H_

#include "sam.h"
#include "can_controller.h"

void PWM_init();
void joystickpos_to_duty_cycle(CAN_MESSAGE joystick_pos);

#endif /* PWM_H_ */