/*
 * PWM.c
 *
 * Created: 31.10.2023 09:07:17
 *  Author: kiennd
 */ 

#include "PWM.h"


void PWM_init()
{
	// Enable PWM clock
	PMC->PMC_WPMR |= 0X504D4300;
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	
	// Disable PIO
	PIOC->PIO_WPMR |= 0X50494F00;
	PIOC->PIO_PDR |= PIO_PDR_P18;
	PIOC->PIO_PDR |= PIO_PDR_P19;
	
	// Choosing peripheral B
	PIOC->PIO_ABSR |= PIO_ABSR_P18;
	PIOC->PIO_ABSR |= PIO_ABSR_P19;
	
	// Enable PWM and choose register
	PWM->PWM_WPCR |= 0X50574D30; 
	
	//Prescale with 32
	REG_PWM_CMR5 = (PWM_CMR_CPRE_MCK_DIV_32);
	REG_PWM_CMR6 = (PWM_CMR_CPRE_MCK_DIV_32);
	
	//period of 20ms
	REG_PWM_CPRD5 = 0xCD14;
	REG_PWM_CPRD6 = 0XCD14;
	
	//start with duty cycle 7,5%
	REG_PWM_CDTY5 = 48563;
	REG_PWM_CDTY6 = 48563;
	
	// Enable
	PWM->PWM_ENA |=PWM_ENA_CHID5;
	PWM->PWM_ENA |=PWM_ENA_CHID6;

}

void joystickpos_to_duty_cycle(CAN_MESSAGE joystick_pos)
{
	int8_t x_position = joystick_pos.data[1];
	
	//calculate corresponding duty cycle from x joystick position
	double corr_dutycycle = 48562.5 - 13.125*x_position;
	
	//printf("cdty = ", corr_dutycycle);
	
	//Update duty cycle
	REG_PWM_CDTYUPD5 = (uint32_t) corr_dutycycle;
	REG_PWM_CDTYUPD6 = (uint32_t) corr_dutycycle;
}

