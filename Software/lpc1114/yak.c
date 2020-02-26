void setting(void)
{
  unsigned char picky = SET_SECOND;
  while(1)
  {
   // button_repress_delay(); // maybe inside check_button ?
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
    }
  }
}
unsigned char set_second(void)
{
  unsigned char x,er;
  if(read_ds3231_second(&x) == ERR)
  {
    return ERROR;
  }
  blink_on();
  while(1)
  {
    switch(check_button())
      case BUTTON_UP:
      {
        
      }
      break;
      case BUTTON_DOWN:
      {
        
      }
      break;
      case BUTTON_CANCEL:
      {
        blink_off();
        return EXIT;
      }
      break;
      case BUTTON_OK_WRITE:
      {
        
      }
      break;
  }

}


