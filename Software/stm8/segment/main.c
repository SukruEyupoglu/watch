
#include "stm8s.h"
#include "i2c.h"
#include "spi.h"
#include "beep.h"
#include "gpio.h"


int main(void)
{
	unsigned char d[0x13];
	// CLK_CKDIVR = 0; // 16mhz
	// default 2mhz
	
	// if u want close clocks for lower energy CLK_CKDIVR
	
	i2c_init();
	spi_init();
	


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
		// CHECK ALERT FLAG
		check_alert();
		// WHILE IDLE MODE CHECK BOOT BUTTON EVERYTIME
		idle_mode();  //  1 minute wait when check mode button
	}
}
