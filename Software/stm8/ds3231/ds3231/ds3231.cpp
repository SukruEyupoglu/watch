#include "../stm8s.h"
#include "i2c/i2c.h"

void ds3231::read_data(void)
{
  i2c_start();
  i2c_write_addr(0xD1); // read
  i2c_read_arr(ds3231.data,0x13); // inside i2c_stop(); there are
}

void ds3231::restart_counting(void)
{
  // RESET FLAGS FOR CONTINUE
  i2c_start();
  i2c_write_addr(0xD0);
  i2c_write(0x0E);
  i2c_write(0x7F & ds3231.data[0x0E]);  // control register
  i2c_write(0x7F & ds3231.data[0x0F]);  // control/status register
  i2c_stop();
}

void ds3231::place_cursor(unsigned char x)
{
  // I2C TAKE THE CURSOR TO START
  i2c_start();
  i2c_write_addr(0xD0); // write
  i2c_write(x); // cursor setting
  i2c_stop();
}





