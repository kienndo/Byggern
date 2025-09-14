
#include "ADC.h"

uint8_t adc_read(int channel)
{
	//WR low, need to write to ADC to start conversion
	volatile char *P = 0x1500;
	*P = 0x0;
	
	//Read each channel
	volatile uint8_t *value = 0x1700;
	volatile uint8_t ch0 = *value;
	volatile uint8_t ch1 = *value;
	volatile uint8_t ch2 = *value;
	volatile uint8_t ch3 = *value;

	//Return the right channel
	switch(channel)
	{
		case 0:
		return ch0;
		case 1:
		return ch1;
		case 2:
		return ch2;
		case 3: 
		return ch3;
	}
	
}

