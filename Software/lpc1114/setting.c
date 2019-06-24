void setting(void)
{
  unsigned char x,s = 0;
  tick_second = 255;
  while(1)
  {
    x = adc_2_light_up_down_read();
    switch( s )
    {
      case 0 :
      {
        
      }
      break;
      case 1 :
      {
        
      }
      break;
    }
    delay(button_delay);
  }
}
