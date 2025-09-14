#pragma once

#include "MCP2515.h"
#include "SPI_driver.h"

uint8_t mcp2515_read(uint8_t address);
void mcp2515_write(uint8_t address, uint8_t data);
void mcp2515_request_to_send(uint8_t MCP_RTS_TXN);
uint8_t mcp2515_read_status();
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void mcp2515_reset();
