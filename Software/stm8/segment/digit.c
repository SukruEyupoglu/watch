
#include "stm8s.h"
#include "i2c.h"
#include "spi.h"
#include "beep.h"
#include "gpio.h"

unsigned char num_to_dig(unsigned char num);
void idle_mode(void);

int main(void)
{
	// CLK_CKDIVR = 0; // 16mhz
	// default 2mhz
	i2c_init();
	spi_init();
	
	unsigned char d[0x13];

	while(1)
	{
		// I2C TAKE THE CURSOR TO START
		i2c_start();
		i2c_write_addr(0xD0); // write
		i2c_write(0x0); // cursor setting
		i2c_stop();
		// GET ALL DATA FROM DS3231 TO d[0x13]
		i2c_start();
		i2c_write_addr(0xD1); // read
		i2c_read_arr(d,0x13);
		i2c_stop();
		// WRITE HOUR AND MINUTE
		spi(num_to_dig(d[hour])); //first hour
		spi(num_to_dig(d[minute])); //second minute
		// WHILE IDLE MODE CHECK BOOT BUTTON EVERYTIME
		idle_mode();  //  1 minute wait when check mode button
	}
}

void idle_mode(void)
{
	
}


unsigned char num_to_dig(unsigned char num)
{
	switch(num)
	{
		case 0:
		{		     // .GFE DCBA 7 segment display
			return 0x3F; // 0011 1111 
		}
		break;
		case 1:
		{
			return 0x06; // 0000 0110 
		}
		break;
		case 2:
		{
			return 0x5B; // 0101 1011 
		}
		break;
		case 3:
		{
			return 0x4F; // 0100 1111 
		}
		break;
		case 4:
		{
			return 0x66; // 0110 0110 
		}
		break;
		case 5:
		{
			return 0x6C; // 0110 1101 
		}
		break;
		case 6:
		{
			return 0x7C; // 0111 1101 
		}
		break;
		case 7:
		{
			return 0x07; // 0000 0111 
		}
		break;
		case 8:
		{
			return 0x7F; // 0111 1111 
		}
		break;
		case 9:
		{
			return 0x6F; // 0110 1111 
		}
		break;
		case 10:
		{
			return 0x70; // 0111 0000 
		}
		break;
		case 11:
		{
			return 0x36; // 0011 0110 
		}
		break;
		default:
		{
			return 0x0;
		}	
	}
	return 0x0;
}
		  
