unsigned char ds3231_clock_setting(unsigned char select_clock_alarm1_alarm2)
{
  unsigned char minute,hour;
  switch(select_clock_alarm1_alarm2)
  {
    case CLOCK:
      {
        if(read_ds3231_minute(&minute) == ERR)
        {
          return ERROR;
        }
        if(read_ds3231_hour(&hour) == ERR)
        {
          return ERROR;
        }        
      }
      break;
    case AL1:
      {
        if(read_ds3231_alarm_1_minute(&minute) == ERR)
        {
          return ERROR;
        }
        if(read_ds3231_alarm_1_hour(&hour) == ERR)
        {
          return ERROR;
        }        
      }
      break;
    case AL2:
      {
        if(read_ds3231_alarm_2_minute(&minute) == ERR)
        {
          return ERROR;
        }
        if(read_ds3231_alarm_2_hour(&hour) == ERR)
        {
          return ERROR;
        }                
      }
      break;
    default:
    break;
  }
  // yaz functıon editing now
}
void ds3231_special_setting(void)
{
  
}
void e2prom_settings(void)
{
  
}

