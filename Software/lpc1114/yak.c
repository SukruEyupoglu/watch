unsigned char setting(void)
{
  unsigned char picky = SET_SECOND;
  while(1)
  {
    switch(picky)
    {
      case SET_SECOND:
        {
          picky = set_second();
        }
        break;
      case SET_MINUTE:
        {
          picky = set_minute();          
        }
        break;
      case SET_HOUR:
        {
          picky = set_hour();
        }
        break;
      case SET_WEEKDAY:
        {
          picky = set_weekday();          
        }
        break;
      case SET_MONTHDAY:
        {
          picky = set_monthday();
        }
        break;
      case SET_MONTH:
        {
          picky = set_month();          
        }
        break;
      case SET_YEAR:
        {
          picky = set_year();
        }
        break;
      case SET_ALR1_SECOND:
        {
          picky = set_alr1_second();          
        }
        break;
      case SET_ALR1_MINUTE:
        {
          picky = set_alr1_minute();
        }
        break;
      case SET_ALR1_HOUR:
        {
          picky = set_alr1_hour();          
        }
        break;
      case SET_ALR2_MINUTE:
        {
          picky = set_alr2_minute();
        }
        break;
      case SET_ALR2_HOUR:
        {
          picky = set_alr2_hour();          
        }
        break;
      case EXIT:
        {
          return EXIT;          
        }
        break;
      case ERROR:
        {
          return ERROR;          
        }
        break;
    }
  }
  return ERROR;
}
unsigned char set_second(void)
{
  unsigned char x,status = SKIP;
  if(read_ds3231_second(&x) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_reg(SET_SECOND,x); // SET LED REGISTERS
    led_write(); //WRITE LEDS      
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_MINUTE;
          }
          x = increase_second(x);
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SET_SECOND;
          }
          x = reduce_second(x);
        }
        break;
      case BUTTON_CANCEL:
        {
          blink_off();
          return SET_SECOND;
        }
        break;
      case BUTTON_OK:
        {
          status = WAIT_FOR_SETTING;
          blink_on();
        }
        break;
      case BUTTON_WRITE:
        {
          if(write_ds3231_second(x) == ERR)
          {
            return ERROR;
          }
          blink_off();
        }
        break;
      default:
        {
          
        }
        break;
    }
  }
  return ERROR;
}


unsigned char increase_second(unsigned char second)
{
  return increase_minute(second);
}
unsigned char reduce_second(unsigned char second)
{
  return reduce_minute(second);
}

unsigned char increase_minute(unsigned char minute)
{
  if(minute == 59)
  {
    return 0;
  }
  else
  {
    return (minute + 1);
  }
}
unsigned char reduce_minute(unsigned char minute)
{
  if(minute == 0)
  {
    return 59;
  }
  else
  {
    return (minute - 1);
  }  
}
unsigned char increase_hour(unsigned char hour)
{
  if(hour == 23)
  {
    return 0;
  }
  else
  {
    return (hour + 1);
  }  
}
unsigned char reduce_hour(unsigned char hour)
{
  if(hour == 0)
  {
    return 23;
  }
  else
  {
    return (hour - 1);
  }  
}

