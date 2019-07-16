void setting(void)
{
  unsigned char d,x,s;
  tick_second = 255;
  while(1)
  {
    switch( d )
    {
      case 0 :
      {
        while(1)
        {
          s = adc_1_time_up_down_read();
          x = adc_2_light_up_down_read();
          if
          delay(button_delay);
        }
      }
      break;
      case 1 :
      {
        
      }
      break;
      default :
      {
        d = 0;
        return;
      }
      break;        
    }
  }
}
