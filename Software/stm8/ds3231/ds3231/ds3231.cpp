ds3231_restart_counting()
{
}

void place_ds3231_cursor(unsigned char x)
{
// RESET FLAGS FOR CONTINUE
i2c_start();
i2c_write_addr(0xD0);
i2c_write(0x0E);
i2c_write(0x00); 
i2c_write(0x00); //i2c_write(0x0F);
i2c_stop();
// I2C TAKE THE CURSOR TO START
i2c_start();
i2c_write_addr(0xD0); // write
i2c_write(x); // cursor setting
i2c_stop();
}





