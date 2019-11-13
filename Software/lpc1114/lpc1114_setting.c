#include "lpc1114_button.h"
#include "lpc1114_setting.h"
#include "lpc1114_ds3231.h"
#include "lpc1114_led.h"

// THIS SETTING FUCTION ONLY SET HOUR AND MINUTE
// CLOCK = 0 , AL1 = 1 , AL2 = 2
unsigned char ds3231_clock_setting(unsigned char select_clock_alarm1_alarm2)
{
  unsigned char selected = HOUR_SELECT;
  unsigned char minute,hour;
  // LOOK WHICH SETTING SELECTED(CLOCK,ALARM1,ALARM2) AND GET HOUR AND MINUTE FROM DS3231
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
    set_led_write_reg(minute,hour); // SET LED REGISTERS
    led_write(); //WRITE LEDS
    // LISTEN BUTTONS FOR SET SELECTED SETTINGS
    switch(check_button())
    {
      case BOO: // CHANGE SETTING HOUR AND MINUTE
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
      case STP_LRM: // INCREASE SELECTED
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
      case SLP: // REDUCE SELECTED
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
      case WRT_SET: // WRITE CHANGED SELECTED SETTINGS TO DS3231
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




