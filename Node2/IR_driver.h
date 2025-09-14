/*
 * IR_driver.h
 *
 * Created: 03.11.2023 11:09:03
 *  Author: kiennd
 */ 

#pragma once
#ifndef IR_DRIVER_H_
#define IR_DRIVER_H_

#include "sam.h"
#include "printf-stdarg.h"
#include "TC.h"

void ADC_init(void);
uint16_t ADC_read(void);
uint32_t goal_count(int *score);

#endif /* IR_DRIVER_H_ */