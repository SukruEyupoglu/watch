
#include "stm8s.h"
#include "i2c.h"


int main(void)
{
	// CLK_CKDIVR = 0; // 16mhz
	// default 2mhz
	i2c_init();
	unsigned char d[0x13];

	while(1)
	{
		i2c_start();
		i2c_write_addr(0xD0); // write
		i2c_write(0x0); // cursor setting
		i2c_stop();

		i2c_start();
		i2c_write_addr(0xD1); // read
		i2c_read_arr(d,0x13);
	}

}
