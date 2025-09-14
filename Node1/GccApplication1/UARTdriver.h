#pragma once
#include <stdio.h>
#include <avr/io.h>

void USART_init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
char USART_Receive(void);
