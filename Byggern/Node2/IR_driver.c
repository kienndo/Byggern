/*
 * IR_driver.c
 *
 * Created: 03.11.2023 11:08:37
 *  Author: kiennd
 */ 


#include "IR_driver.h"

void ADC_init(void)
{
	//Disable write protection on PMC and ADC
 	PMC->PMC_WPMR |= 0X504D4300;
 	ADC->ADC_WPMR |= 0x41444300;
	 
	//Reset ADC
	ADC->ADC_CR = ADC_CR_SWRST;
	
	//Enable free run
	ADC->ADC_MR = ADC_MR_FREERUN_ON;
	
	//Enable ADC peripheral clock
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;

	//Enable channel 2
	ADC->ADC_CHER = ADC_CHER_CH2;
	
	//Start conversion
	ADC->ADC_CR = ADC_CR_START;	
}

uint16_t ADC_read(void)
{
	return ADC->ADC_CDR[2];
}

uint32_t goal_count(int *score)
{
	uint32_t threshold = 1000;
	
	if(ADC_read() < threshold)
	{
		*score += 1;
		delay_ms(500);
	}
	
	return *score;
}



