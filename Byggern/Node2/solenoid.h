/*
 * solenoid.h
 *
 * Created: 07.11.2023 22:04:43
 *  Author: kiennd
 */ 

#pragma once
#ifndef SOLENOID_H_
#define SOLENOID_H_

#include "sam.h"
#include "can_controller.h"
#include "TC.h"

void solenoid_init(void);
void check_btn(CAN_MESSAGE message);


#endif /* SOLENOID_H_ */