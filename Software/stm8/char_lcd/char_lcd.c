


#include "char_lcd.h"
#include "hc595/hc595.h"
#include "delay/delay.h"



void char_lcd_4_bit_init(void)
{
	
}

void char_lcd_4_bit_send(unsigned char data)
{
	// hc595_send( 0x0F & (data >> 4) );
}



