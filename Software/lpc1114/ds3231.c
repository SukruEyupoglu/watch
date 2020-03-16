#include "lpc1114_i2c.h"
#include "lpc1114_ds3231.h"

static unsigned char time2reg(unsigned char time);
static unsigned char reg2time(unsigned char reg);

// EVERY MINUTE WAKE-UP LPC1114
unsigned char ds3231_every_minute_alarm_init(void)
{
	unsigned char con = 0;
	// SET ALARM 1 ENABLE AND ENABLE INTERRUPT OUTPUT
	if(read_ds3231_control(&con) == ERR)
	{
		return ERROR;
	}
	if( !(con & (1 << DS3231_CONTROL_INTCN) ) )
	{
		// SET ALARM 1 TIME TO EVERY MINUTE
		if(write_ds3231_alarm_1_according_to_second(EVERY_MINUTE) == ERR)
		{
			return ERROR;
		}
		// SET ALARM 1 ENABLE AND ENABLE INTERRUPT OUTPUT
		if(write_ds3231_control( (1 << DS3231_CONTROL_INTCN) | (1 << DS3231_CONRTOL_A1IE) ) == ERR)
		{
			return ERROR;
		}
	}
	return OK;
}


unsigned char start_temp_conversion(void)
{
    unsigned char x,y;
    if( read_ds3231_status(&y) == ERR)
    {
        return ERROR;
    }
    if( read_ds3231_conrol(&x) == ERR)
    {
        return ERROR;
    }
    if( !( (y & STAT_BSY) | (x & CTRL_CONV) ) )
    {
        x |= CTRL_CONV;
        if(i2c(DS3231_ADDR & 0xFE,DS3231_CONTROL_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
            return ERROR;
        }
    }
    return OK;        
}

// NOKTADAN ONCESI MSB NOKTADAN SONRASI 25 ILE CARPILARAK LSB DIR
// MSB = DEGREE LSB*25 = PRECENT --> MSB = 20 , PERCENT = 50 --> 20.50 DEGREE
unsigned char read_ds3231_temp(unsigned char * temp_msb, unsigned char * temp_lsb)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_MSB_TEMP_REG,DS3231_ADDR_SIZE,temp_msb,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    if(i2c(DS3231_ADDR | 0x01,DS3231_LSB_TEMP_REG,DS3231_ADDR_SIZE,temp_lsb,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * temp_lsb >>= 6;
    return OK;
}

unsigned char write_ds3231_control(unsigned char control)
{
    if(i2c(DS3231_ADDR & 0xFE,DS3231_CONTROL_REG,DS3231_ADDR_SIZE,&control,WRITING_NUMBER) == ERR)
    {
        return ERROR;
    }
    return OK;    
}

unsigned char read_ds3231_conrol(unsigned char * control)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_CONTROL_REG,DS3231_ADDR_SIZE,control,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    return OK;
}

unsigned char write_ds3231_status(unsigned char status)
{
    if(i2c(DS3231_ADDR & 0xFE,DS3231_STATUS_REG,DS3231_ADDR_SIZE,&status,WRITING_NUMBER) == ERR)
    {
        return ERROR;
    }
    return OK;    
}

unsigned char read_ds3231_status(unsigned char * status)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_STATUS_REG,DS3231_ADDR_SIZE,status,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    return OK;
}

