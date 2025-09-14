
#pragma once
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "MCP2515_driver.h"
#include "UARTdriver.h"
#include "SRAMdriver.h"
#include "ADC.h"
#include "MCP2515.h"

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
char SPI_recieve(void);




