/*
 * solenoid.c
 *
 * Created: 07.11.2023 22:04:20
 *  Author: kiennd
 */ 
#include "solenoid.h"


void solenoid_init(void)
{
	//Enable pio på pa2
	//Sette den til output
	PIOA->PIO_PER |= PIO_PER_P2;
	PIOA->PIO_OER |= PIO_OER_P2;
	
	//Starte med høy verdi
	PIOA->PIO_SODR |= PIO_SODR_P2;
}

void check_btn(CAN_MESSAGE message)
{
	int8_t btn = message.data[0];
	if(btn) {
		//printf("btn is pressed");
		PIOA->PIO_CODR |= PIO_CODR_P2;
	} else {
		PIOA->PIO_SODR |= PIO_SODR_P2;
	
	}
}