unsigned char write_ds3231_second(unsigned char second)
{
	unsigned char x;
    if(second < 60)
    {
    	x = time2reg(second);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_SECOND_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_minute(unsigned char minute)
{
	unsigned char x;
    if(minute < 60)
    {
    	x = time2reg(minute);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_MINUTE_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_hour(unsigned char hour)
{
	unsigned char x;
    if(hour < 24)
    {
    	x = time2reg(hour);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_HOUR_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_day(unsigned char day)
{
	unsigned char x;
    if( (day < 8) & (day > 0) )
    {
    	x = time2reg(day);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_DAY_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_date(unsigned char date)
{
	unsigned char x;
    if( (date < 32) & (date > 0) )
    {
    	x = time2reg(date);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_DATE_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_month(unsigned char month)
{
	unsigned char x;
    if( (month < 13) & (month > 0) )
    {
    	x = time2reg(month);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_MONTH_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char write_ds3231_year(unsigned char year)
{
	unsigned char x;
    if(year < 100)
    {
    	x = time2reg(year);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_YEAR_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
    }
  return OK;
}

unsigned char close_ds3231_alarm_1(void)
{
    // WRITE ZERO TO ALL ALARM REGISTERS
    if(i2c(DS3231_ADDR & 0xFE,DS3231_A1_START_REG,DS3231_ADDR_SIZE,ZERO,DS3231_A1_REG_COUNT) == ERR)
    {
      return ERROR;
    }
    return OK;
}

unsigned char close_ds3231_alarm_2(void)
{
    // WRITE ZERO TO ALL ALARM REGISTERS
    if(i2c(DS3231_ADDR & 0xFE,DS3231_A2_START_REG,DS3231_ADDR_SIZE,ZERO,DS3231_A2_REG_COUNT) == ERR)
    {
      return ERROR;
    }
    return OK;
}


unsigned char write_ds3231_alarm_1_according_to_second(unsigned char second)
{
	unsigned char f,x;
    if(second < 60)
    {
    	x = time2reg(second);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A1_SECOND_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A1_SECOND_REG ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_1_according_to_minute(unsigned char minute)
{
	unsigned char f,x;
    if(minute < 60)
    {
    	x = time2reg(minute);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A1_MINUTE_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A1_MINUTE_REG ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_1_according_to_hour(unsigned char hour)
{
	unsigned char f,x;
    if(hour < 24)
    {
    	x = time2reg(hour);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A1_HOUR_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A1_HOUR_REG ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_1_according_to_day(unsigned char day)
{
	unsigned char f,x;
    if( (day < 8) & (day > 0) )
    {
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A1_DAY_REG,DS3231_ADDR_SIZE,&day,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A1_DAY_REG ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_1_according_to_date(unsigned char date)
{
	unsigned char f,x;
    if( (date < 32) & (date > 0) )
    {
      x = ( time2reg(date) | (1 << 6) );
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A1_DATE_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A1_DATE_REG ; (f < 0x0B) ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}
unsigned char write_ds3231_alarm_2_according_to_minute(unsigned char minute)
{
	unsigned char f,x;
    if(minute < 60)
    {
    	x = time2reg(minute);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A2_MINUTE_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A2_MINUTE_REG ; (f < 0x0E) ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_2_according_to_hour(unsigned char hour)
{
	unsigned char f,x;
    if(hour < 60)
    {
    	x = time2reg(hour);
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A2_HOUR_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A2_HOUR_REG ; f < 0x0E ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_2_according_to_day(unsigned char day)
{
	unsigned char f,x;
    if( (day < 8) & (day > 0) )
    {
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A2_DAY_REG,DS3231_ADDR_SIZE,&day,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A2_DAY_REG ; f < 0x0E ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
        {
          return ERROR;
        }
      }  
    }
    return OK;
}

unsigned char write_ds3231_alarm_2_according_to_date(unsigned char date)
{
    unsigned char x,f;
    if( (date < 32) & (date > 0) )
    {
      x = ( time2reg(date) | (1 << 6) );
      if(i2c(DS3231_ADDR & 0xFE,DS3231_A2_DATE_REG,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
      {
        return ERROR;
      }
      x = (1 << 7);
      for(f = DS3231_A2_DATE_REG ; f < 0x0E ; f++)
      {
        if(i2c(DS3231_ADDR & 0xFE,f,DS3231_ADDR_SIZE,&x,WRITING_NUMBER) == ERR)
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

/*
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
*/

unsigned char read_ds3231_second(unsigned char * second)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_SECOND_REG,DS3231_ADDR_SIZE,second,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * second = reg2time(* second);
    return OK;
}

unsigned char read_ds3231_minute(unsigned char * minute)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_MINUTE_REG,DS3231_ADDR_SIZE,minute,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * minute = reg2time(* minute);
    return OK;
}

unsigned char read_ds3231_hour(unsigned char * hour)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_HOUR_REG,DS3231_ADDR_SIZE,hour,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * hour = reg2time(* hour);
    return OK;
}

unsigned char read_ds3231_day(unsigned char * day)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_DAY_REG,DS3231_ADDR_SIZE,day,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    return OK;
}

unsigned char read_ds3231_date(unsigned char * date)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_DATE_REG,DS3231_ADDR_SIZE,date,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * date = reg2time(* date);
    return OK;
}

unsigned char read_ds3231_month(unsigned char * month)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_MONTH_REG,DS3231_ADDR_SIZE,month,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * month = reg2time(* month) & 0x7F;
    return OK;
}

unsigned char read_ds3231_year(unsigned char * year)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_YEAR_REG,DS3231_ADDR_SIZE,year,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * year = reg2time(* year);
    return OK;
}

unsigned char read_ds3231_alarm_1_second(unsigned char * second)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A1_SECOND_REG,DS3231_ADDR_SIZE,second,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * second = reg2time(* second) & 0x7F;
    return OK;
}

unsigned char read_ds3231_alarm_1_minute(unsigned char * minute)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A1_MINUTE_REG,DS3231_ADDR_SIZE,minute,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * minute = reg2time(* minute) & 0x7F;
    return OK;
}

unsigned char read_ds3231_alarm_1_hour(unsigned char * hour)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A1_HOUR_REG,DS3231_ADDR_SIZE,hour,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * hour = reg2time(* hour) & 0x7F;
    return OK;
}

unsigned char read_ds3231_alarm_1_day(unsigned char * day)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A1_DAY_REG,DS3231_ADDR_SIZE,day,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    if( * day & (1 << 6) )
    {
        * day = reg2time(* day) & 0x07;
    }
    else
    {
        * day = 0;
    }
    return OK;
}

unsigned char read_ds3231_alarm_1_date(unsigned char * date)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A1_DATE_REG,DS3231_ADDR_SIZE,date,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    if( * date & (1 << 6) )
    {
        * date = 0;
    }
    else
    {
        * date = reg2time(* date) & 0x3F;
    }
    return OK;
}

unsigned char read_ds3231_alarm_2_minute(unsigned char * minute)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A2_MINUTE_REG,DS3231_ADDR_SIZE,minute,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * minute = reg2time(* minute) & 0x7F;
    return OK;
}

unsigned char read_ds3231_alarm_2_hour(unsigned char * hour)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A2_HOUR_REG,DS3231_ADDR_SIZE,hour,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    * hour = reg2time(* hour) & 0x7F;
    return OK;
}

unsigned char read_ds3231_alarm_2_day(unsigned char * day)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A2_DAY_REG,DS3231_ADDR_SIZE,day,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    if( * day & (1 << 6) )
    {
        * day = reg2time(* day) & 0x07;
    }
    else
    {
        * day = 0;
    }
    return OK;
}

unsigned char read_ds3231_alarm_2_date(unsigned char * date)
{
    if(i2c(DS3231_ADDR | 0x01,DS3231_A2_DATE_REG,DS3231_ADDR_SIZE,date,READING_NUMBER) == ERR)
    {
      return ERROR;
    }
    if( * date & (1 << 6) )
    {
        * date = 0;
    }
    else
    {
        * date = reg2time(* date) & 0x3F;
    }
    return OK;
}




