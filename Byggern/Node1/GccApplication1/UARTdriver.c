#include "UARTdriver.h"

void USART_init(unsigned int ubrr)
{
	//Set baud rate to 9600
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//Choosing one stop bit, no parity, 8 data bits
	UCSR0C &= ~(1<<UMSEL0);
	UCSR0C = (1<<URSEL0)|(3<<UCSZ00);
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	fdevopen(USART_Transmit, USART_Receive);
}

//From data sheet
void USART_Transmit(unsigned char data)
{
	if (data == '\n'){
		USART_Transmit('\r');
	}
	//Wait for empty transmit buffer 
	while (!( UCSR0A & (1<<UDRE0)) )
	;
	//Put data into buffer, sends the data
	UDR0 = data;
}

//From data sheet
char USART_Receive(void)
{
	//Wait for data to be received
	while (!(UCSR0A & (1<<RXC0)) )
	//Get and return received data from buffer
	return UDR0;
}