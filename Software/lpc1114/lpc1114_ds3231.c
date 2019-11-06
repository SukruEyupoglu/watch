#include "lpc1114_i2c.h"
#include "lpc1114_error.h"
#include "lpc1114_ds3231.h"

void read_ds3231_data(void)
{
  // volatile ds3231; // at main file
  // DS3231 HAS 19 REGISTER
  unsigned char saat[19];
  //READ ALL REGISTER AND SAVE TO RAW ARRAY  
  if(i2c(DS3231_ADDR,0,1,1,saat,19) == ERR)
  {
    error();
  }
  // CONVERT RAW REGISTER DATA TO REASONABLE DATA
  raw_to_ds_t(&ds3231,saat);
}

void write_ds3231_clock(void)
{
  
}
void write_ds3231_alarm_1(void)
{
  
}
void write_ds3231_alarm_2(void)
{
  
}


void write_ds3231_data(unsigned char * data,unsigned char size,unsigned int start_addr)
{
  if(i2c(DS3231_ADDR,start_addr,1,0,data,size) == ERR)
  {
    error();
  }
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
