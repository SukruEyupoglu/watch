
#include "setting.h"
#include "e2prom.h"
#include "ds3231.h"
#include "error.h"
#include "led.h"


const unsigned char monthdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

unsigned char setting_ds3231(void)
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
  return OK;
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
          status = SKIP;
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

unsigned char set_minute(void)
{
  unsigned char x,status = SKIP;
  if(read_ds3231_minute(&x) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_reg(SET_MINUTE,x); // SET LED REGISTERS
    led_write(); //WRITE LEDS      
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_HOUR;
          }
          x = increase_minute(x);
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SET_SECOND;
          }
          x = reduce_minute(x);
        }
        break;
      case BUTTON_CANCEL:
        {
          blink_off();
          return SET_MINUTE;
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
          if(write_ds3231_minute(x) == ERR)
          {
            return ERROR;
          }
          blink_off();
          status = SKIP;
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

unsigned char set_hour(void)
{
  unsigned char x,status = SKIP;
  if(read_ds3231_hour(&x) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_reg(SET_HOUR,x); // SET LED REGISTERS
    led_write(); //WRITE LEDS      
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_WEEKDAY;
          }
          x = increase_hour(x);
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SET_MINUTE;
          }
          x = reduce_hour(x);
        }
        break;
      case BUTTON_CANCEL:
        {
          blink_off();
          return SET_HOUR;
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
          if(write_ds3231_hour(x) == ERR)
          {
            return ERROR;
          }
          blink_off();
          status = SKIP;
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

unsigned char set_weekday(void)
{
  unsigned char x,status = SKIP;
  if(read_ds3231_day(&x) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_reg(SET_WEEKDAY,x); // SET LED REGISTERS
    led_write(); //WRITE LEDS      
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_MONTHDAY;
          }
          x = increase_weekday(x);
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SET_HOUR;
          }
          x = reduce_weekday(x);
        }
        break;
      case BUTTON_CANCEL:
        {
          blink_off();
          return SET_WEEKDAY;
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
          if(write_ds3231_day(x) == ERR)
          {
            return ERROR;
          }
          blink_off();
          status = SKIP;
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

unsigned char set_monthday(void)
{
  unsigned char x,y,z,status = SKIP;
  if(read_ds3231_date(&x) == ERR)
  {
    return ERROR;
  }
  if(read_ds3231_month(&y) == ERR)
  {
    return ERROR;
  }
  if(read_ds3231_year(&z) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_reg(SET_MONTHDAY,x); // SET LED REGISTERS
    led_write(); //WRITE LEDS      
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_YEAR;
          }
          x = increase_monthday(x,y,z);
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SET_WEEKDAY;
          }
          x = reduce_monthday(x,y,z);
        }
        break;
      case BUTTON_CANCEL:
        {
          blink_off();
          return SET_MONTHDAY;
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
          if(write_ds3231_date(x) == ERR)
          {
            return ERROR;
          }
          blink_off();
          status = SKIP;
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

unsigned char set_month(void)
{
  unsigned char x,status = SKIP;
  if(read_ds3231_month(&x) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_reg(SET_MONTH,x); // SET LED REGISTERS
    led_write(); //WRITE LEDS      
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_YEAR;
          }
          x = increase_month(x);
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SET_MONTHDAY;
          }
          x = reduce_month(x);
        }
        break;
      case BUTTON_CANCEL:
        {
          blink_off();
          return SET_MONTH;
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
          if(write_ds3231_month(x) == ERR)
          {
            return ERROR;
          }
          blink_off();
          status = SKIP;
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

unsigned char set_year(void)
{
  unsigned char x,status = SKIP;
  if(read_ds3231_year(&x) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_reg(SET_YEAR,x); // SET LED REGISTERS
    led_write(); //WRITE LEDS      
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_YEAR;
          }
          x = increase_year(x);
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SET_MONTH;
          }
          x = reduce_year(x);
        }
        break;
      case BUTTON_CANCEL:
        {
          blink_off();
          return SET_YEAR;
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
          if(write_ds3231_year(x) == ERR)
          {
            return ERROR;
          }
          blink_off();
          status = SKIP;
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

unsigned char increase_weekday(unsigned char weekday)
{
  if(weekday == 7)
  {
    return 1;
  }
  else
  {
    return (weekday + 1);
  }  
}
unsigned char reduce_weekday(unsigned char weekday)
{
  if(weekday == 1)
  {
    return 7;
  }
  else
  {
    return (weekday - 1);
  }  
}

unsigned char increase_monthday(unsigned char monthday,unsigned char month_number,unsigned char year_number)
{
  if(!(year_number / 4))
  {
    if(month_number == 2)
    {
      if(monthday == monthdays[month_number - 1])
      {
        return (monthday + 1);
      }
    }
  }
  else
  {
    if(monthday == monthdays[month_number - 1])
    {
      return 1;
    }
    else
    {
      return (monthday + 1);
    }
  }
}
unsigned char reduce_monthday(unsigned char monthday,unsigned char month_number)
{
  if(monthday == 1)
  {
    return monthdays[month_number - 1];
  }
  else
  {
    return (monthday - 1);
  }  
}

unsigned char increase_year(unsigned char month)
{
  if(month == 12)
  {
    return 1;
  }
  else
  {
    return (month + 1);
  }  
}
unsigned char reduce_year(unsigned char month)
{
  if(month == 1)
  {
    return 12;
  }
  else
  {
    return (month - 1);
  }  
}

unsigned char increase_year(unsigned char year)
{
  if(year == 99)
  {
    return 0;
  }
  else
  {
    return (year + 1);
  }  
}
unsigned char reduce_year(unsigned char year)
{
  if(year == 0)
  {
    return 99;
  }
  else
  {
    return (year - 1);
  }  
}

###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################

unsigned char setting_e2prom(void)
{
  unsigned char picky = SHOW_VERSION;
  while(1)
  {
    switch(picky)
    {
      case SHOW_VERSION:
        {
          picky = show_version();
        }
        break;
      case SET_NAMAZ:
        {
          picky = set_namaz_alarm();          
        }
        break;
      case SET_SPECIAL:
        {
          picky = set_special_alarm();
        }
        break;
      case SET_HOURLY:
        {
          picky = set_hourly_alarm();          
        }
        break;
      case SET_REPEAT:
        {
          picky = set_repeated_alarm();
        }
        break;
      case SET_LIGHT:
        {
          picky = set_light();
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
      default:
        {
          
        }
        break;
    }
  }
  return OK;
}

unsigned char show_version(void)
{
  unsigned int reg_addr = VERSION_ADDR,size = 1;
  unsigned char data,status = SKIP;
  if(e2prom_read(reg_addr,&data,size) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_bit(E2PROM_SETTING_LAST_ADDR - reg_addr,data); // (CIRCLE,DIGIT)
    led_write(); // WRITE LEDS
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_ARE_THERE_ALARM;
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
          status = SKIP;
        }
        break;
      default:
        {
          
        }
        break;
    }
  }
  return OK;
}












