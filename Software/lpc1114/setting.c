void setting(void)
{
  unsigned int ee_reg = 1;
  unsigned char set;
  unsigned char btn;
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
      btn = check_button();
      switch(btn)
      {
        case 201:
          {
            
          }
          break;
        case 202:
          {
            
          }
          break;
        case 203:
          {
            
          }
          break;
        case 204:
          {
            
          }
          break;
        case 205:
          {
            
          }
          break;
        case 206:
          {
            
          }
          break;
        case 207:
          {
            
          }
          break;
        case 208:
          {
            
          }
          break;
        case 209:
          {
            
          }
          break;
        case 210:
          {
            
          }
          break;
        default:
          {
            set_blink();
          }
          break;
      }
    }
  }
}
// void led_write(unsigned char watch,unsigned char minute,unsigned char ref)
void set_blink(unsigned char typ,unsigned int dim_time,unsigned int shiny_time)
{
  unsigned char bl[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  if(typ)
  {
    
  }
  else
  {
    
  }
}
void yak(unsigned char sh[12])
{
  unsigned char f;
  for(f = 0 ; f < 12 ; f++)
  {
    spi( sh[f] );
  }
  latch();
}




