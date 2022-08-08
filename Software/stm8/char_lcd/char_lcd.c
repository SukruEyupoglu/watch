


#include "char_lcd.h"
#include "hc595/hc595.h"
#include "delay/delay.h"



void char_lcd_4_bit_init(void)
{
	unsigned char cmd = 0;
	cmd |= LCD_EN;
	cmd &= ~LCD_RW;
	cmd &= ~LCD_RS;
	delay_ms(15); // power-on initialization time
	hc595_send(cmd);
	delay_ms(3);
	char_lcd_4_bit_send( cmd , 0x02);
	char_lcd_4_bit_send( cmd , 0x20);
	char_lcd_4_bit_send( cmd , 0x01);
	char_lcd_4_bit_send( cmd , 0x0C);
	char_lcd_4_bit_send( cmd , 0x06);	
}

void char_lcd_4_bit_send(unsigned char cmd , unsigned char data)
{
	// SEND UPPER 4 BIT FIRST
	hc595_send( cmd | (data >> 4) );
	hc595_send( ( cmd | (data >> 4) ) & ( ~LCD_EN ) );
	delay_ms(1);
	hc595_send( cmd | (data >> 4) );
	delay_ms(3);
	// SEND LOWER 4 BIT SECOND
	hc595_send( cmd | (0x0F & data) );
	hc595_send( ( cmd | (0x0F & data) ) & ( ~LCD_EN ) );
	delay_ms(1);
	hc595_send( cmd | (0x0F & data) );
	delay_ms(3);
}

void char_lcd_4_bit_write(unsigned char data)
{
	
}


