#include "lpc1114_i2c.h"
#include "lpc1114_ds3231.h"

unsigned char write_ds3231_second(unsigned char second)
{
    if(second < 60)
    {
      if(i2c(DS3231_ADDR,0x00,1,0,&time2reg(second),1) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_minute(unsigned char minute)
{
    if(minute < 60)
    {
      if(i2c(DS3231_ADDR,0x01,1,0,&time2reg(minute),1) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_hour(unsigned char hour)
{
    if(hour < 24)
    {
      if(i2c(DS3231_ADDR,0x02,1,0,&time2reg(hour),1) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_day(unsigned char day)
{
    if( (day < 8) & (day > 0) )
    {
      if(i2c(DS3231_ADDR,0x03,1,0,&day,1) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_date(unsigned char date)
{
    if( (date < 32) & (date > 0) )
    {
      if(i2c(DS3231_ADDR,0x04,1,0,&time2reg(date),1) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_month(unsigned char month)
{
    if( (month < 13) & (month > 0) )
    {
      if(i2c(DS3231_ADDR,0x05,1,0,&time2reg(month),1) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_year(unsigned char year)
{
    if(year < 100)
    {
      if(i2c(DS3231_ADDR,0x06,1,0,&time2reg(year),1) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_alarm_1_according_to_second(unsigned char second)
{
    if(second < 60)
    {
      if(i2c(DS3231_ADDR,0x07,1,0,&time2reg(second),1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x07) ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_1_according_to_minute(unsigned char minute)
{
    if(minute < 60)
    {
      if(i2c(DS3231_ADDR,0x08,1,0,&time2reg(minute),1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x08) ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_1_according_to_hour(unsigned char hour)
{
    if(hour < 60)
    {
      if(i2c(DS3231_ADDR,0x09,1,0,&time2reg(hour),1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x09) ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_1_according_to_day(unsigned char day)
{
    if( (day < 8) & (day > 0) )
    {
      if(i2c(DS3231_ADDR,0x0A,1,0,&day,1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x0A) ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_1_according_to_date(unsigned char date)
{
    unsigned char x;
    if( (date < 32) & (date > 0) )
    {
      x = ( time2reg(date) | (1 << 6) );
      if(i2c(DS3231_ADDR,0x0A,1,0,&x,1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x0A) ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}
unsigned char write_ds3231_alarm_2_according_to_minute(unsigned char minute)
{
    if(minute < 60)
    {
      if(i2c(DS3231_ADDR,0x0B,1,0,&time2reg(minute),1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x0B) ; (f < 0x0E) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_2_according_to_hour(unsigned char hour)
{
    if(hour < 60)
    {
      if(i2c(DS3231_ADDR,0x0C,1,0,&time2reg(hour),1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x0C) ; (f < 0x0E) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_2_according_to_day(unsigned char day)
{
    if( (day < 8) & (day > 0) )
    {
      if(i2c(DS3231_ADDR,0x0D,1,0,&day,1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x0D) ; (f < 0x0E) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_2_according_to_date(unsigned char date)
{
    unsigned char x;
    if( (date < 32) & (date > 0) )
    {
      x = ( time2reg(date) | (1 << 6) );
      if(i2c(DS3231_ADDR,0x0D,1,0,&x,1) == ERR)
      {
        return ERROR;
      }
      for(f = (0x0D) ; (f < 0x0E) ; f++)
      {
        if(i2c(DS3231_ADDR,f,1,0,(1 << 7),1) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

static unsigned char time2reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

static unsigned char reg2time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}

static void raw_to_ds_t(ds_t * ds,unsigned char array[19])
{
  // UPPERLINE IS 0 -->> WITHOUT UPPERLINE IS 1
  ds.second = reg2time(array[0]);
  ds.minute = reg2time(array[1]);
  ds.hour__am_pm = reg2time(array[2]);
  ds.week_day = saat[3];
  ds.month_date_day = reg2time(array[4]);
  ds.month__century = reg2time((array[5] & 0x7F));
  ds.year = reg2time(array[6]);
  ds.alarm1_second = reg2time((array[7] & 0x7F));
  ds.alarm1_minute = reg2time((array[8] & 0x7F));
  ds.alarm1_hour__am_pm = reg2time((array[9] & 0x7F));
  if(array[10] & 0x40)
     {
       ds.alarm1_month_week_day = array[10] & 0x7;
     }
  else
     {
       ds.alarm1_month_week_day = reg2time((array[10] & 0x7F));
     }
  ds.alarm2_minute = reg2time(array[11]);
  ds.alarm2_hour__am_pm = reg2time(array[12]);
  if(array[13] & 0x40)
     {
       ds.alarm2_month_week_day = array[13] & 0x7;
     }
  else
     {
       ds.alarm2_month_week_day = reg2time((array[13] & 0x7F));
     }
  ds.control = array[14];
  ds.status = array[15];
  ds.aging_offset = array[16];
  ds.msb_temperature = array[17];
  ds.lsb_temperature = array[18];
}
