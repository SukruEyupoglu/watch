

#define DS3231_ADDR             0x68

// FLASH HAVE 3_BYTE BOUNDARY ADDRESS SIZE
// E2PROM HAVE 2_BYTE BOUNDARY ADDRESS SIZE
// DS3231 HAVE BYTE BOUNDARY ADDRESS SIZE
#define DS3231_ADDR_SIZE 1

#define WRITING_NUMBER 1
#define READING_NUMBER 1

#define ERROR 1
#define OK 0

#define READ 1
#define WRITE 0

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

#define DS3231_SECOND_REG                   0x00
#define DS3231_MINUTE_REG                   0x01
#define DS3231_HOUR_REG                     0x02
#define DS3231_DAY_REG                      0x03
#define DS3231_DATE_REG                     0x04
#define DS3231_MONTH_REG                    0x05
#define DS3231_YEAR_REG                     0x06
#define DS3231_A1_SECOND_REG                0x07
#define DS3231_A1_MINUTE_REG                0x08
#define DS3231_A1_HOUR_REG                  0x09
#define DS3231_A1_DAY_REG                   0x0A
#define DS3231_A1_DATE_REG                  0x0A
#define DS3231_A2_MINUTE_REG                0x0B
#define DS3231_A2_HOUR_REG                  0x0C
#define DS3231_A2_DAY_REG                   0x0D
#define DS3231_A2_DATE_REG                  0x0D
#define DS3231_CONTROL_REG                  0x0E
#define DS3231_STATUS_REG                   0x0F
#define DS3231_AGING_OFFSET_REG             0x10
#define DS3231_MSB_TEMP_REG                 0x11
#define DS3231_LSB_TEMP_REG                 0x12

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




