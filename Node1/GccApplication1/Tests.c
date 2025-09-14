#include "Tests.h"

void USART_Transmit_test()
{
		USART_Transmit('H');
		_delay_ms(1000);
		
		USART_Transmit('H');
		printf("Hello");
		_delay_ms(1000);

}

void AddressDecoder_test(uint8_t address)
{
	uint8_t *p = address;
	uint8_t var = *p;
	*p = 0x30;
}

void ADC_test()
{
	volatile char *P = 0x1500;
	*P = 0x0;
	volatile uint8_t *adc_value_ch1 = 0x1700;
	volatile uint8_t adc_ch1 = *adc_value_ch1;
	volatile uint8_t adc_ch2 = *adc_value_ch1;
	volatile uint8_t adc_ch3 = *adc_value_ch1;
	volatile uint8_t adc_ch4 = *adc_value_ch1;
	printf("verdien er %4d og %4d og %4d og %4d \r\n ",adc_ch1, adc_ch2, adc_ch3, adc_ch4);
	_delay_ms(1000);
}

void Button_test()
{
	
	DDRB &= ~((1<<PINB3)|(1<<PINB4)|(1<<PINB5));
	volatile uint8_t PORTB_val = PINB;
	uint8_t PIN4_mask = (1<<PINB4);
	
	if(PIN4_mask&PORTB_val){
		printf("Høyre knappen trykkes");
	}
	uint8_t PIN5_mask = (1<<PINB5);
	
	if(PIN5_mask&PORTB_val){
		printf("Venstre knappen trykkes");
	}
	
	uint8_t PIN3_mask = (1<<PINB3);
	if(!(PIN3_mask&PORTB_val)){
		printf("Joystick trykkes");
	}
}



