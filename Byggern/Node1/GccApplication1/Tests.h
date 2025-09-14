#pragma once
#include <avr/io.h>
#include <avr/sleep.h>
#define F_CPU 4915200
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "UARTdriver.h"
#include "SRAMdriver.h"
#include "ADC.h"

void USART_Transmit_test();
void AddressDecoder_test(uint8_t address);
void ADC_test();
void Button_test();