
#include "CAN_driver.h"

uint8_t CAN_init()
{
	uint8_t value;
	
	SPI_MasterInit();
	mcp2515_reset();
	
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG)
	{
		printf("MCP2515 is NOT in configuration mode after reset!\r\n");
		return 1;
	}
	
	//Enable interrupt
	mcp2515_write(MCP_CANINTE, 0x03);
	
	//Set can timing so that it matches the Atsam
	//CNF1: SJW = 4, BRP = 3
	mcp2515_write(MCP_CNF1, 0xC3);
	
	//CNF2: BLTMODE = 1, SAM = 0, PHSEG1 = 4, PRSEG = 3
	mcp2515_write(MCP_CNF2, 0xA3);
	
	//CNF3: PHSEG2 = 5
	mcp2515_bit_modify(MCP_CNF3, 0x7, 0x5);
	
	//Set normal mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	return 0;
}

void CAN_transmit(can_message message)
{
	//Setup transmit buffer 0
	
	//ID
	int8_t idHigh, idLow;
	idHigh = (uint8_t) ((message.id) >> 3);
	idLow = (uint8_t) ((message.id) << 5);
	
	mcp2515_write(0x31, idHigh);
	mcp2515_write(0x32, idLow);
	
	//Data length
	mcp2515_write(0x35, message.dlc);
	
	//Data
	for (uint8_t i = 0; i < message.dlc; i++){
		_delay_ms(1);
		mcp2515_write(0x36 + i, message.data[i]);
	}
	
	mcp2515_request_to_send(MCP_RTS_TX0);
}

can_message CAN_recieve()
{
	can_message message;
	uint16_t idHigh, idLow;
	
	uint8_t interrupt_status;
	interrupt_status = mcp2515_read(MCP_CANINTF);
	
	printf("interrupt status = %d ", mcp2515_read(MCP_CANINTF));
	
	//Receive buffer 0
	if(interrupt_status&(0x1)){
		printf("leser melding");
		idHigh = (uint16_t) mcp2515_read(0x61);
		idLow = (uint16_t) mcp2515_read(0x62);
		
		message.id = (idHigh<<3)+(idLow>>5);
		
		message.dlc = mcp2515_read(0x65);
		
		for(uint8_t i = 0; i < message.dlc; i++){
			message.data[i] = mcp2515_read(0x66 + i);
		}
		
		mcp2515_bit_modify(MCP_CANINTF, 0x1, 0);
	}
	
	//Receive buffer 1
 	if(interrupt_status&(0x2)){
 		printf("leser melding");
 		idHigh = (uint16_t) mcp2515_read(0x71);
 		idLow = (uint16_t) mcp2515_read(0x72);
		
		message.id = (idHigh<<3)+(idLow>>5);
			
		message.dlc = mcp2515_read(0x75);
			
		for(uint8_t i = 0; i < message.dlc; i++){
			message.data[i] = mcp2515_read(0x76 + i);
		}
			
		mcp2515_bit_modify(MCP_CANINTF, 0x2, 0);
	}
		

	return message;
}

void CAN_send_joystick_position(void)
{
	struct joystick_pos pos = USB_joystickPosition();
	int8_t joystick_button_press = joystick_button_pressed();
	int8_t right_slider_pos = USB_rightSliderPosition();
	
	can_message message;
	message.id = 0x0F; 
	message.dlc = 0x4;
	message.data[0] = (int8_t) joystick_button_press;
	message.data[1] = (int8_t) pos.x;
	message.data[2] = (int8_t) pos.y;
	message.data[3] = (int8_t) right_slider_pos;
	
	CAN_transmit(message);
}
