/*
 * Node2.c
 *
 * Created: 17.10.2023 14:07:46
 * Author : kiennd
 */ 

#include "sam.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "PWM.h"
#include "IR_driver.h"
#include "motor.h"
#include "TC.h"
#include "solenoid.h"

int main(void)
{
	//Set can timing 
	WDT->WDT_MR = WDT_MR_WDDIS;
	uint32_t PHASE2 = 6;
	uint32_t PHASE1 = 5;
	uint32_t PROPAG = 4;
	uint32_t SJW = 3;
	uint32_t BRP = 42;
	uint32_t SMP = 1;
	uint32_t can_br = (PHASE2-1) | ((PHASE1-1) << 4) | ((PROPAG-1) << 8) | ((SJW-1) << 12) | ((BRP-1) << 16) | (SMP << 24);


    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
 	can_init_def_tx_rx_mb(can_br);
 	PWM_init();
	ADC_init();
	DAC_init();
	motor_init();
	timer_init();
	solenoid_init();
	
	int score = 0;
	int errorsum = 0;
	
    while (1) 
    {
		//Turn LEDs on
// 		REG_PIOA_WPMR &= ~(1<<PIO_WPMR_WPEN);
// 		REG_PIOA_PER |= PIO_PA19;
// 		REG_PIOA_OER |= PIO_PA19;
// 		REG_PIOA_SODR |= PIO_PA19;
// 				
// 		REG_PIOA_PER |= PIO_PA20;
// 		REG_PIOA_OER |= PIO_PA20;
// 		REG_PIOA_SODR |= PIO_PA20;
	
		//Test ADC
//      printf("adc_read: %d \r\n", ADC_read());

		//Test read_encoder
        //printf("total byte = %d \r\n", read_encoder());
		
		//Print score
 		printf("score = %d \r\n", goal_count(&score));
		
		//Start PI controller
		PID_to_speed(&errorsum);
		 
    }
}
