


#include "char_lcd.h"
#include "hc595/hc595.h"
#include "delay/delay.h"

#define LCD_EN (1 << 4) // falling edge triggered
#define LCD_RW (1 << 5) // 0 = write , 1 = read
#define LCD_RS (1 << 6) // 0 = command , 1 = data



void char_lcd_cmd(unsigned char cmd)
{
    hc595_send( ( (cmd >> 4) & 0x0F) | LCD_EN); // send high 4 bit with EN-HIGH
    delay_ms(1);
    hc595_send( (cmd >> 4) & 0x0F); // ONLY EN HIGH-TO-LOW FOR ENABLE
    delay_ms(10);

    hc595_send( (cmd & 0x0F) | LCD_EN); // send high 4 bit with EN-HIGH
    delay_ms(1);
    hc595_send(cmd & 0x0F); // ONLY EN HIGH-TO-LOW FOR ENABLE
    delay_ms(10);
}

void char_lcd_data(unsigned char data)
{
    hc595_send( ( (data >> 4) & 0x0F) | (LCD_EN | LCD_RS) ); // send high 4 bit with EN-HIGH
    delay_ms(1);
    hc595_send( ( (data >> 4) & 0x0F) | LCD_RS); // ONLY EN HIGH-TO-LOW FOR ENABLE
    delay_ms(10);

    hc595_send( (data & 0x0F) | (LCD_EN | LCD_RS) ); // send high 4 bit with EN-HIGH
    delay_ms(1);
    hc595_send( (data & 0x0F) | LCD_RS); // ONLY EN HIGH-TO-LOW FOR ENABLE
    delay_ms(10);
}

void char_lcd_4_bit_init(void)
{
	hc595_init();
	delay_ms(15); // power-on initialization time
	char_lcd_cmd(0x02); // set 4 bit operation
	char_lcd_cmd(0x28); // 0x20 for only 8 char , 0x28 for 16 char for 16x1 lcd
	char_lcd_cmd(0x0F); // set blink cursor vb.
}

// for 16x01 character lcd
void char_lcd(unsigned char data[16] , unsigned char size)
{
	unsigned char f;
	char_lcd_cmd(0x01); // clear lcd and set cursor to 0
	if( (size > 16) | (size == 0) ) return;
	for( f = 0 ; f < size ; f++)
	{
		if(f == 8)
		{
			char_lcd_cmd(0xC0); // set coursor to 8
		}
		char_lcd_data(data[f]);
	}
	// dummy data for many character lcd
	char_lcd_data(data[f]); // NOT BUG NECESSARY FOR LAST CHAR
}
