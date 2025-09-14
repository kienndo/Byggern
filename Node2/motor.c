
#include "motor.h"

volatile int slider_position = 0;

void DAC_init()
{
	//Disable write protection PMC
	PMC->PMC_WPMR |= 0X504D4300;
	
	//Enable DACC peripheral clock
	PMC->PMC_PCER1 = PMC_PCER1_PID38;
	
	//Disable write protection DACC
	DACC->DACC_WPMR |= 0X44414300;
	
	//Choose channel 0 and use half of the word register
	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL0;
	DACC->DACC_MR = DACC_MR_WORD_HALF;
	
	// Enable channel 0
	DACC->DACC_CHER |= DACC_CHER_CH0;
}

void motor_init()
{
	//Enable PIOC and PIOD clock
	PMC->PMC_PCER0 = PMC_PCER0_PID13;
	PMC->PMC_PCER0 = PMC_PCER0_PID14;
	
	//Disable write protection PIOC and PIOD
	PIOC->PIO_WPMR |= 0x50494f00;
	PIOD->PIO_WPMR |= 0x50494f00;
	
	//Enable output pin for EN, DIR, SEL, NOT RESET, NOT OE
	PIOD->PIO_PER |= EN | DIR | SEL | NOT_RST | NOT_OE;
	PIOD->PIO_OER |= EN | DIR | SEL | NOT_RST | NOT_OE;
	
	//Set EN, NOT RESET and NOT OE pins high
	PIOD->PIO_SODR |= EN |  NOT_RST | NOT_OE;
	
	//Enable input from encoder outputs
	PIOC->PIO_PER |= DO0 |  DO1 | DO2 |  DO3 |  DO4 |  DO5 |  DO6 |  DO7;
	PIOC->PIO_ODR |= DO0 |  DO1 | DO2 |  DO3 |  DO4 |  DO5 |  DO6 |  DO7;
	
	//Reset encoder
	PIOD->PIO_CODR |= NOT_RST;
}

void joystick_to_speed(CAN_MESSAGE joystick_pos)
{
	int8_t y_position = joystick_pos.data[2]; 
	
	double input_DAC = 0;
	if(y_position < -10)
	{
		PIOD->PIO_CODR |= PIO_CODR_P10;
		input_DAC = -655.36*(y_position);
		
	}
	else if(y_position > 10)
	{
		PIOD->PIO_SODR |= PIO_SODR_P10;
		input_DAC = 655.36*y_position;
	}
	
	//printf("PIO-VERDI: %d \r\n", PIOD->PIO_ODSR);
	//printf("input DAC = %d \r\n", (int32_t) input_DAC);
	
	if(input_DAC > 65000) {
		input_DAC = 65000;
	}
	
	DACC->DACC_CDR = (int32_t) input_DAC;
}


uint16_t read_encoder()
{
	// Set OE low
	PIOD->PIO_CODR = NOT_OE;
	
	//Set SEL low
	PIOD->PIO_CODR |= SEL;
	
	//Delay for 20 microseconds
	delay_us(20);
	
	//Read MJ2 to get high byte
	uint8_t high_byte = ((PIOC->PIO_PDSR) & 0x1FE) >> 1;
	
	//Set SEL high
	PIOD->PIO_SODR |= SEL;
	
	//Delay for 20 microseconds
	delay_us(20);
	
	//Read MJ2 to get low byte
	uint8_t low_byte = ((PIOC->PIO_PDSR) & 0x1FE) >> 1;
	
	//Reset encoder
	PIOD->PIO_CODR = NOT_RST;
	PIOD->PIO_SODR = NOT_RST;
	
	uint16_t total_byte = low_byte | ((int16_t) high_byte << 8);
	
	//Set OE high
	PIOD->PIO_SODR |= NOT_OE;
	
	return total_byte;
}

void change_slider_pos(CAN_MESSAGE joystick_pos)
{
	slider_position = joystick_pos.data[3];
}

int PI_controller(int* errorsum)
{
	//Encoder max = 1407;
	//Encoder min = 0;
	
	//Calculate ref from slider position
	int ref = 1407 - 14.07*slider_position;
	
	if (ref < 0){
		ref = 0;
	}
	
	int encoder_value = read_encoder();
	if (encoder_value > 1500) {
		encoder_value = 0;
	}
	
	int error = ref - encoder_value;
	//printf("error = %d \r\n", error);
	
	*errorsum += error;
	
	//Calculate u with a PI controller
	double K_p = 10;
	double K_i = 1.5;
	double T_s = 0.1;
	int u = K_p*error + *errorsum * T_s * K_i;
	
	//Limit u to DACC values
	if(u > 65536){
		u = 65536;
	} else if (u < -65536){
		u = -65536;
	}
	
	//printf("ref = %d, encoder = %d, error = %d, errorsum = %d, u = %d \r\n", ref, read_encoder(), error, *errorsum, u);
	
	return u;
	
}

void PID_to_speed(int* errorsum)
{
	int u = PI_controller(errorsum);
	
	int input_DAC = 0;
	if (u > 0) {
		//Left direction
		PIOD->PIO_CODR |= PIO_CODR_P10;
		input_DAC = u;
		} else {
		//Right direction
		PIOD->PIO_SODR |= PIO_SODR_P10;
		input_DAC = -u;
	}
	
	//Limit input to DAC (upper limit is 65000 to have some margin)
	if(input_DAC > 65000) 
	{
		input_DAC = 65000;
	} else if (input_DAC < 0) 
	{
		input_DAC = 0;
	}
	
	//printf("u = %d, input_DAC = %d \r\n", u, input_DAC);
	//Input to DAC
	DACC->DACC_CDR = (int32_t) input_DAC;
}

