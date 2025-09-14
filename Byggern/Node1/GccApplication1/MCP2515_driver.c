
#include "MCP2515_driver.h"

uint8_t mcp2515_read(uint8_t address)
{
	PORTB |= (1<<PB4);
	uint8_t result;
	
	//Set SS low
	PORTB &= ~(1<<PB4);
	
	SPI_MasterTransmit(MCP_READ);
	SPI_MasterTransmit(address);
	result = SPI_recieve();

	//Set SS high
	PORTB |= (1<<PB4);
	
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data)
{
	PORTB |= (1<<PB4);
	
	//Set SS low
	PORTB &= ~(1<<PB4);
	
	SPI_MasterTransmit(MCP_WRITE);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	
	//Set SS high
	PORTB |= (1<<PB4);
}

void mcp2515_request_to_send(uint8_t MCP_RTS_TXN)
{
	PORTB |= (1<<PB4);
	
	//Set SS low
	PORTB &= ~(1<<PB4);
	
	SPI_MasterTransmit(MCP_RTS_TXN);
	
	//Set SS high
	PORTB |= (1<<PB4);
}

uint8_t mcp2515_read_status()
{
	uint8_t status;
	PORTB |= (1<<PB4);
	
	//Set SS low
	PORTB &= ~(1<<PB4);
	
	SPI_MasterTransmit(MCP_READ_STATUS);
	status = SPI_recieve();
	
	PORTB &= ~(1<<PB4);
	
	return status;
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	PORTB |= (1<<PB4);
	
	//Set SS low
	PORTB &= ~(1<<PB4);
	
	SPI_MasterTransmit(MCP_BITMOD);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(mask);
	SPI_MasterTransmit(data);
}

void mcp2515_reset()
{
	PORTB |= (1<<PB4);
	
	//Set SS low
	PORTB &= ~(1<<PB4);
	
	SPI_MasterTransmit(MCP_RESET);
	
	PORTB |= (1<<PB4);
	
}



