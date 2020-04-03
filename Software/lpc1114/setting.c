
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

unsigned char increase_month(unsigned char month)
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
unsigned char reduce_month(unsigned char month)
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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*

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
      case SET_SPECIAL:
        {
          picky = set_special_alarm();          
        }
        break;
      case SET_NAMAZ:
        {
          picky = set_namaz_alarm();
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
    set_led_write_bit(VERSION_ADDR,data); // (CIRCLE,DIGIT)
    led_write(); // WRITE LEDS
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_SPECIAL;
          }
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SHOW_VERSION;
          }
        }
        break;
      case BUTTON_CANCEL:
        {
          // blink_off();
          return CANCEL;
        }
        break;
      case BUTTON_OK:
        {
          if(status = SKIP)
          {
            return SHOW_VERSION;
          }
          else
          {
          }
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
unsigned char set_special_alarm()
{
  unsigned int reg_addr = VERSION_ADDR,size = 1;
  unsigned char data,status = SKIP;
  if(e2prom_read(reg_addr,&data,size) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_bit(VERSION_ADDR,data); // (CIRCLE,DIGIT)
    led_write(); // WRITE LEDS
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_SPECIAL;
          }
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SHOW_VERSION;
          }
        }
        break;
      case BUTTON_CANCEL:
        {
          // blink_off();
          return CANCEL;
        }
        break;
      case BUTTON_OK:
        {
          if(status = SKIP)
          {
            return SHOW_VERSION;
          }
          else
          {
            // read data from e2prom and same as old data not write same data
          }
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
*/















/*
#define SET_LRM 201
#define SET_CLK 202
#define STP_LRM 203
#define SLP 204
#define BOO 205
#define WRT_SET 206
#define LIG_DWN 207
#define LIG_UP 208
#define TM_DWN 209
#define TM_UP 210



void setting(void)
{
  unsigned int ee_reg = 1;
  unsigned char set;
  unsigned char btn;
  unsigned char cho1,cho2;
  unsigned char mux = 1;
  systick_second_sleep(255);
  if(i2c(eeprom_addr,ee_reg,2,1,&set,1) == ERR)
  {
    error();
  }
  while(1)
  {
    led_write(set,(60 - ee_reg),((60 - ee_reg) - mux));
    cho1 = 0;
    while(1)
    {
      btn = check_button();
      switch(btn)
      {
        case SET_LRM:
          {
            systick_second_sleep(255);
            cho1 = 1;
          }
          break;
        case SET_CLK:
          {
            systick_second_sleep(255);
            cho1 = 1;
          }
          break;
        case STP_LRM:
          {
            systick_second_sleep(255);
            cho1 = 1;            
          }
          break;
        case SLP:
          {
            systick_second_sleep(1);
            cho1 = 1;
            cho2 = 1;
          }
          break;
        case BOO:
          {
            systick_second_sleep(255);
            cho1 = 1;            
          }
          break;
        case WRT_SET:
          {
            systick_second_sleep(255);
            cho1 = 1;
            cho2 = 1;
            write_setting(ee_reg,set,mux);
          }
          break;
        case LIG_UP:
          {
            systick_second_sleep(255);
            cho1 = 1;
            if(ee_reg == 0xFFF)
            {
              ee_reg = 1;
            }
            else
            {
              ee_reg++;
            }
            mux = (ee_reg % 60) + 1;
            if(i2c(eeprom_addr,ee_reg,2,1,&set,1) == ERR)
            {
              error();
            }
          }
          break;
        case LIG_DWN:
          {
            systick_second_sleep(255);
            cho1 = 1;
            if(ee_reg == 1)
            {
              ee_reg = 0xFFF;
            }
            else
            {
              ee_reg--;
            }
            mux = (ee_reg % 60) + 1;
            if(i2c(eeprom_addr,ee_reg,2,1,&set,1) == ERR)
            {
              error();
            }
          }
          break;
        case TM_UP:
          {
            systick_second_sleep(255);
            cho1 = 1;
            if(check_registered_data(ee_reg)) //fonksiyon yazilacak
            {
              if(set)
              {
                set = 0;
              }
              else
              {
                set = 1;
              }
            }
            else
            {
              if(set == 255)
              {
                set = 0;
              }
              else
              {
                set++;
              }
            }
          }
          break;
        case TM_DWN:
          {
            systick_second_sleep(255);
            cho1 = 1;
            if(check_registered_data(ee_reg))
            {
              if(set)
              {
                set = 0;
              }
              else
              {
                set = 1;
              }
            }
            else
            {
              if(set == 0)
              {
                set = 255;
              }
              else
              {
                set--;
              }
            }
          }
          break;
        default:
          {
            set_blink(0,100000,100000);
          }
          break;
      }
      if(cho1)
      {
        break;
      }
    }
    if(cho2)
    {
      break;
    }
  }
}
// void led_write(unsigned char watch,unsigned char minute,unsigned char ref)
void set_blink(unsigned char typ,unsigned int dim_time,unsigned int shiny_time)
{
  unsigned char bl[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  if(typ)
  {
    bl[11] = led[11];
    bl[10] = led[10];
    bl[9] = led[9];
    bl[8] = led[8];
  }
  else
  {
    bl[7] = led[7];
    bl[6] = led[6];
    bl[5] = led[5];
    bl[4] = led[4];
    bl[3] = led[3];
    bl[2] = led[2];
    bl[1] = led[1];
    bl[0] = led[0];
  }
  yak(bl);
  delay(dim_time);
  yak(led);
  delay(shiny_time);
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
*/



