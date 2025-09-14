#include "USBmulti_driver.h"
#include "Fonts.h"

void USBmulti_init()
{
	//Set pin 3, 4 and 5 as input
	DDRD &= ~((1<<PIND3)|(1<<PIND4)|(1<<PIND5));	
}

enum direction USB_joystickDirection()
{
	int16_t x_pos = USB_joystickPosition().x;
	int16_t y_pos = USB_joystickPosition().y;

	if (abs(x_pos) > abs(y_pos)) {
		if(x_pos < -1){
			return LEFT;
		} else if (x_pos > 1){
			return RIGHT;
		}
	} else if (abs(x_pos) < abs(y_pos)) {
		if(y_pos < -3){
			return DOWN;
		} else if (y_pos > 3) {
			return UP;
		}
	}
	
	return NEUTRAL;
}

 struct joystick_pos USB_joystickPosition()
{
	struct joystick_pos j_pos;
	
	uint8_t y_pos = adc_read(0);
	uint8_t x_pos = adc_read(1);
	
	int16_t x_pos_signed = (int16_t) x_pos;
	int16_t y_pos_signed = (int16_t) y_pos;
	

	//printf("x_pos = %d, x_pos_signed = %d \r\n", x_pos, x_pos_signed);
	
	if (y_pos_signed <= 127) {
		j_pos.y = -(((127-y_pos_signed)*100)/127);
	} else {
		j_pos.y = ((y_pos_signed-127)*100)/(249-127);
	}
	
	if (x_pos <= 126){
		j_pos.x = -(((126-x_pos_signed)*100)/126);
	} else {
		j_pos.x = ((x_pos_signed-126)*100)/(250-126);
	}
	
	//printf("j_pos.y = %d, j_pos.x = %d \r\n ", j_pos.y, j_pos.x);
	 
	return j_pos;
	 
 }
 
 int joystick_button_pressed()
 {
	 volatile uint8_t PORTD_val = PIND;
	 
	 uint8_t PIN3_mask = (1<<PIND3);
	 return !(PIN3_mask&PORTD_val);
 }
 
 int8_t USB_leftSliderPosition()
 {
	 int8_t pos = (adc_read(2)*100)/255;
	 return pos;
 }
 
 int8_t USB_rightSliderPosition()
 {
	 int8_t pos = (adc_read(3)*100)/255;
	 return pos;
 }

//From data sheet
void OLED_init()
{
 OLED_write_command(0xae); // display off
 OLED_write_command(0xa1); //segment remap
 OLED_write_command(0xda); //common pads hardware: alternative
 OLED_write_command(0x12);
 OLED_write_command(0xc8); //common output scan direction:com63~com0
 OLED_write_command(0xa8); //multiplex ration mode:63
 OLED_write_command(0x3f);
 OLED_write_command(0xd5); //display divide ratio/osc. freq. mode
 OLED_write_command(0x80);
 OLED_write_command(0x81); //contrast control
 OLED_write_command(0x50);
 OLED_write_command(0xd9); //set pre-charge period
 OLED_write_command(0x21);
 OLED_write_command(0x20); //Set Memory Addressing Mode
 OLED_write_command(0x00); //horizontal mode
 OLED_write_command(0xdb); //VCOM deselect level mode
 OLED_write_command(0x30);
 OLED_write_command(0xad); //master configuration
 OLED_write_command(0x00);
 OLED_write_command(0xa4); //out follows RAM content
 OLED_write_command(0xa6); //set normal display
 OLED_write_command(0xaf); // display on
 }
 
void OLED_goto_column(uint8_t col)
{
	OLED_write_command(0x21);
	OLED_write_command(col);
	OLED_write_command(0x7F);
}
  
 void OLED_goto_page(uint8_t page)
 {
	  OLED_write_command(0x22);
	  OLED_write_command(page);
	  OLED_write_command(0x07);
 }
 
 void OLED_pos(uint8_t page, uint8_t col)
 {
	 OLED_goto_column(col);
	 OLED_goto_page(page);
 }

 void OLED_write_data(char data)
 {
	 char *data_OLED_ptr = (char *)0x1200;
	 data_OLED_ptr[0] = (char)data;
 }
 
 void OLED_write_command(char command)
 {
	 char *command_OLED_ptr = (char *)0x1000;
	 command_OLED_ptr[0] = command;
 }

void OLED_write_char(char character)
{
	uint8_t byte;
	for (int j = 0; j < 7; j++){
		byte = pgm_read_byte(&(font8[character - 32][j]));
		OLED_write_data(byte);
	}
}

void OLED_print(char string[])
{
	for(int i = 0; i < strlen(string); i++){
		OLED_write_char(string[i]);
	}
}

void OLED_choose_menu()
{
	int current_page = 0;
	
	OLED_pos(0x00, 0x75);
	
	while(!(joystick_button_pressed())){
		OLED_goto_column(0x75);
		OLED_write_char(' ');
		if (USB_joystickDirection() == UP && current_page > 0){
			OLED_goto_page(current_page - 1);
			current_page -= 1;
			} else if(USB_joystickDirection() == DOWN && current_page < 7){
			OLED_goto_page(current_page + 1);
			current_page += 1;
		}
		OLED_goto_column(0x75);
		OLED_write_char('<');
		
		_delay_ms(1000);
	}
	
	OLED_clearScreen();
	
	return current_page;
	
}

void menu_items_print(void)
{
	OLED_pos(0x00, 0x00);
	OLED_print("Start Game");
	OLED_pos(0x01, 0x00);
	OLED_print("Start Game");
	OLED_pos(0x02, 0x00);
	OLED_print("Start Game");
	OLED_pos(0x03, 0x00);
	OLED_print("Start Game");
	OLED_pos(0x04, 0x00);
	OLED_print("Start Game");
	OLED_pos(0x05, 0x00);
	OLED_print("Start Game");
	OLED_pos(0x06, 0x00);
	OLED_print("Start Game");
	OLED_pos(0x07, 0x00);
	OLED_print("Start Game");
}

void OLED_clearScreen()
{
	for(int i = 0; i < 8; i++){
		OLED_goto_page(i);
		for (int j = 0; j < 128; j++){
			OLED_goto_column(j);
			OLED_write_data(0x00);
		}
	}
	
	printf("screen_cleared");
}