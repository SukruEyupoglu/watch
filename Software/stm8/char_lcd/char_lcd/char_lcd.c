


#include "char_lcd.h"
#include "hc595/hc595.h"
#include "delay/delay.h"

#define LCD_EN (1 << 4) // falling edge triggered
#define LCD_RW (1 << 5) // 0 = write , 1 = read
#define LCD_RS (1 << 6) // 0 = command , 1 = data



void char_lcd_4_bit_init(void)
{
	delay_ms(15); // power-on initialization time
	char_lcd_4_bit_send_command(0x00);
	char_lcd_4_bit_send_command(0x02);
	char_lcd_4_bit_send_command(0x20);
	char_lcd_4_bit_send_command(0x01);
	char_lcd_4_bit_send_command(0x0C);
	char_lcd_4_bit_send_command(0x06);	
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

void char_lcd_4_bit_send_data(unsigned char data)
{
	char_lcd_4_bit_send( ( LCD_EN | LCD_RS ) , data);
}
void char_lcd_4_bit_send_command(unsigned char cmd)
{
	char_lcd_4_bit_send( LCD_EN , cmd);
}
			    
void char_lcd(unsigned char data[20] , unsigned char size)
{
	unsigned char f;
	char_lcd_4_bit_send_command(0x01); // clear lcd
	char_lcd_4_bit_send_command(0x80); // set coursor to 0
	if( size > 20 ) return;
	for( f = 0 ; f < size ; f++)
	{
		char_lcd_4_bit_send_data(data[f]);
	}
}
