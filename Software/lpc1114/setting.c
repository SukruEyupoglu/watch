void setting(void)
{
  unsigned int ee_reg = 1;
  unsigned char set;
  systick_second_sleep(255);
  while(1)
  {
    if(i2c(eeprom_addr,ee_reg,2,1,&set,1) == ERR)
    {
      error();
    }
    led_write(set,(60 - ee_reg),((60 - ee_reg) - 1));
    while(1)
    {
      
    }
  }
}
// void led_write(unsigned char watch,unsigned char minute,unsigned char ref)





