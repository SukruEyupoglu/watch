


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
	delay_ms(15); // power-on initialization time
	char_lcd_cmd(0x02);
	char_lcd_cmd(0x28);
	char_lcd_cmd(0x0E);
}

void char_lcd(unsigned char data[20] , unsigned char size)
{
	unsigned char f;
	char_lcd_cmd(0x01); // clear lcd
	char_lcd_cmd(0x80); // set coursor to 0
	if( size > 20 ) return;
	for( f = 0 ; f < size ; f++)
	{
		char_lcd_data(data[f]);
	}
}
