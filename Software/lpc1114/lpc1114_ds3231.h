

#define DS3231_ADDR             0x68

#define ERROR 1
#define OK 0

#define TIMING_TYPE_1_PROPER_SECOND       0x07
#define TIMING_TYPE_1_PROPER_MINUTE       0x08
#define TIMING_TYPE_1_PROPER_HOUR         0x09
#define TIMING_TYPE_1_PROPER_DAY          0x0A

#define TIMING_TYPE_2_PROPER_MINUTE       0x0B
#define TIMING_TYPE_2_PROPER_HOUR         0x0C
#define TIMING_TYPE_2_PROPER_DAY          0x0D

typedef struct ds_t
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

const unsigned char month_day [12] = { 31,29,31,30,31,30,31,31,30,31,30,31 }; // 1 year 366 day

#define DS3231_second                     0x00
#define DS3231_minute                     0x01
#define DS3231_hour__am_pm                0x02
#define DS3231_week_day                   0x03
#define DS3231_month_date_day             0x04
#define DS3231_month__century             0x05
#define DS3231_year                       0x06
#define DS3231_alarm1_second              0x07
#define DS3231_alarm1_minute              0x08
#define DS3231_alarm1_hour__am_pm         0x09
#define DS3231_alarm1_month_week_day      0x0A
#define DS3231_alarm2_minute              0x0B
#define DS3231_alarm2_hour__am_pm         0x0C
#define DS3231_alarm2_month_week_day      0x0D
#define DS3231_control                    0x0E
#define DS3231_status                     0x0F
#define DS3231_aging_offset               0x10
#define DS3231_msb_temperature            0x11
#define DS3231_lsb_temperature            0x12

unsigned char write_ds3231_alarm_1(unsigned char timing_type_1,unsigned char time);
unsigned char write_ds3231_alarm_2(unsigned char timing_type_2,unsigned char time);

unsigned char write_ds3231_second(unsigned char second);
unsigned char write_ds3231_minute(unsigned char minute);
unsigned char write_ds3231_hour(unsigned char hour);
unsigned char write_ds3231_day(unsigned char day);
unsigned char write_ds3231_date(unsigned char date);
unsigned char write_ds3231_month(unsigned char month);
unsigned char write_ds3231_year(unsigned char year);
  
void read_ds3231_data(void);

static unsigned char time2reg(unsigned char time);
static unsigned char reg2time(unsigned char reg);
static void raw_to_ds_t(ds_t * ds,unsigned char array[19]);




