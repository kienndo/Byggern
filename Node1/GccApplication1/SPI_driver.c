#include "SPI_driver.h"

void SPI_MasterInit (void)
{
	// Set MOSI, SCK, SS as output, all others input
	DDRB |= (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
	
	// Enable SPI, Master, set clock rate to fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	//Set MISO to input
	DDRB &= ~(1<<DDB6);
	
	//Set SPI mode 0
	SPCR &= ~(1<<CPOL);
	SPCR &= ~(1<<CPHA);
	
	//Set SS high
	PORTB &= (1<<PB4);
 }

void SPI_MasterTransmit(char cData)
{
	//Start transmission
	SPDR = cData;
	
	//Wait for transmission to complete
	while(!(SPSR & (1<<SPIF)));
}

char SPI_recieve(void)
{
	//Dummy-byte xP
	SPI_MasterTransmit(0xFF);
	
	return SPDR;
}
