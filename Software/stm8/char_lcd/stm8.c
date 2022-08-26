#include "char_lcd/char_lcd.h"

int main()
{
	// code example for array
	unsigned char data[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	unsigned char size = 5;
	
	char_lcd_4_bit_init();
	char_lcd(data , size); //code example for array 
	
	while(1)
	{
	//char_lcd(data , size);
	}
return 0;
}

