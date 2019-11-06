#include "lpc1114_i2c.h"
#include "lpc1114_error.h"
#include "lpc1114_ds3231.h"

unsigned char read_ds3231_data(void)
{
  // volatile ds3231; // at main file
  // DS3231 HAS 19 REGISTER
  unsigned char saat[19];
  //READ ALL REGISTER AND SAVE TO RAW ARRAY  
  if(i2c(DS3231_ADDR,0,1,1,saat,19) == ERR)
  {
    return ERROR;
  }
  // CONVERT RAW REGISTER DATA TO REASONABLE DATA
  raw_to_ds_t(&ds3231,saat);
  return OK;
}
void read_ds3231_clock(void)
{
  
}
unsigned char write_ds3231_clock(
                                 unsigned char second,
                                 unsigned char minute,
                                 unsigned char hour,
                                 unsigned char day,
                                 unsigned char date,
                                 unsigned char month,
                                 unsigned char year
                                )
{
  if(second < 60)
  {
    if(i2c(DS3231_ADDR,0x00,1,0,&time2reg(second),1) == ERR)
    {
      return ERROR;
    }
  }
  if(minute < 60)
  {  
    if(i2c(DS3231_ADDR,0x01,1,0,&time2reg(minute),1) == ERR)
    {
      return ERROR;
    }
  }
  if(hour < 24)
  {  
    if(i2c(DS3231_ADDR,0x02,1,0,&time2reg(hour),1) == ERR)
    {
      return ERROR;
    }
  }
  if( (day < 8) & (day > 0) )
  {  
    if(i2c(DS3231_ADDR,0x03,1,0,&time2reg(day),1) == ERR)
    {
      return ERROR;
    }
  }
  if( (date < 32) & (date > 0) )
  {  
    if(i2c(DS3231_ADDR,0x04,1,0,&time2reg(date),1) == ERR)
    {
      return ERROR;
    }
  }
  if( (month < 13) & (month > 0) )
  {  
    if(i2c(DS3231_ADDR,0x05,1,0,&time2reg(month),1) == ERR)
    {
      return ERROR;
    }
  }
  if(year < 100)
  {  
    if(i2c(DS3231_ADDR,0x06,1,0,&time2reg(year),1) == ERR)
    {
      return ERROR;
    }
  }
  return OK;
}

// EVERY SECOND(SECONDLY),EVERY MINUTE(MINUTELY),EVERY HOUR(HOURLY),EVERY DAY(DAILY),SPECIAL DATE
// timing type secondly = 0x07, minutely = 0x08, hourly = 0x09 same as register adress
unsigned char write_ds3231_alarm_1(unsigned char timing_type_1,unsigned char time)
{
  if(i2c(DS3231_ADDR,timing_type,1,0,&time2reg(time),1) == ERR)
  {
    return ERROR;
  }
  if(i2c(DS3231_ADDR,(timing_type + 1),1,0,(1 << 7),1) == ERR)
  {
    return ERROR;
  }
  return OK;
}

// EVERY MINUTE(MINUTELY),EVERY HOUR(HOURLY),EVERY DAY(DAILY),SPECIAL DATE
// timing type minutely = 0x0B, hourly = 0x0C same as register adress
unsigned char write_ds3231_alarm_2(unsigned char timing_type_2,unsigned char time)
{
  if(i2c(DS3231_ADDR,timing_type,1,0,&time2reg(time),1) == ERR)
  {
    return ERROR;
  }
  if(i2c(DS3231_ADDR,(timing_type + 1),1,0,(1 << 7),1) == ERR)
  {
    return ERROR;
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
