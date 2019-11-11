#include "lpc1114_button.h"
#include "lpc1114_setting.h"
#include "lpc1114_ds3231.h"
#include "lpc1114_led.h"

unsigned char ds3231_clock_setting(unsigned char select_clock_alarm1_alarm2)
{
  unsigned char selected = HOUR_SELECT;
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
  while(1)
  {
    set_led_write_reg(minute,hour); // not written yet
    led_write();
    switch(check_button())
    {
      case BOO:
        {
          if(selected == MINUTE_SELECT)
          {
            selected = HOUR_SELECT;
          }
          if(selected == HOUR_SELECT)
          {
            selected = MINUTE_SELECT;
          }          
        }
        break;        
      case STP_LRM:
        {
          if(selected == MINUTE_SELECT)
          {
            minute = increase_minute(minute);
          }
          if(selected == HOUR_SELECT)
          {
            hour = increase_hour(hour);
          }          
        }
        break;
      case SLP:
        {
          if(selected == MINUTE_SELECT)
          {
            minute = reduce_minute(minute);
          }
          if(selected == HOUR_SELECT)
          {
            hour = reduce_hour(hour);
          }                    
        }
        break;
      case WRT_SET:
        {
            switch(select_clock_alarm1_alarm2)
            {
              case CLOCK:
                {
                  if(write_ds3231_minute(minute) == ERR)
                  {
                    return ERROR;
                  }
                  if(write_ds3231_hour(hour) == ERR)
                  {
                    return ERROR;
                  }        
                }
                break;
              case AL1:
                {
                  if(write_ds3231_alarm_1_according_to_minute(minute) == ERR)
                  {
                    return ERROR;
                  }
                  if(write_ds3231_alarm_1_according_to_hour(hour) == ERR)
                  {
                    return ERROR;
                  }        
                }
                break;
              case AL2:
                {
                  if(write_ds3231_alarm_2_according_to_minute(minute) == ERR)
                  {
                    return ERROR;
                  }
                  if(write_ds3231_alarm_2_according_to_hour(hour) == ERR)
                  {
                    return ERROR;
                  }                
                }
                break;
              default:
                break;
            }
        }
        break;
      default:
        {
          return OK;
        }
        break;
    }
  }
}
void ds3231_special_setting(void)
{
  
}
void e2prom_settings(void)
{
  
}

