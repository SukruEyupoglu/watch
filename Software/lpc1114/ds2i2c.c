



const unsigned char month_day [12] = { 31,29,31,30,31,30,31,31,30,31,30,31 }; // 1 year 366 day
#define DS_ADDR             0x68
struct ds 
  {
  unsigned char second;
  unsigned char minute;
  unsigned char hour__am_pm;
  unsigned char week_day;
  unsigned char month_date_day;
  unsigned char month__century;
  unsigned char year;
  unsigned char alarm1_second;
  unsigned char alarm1_minute;
  unsigned char alarm1_hour__am_pm;
  unsigned char alarm1_month_week_day;
  unsigned char alarm2_minute;
  unsigned char alarm2_hour__am_pm;
  unsigned char alarm2_month_week_day;
  unsigned char control;
  unsigned char status;
  unsigned char aging_offset;
  unsigned char msb_temperature;
  unsigned char lsb_temperature;
  }
void led_write_janjan(unsigned char led[12])
{
unsigned char i;  
for(i = 0 ; i < 12 ; i++)
{
    spi(led[i]);
}
}
  
  
  
  
