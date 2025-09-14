/*
 * TC.c
 *
 * Created: 07.11.2023 17:55:15
 *  Author: kiennd
 */ 

#include "TC.h"
#include "sam.h"
#include <stdio.h>


void timer_init(void)
{
	// Enable timer/counter peripheral clock
	PMC->PMC_PCER0 |= PMC_PCER0_PID27;
	
	// Disable write protection
	REG_TC0_WPMR = 0x54494D00;
	
	// Choose waveform mode, stop the clock when counter = the value of RC
	REG_TC0_CMR0 |= TC_CMR_WAVE;
	REG_TC0_CMR0 |= TC_CMR_CPCSTOP;
	
	// Enable counter clock
	REG_TC0_CCR0 |= TC_CCR_CLKEN;

 }

void delay_ms(int delay)
{
	// Choose MCK/32 clock frequency
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK2;
	
	//Set value to 10500 to get 1 ms
	REG_TC0_RC0 = 10500;

	for (int i = 0; i < delay; i++){
		// Restart the clock
		REG_TC0_CCR0 |= TC_CCR_SWTRG;
		
		//Stop after 1 ms
		while (!(REG_TC0_SR0 & TC_SR_CPCS));
	}
}

void delay_us(int delay)
{
	// Choose MCK/2 clock frequency
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK1;
	
	//Set value to 42 to get 1 us
	REG_TC0_RC0 = 42;

	for (int i = 0; i < delay; i++){
		// Restart the clock
		REG_TC0_CCR0 |= TC_CCR_SWTRG;
		
		//Stop after 1 ms
		while (!(REG_TC0_SR0 & TC_SR_CPCS));
	}
}