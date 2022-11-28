void restart_counting(void)
{
  // RESET FLAGS FOR CONTINUE
  i2c_start();
  i2c_write_addr(0xD0);
  i2c_write(0x0E);
  i2c_write(0x7F & data[0x0E]);  // control register
  i2c_write(0x7F & data[0x0F]);  // control/status register
  i2c_stop();
}

void place_cursor(unsigned char x)
{
// I2C TAKE THE CURSOR TO START
i2c_start();
i2c_write_addr(0xD0); // write
i2c_write(x); // cursor setting
i2c_stop();
}





