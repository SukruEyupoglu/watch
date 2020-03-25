

#define DS3231_ADDR             0x68

// FLASH HAVE 3_BYTE BOUNDARY ADDRESS SIZE
// E2PROM HAVE 2_BYTE BOUNDARY ADDRESS SIZE
// DS3231 HAVE BYTE BOUNDARY ADDRESS SIZE
#define DS3231_ADDR_SIZE 1

#define WRITING_NUMBER 1
#define READING_NUMBER 1

#define DS3231_SECOND_OUT_OF_RANGE        60
#define DS3231_MINUTE_OUT_OF_RANGE        60
#define DS3231_HOUR_OUT_OF_RANGE          24
#define DS3231_DAY_OUT_OF_UP_RANGE        8
#define DS3231_DAY_OUT_OF_DOWN_RANGE      0
#define DS3231_DATE_OUT_OF_UP_RANGE       32
#define DS3231_DATE_OUT_OF_DOWN_RANGE     0

#define ERR 1
#define ERROR 1
#define OK 0

#define ZERO 0
#define ONE 1

#define READ 1
#define WRITE 0

#define CTRL_EOSC         (1 << 7)        // COMMINICATION OSCILATOR ENABLE DISABLE NO EFFECT TO TIMING
                                          // WHEN VCC POWER UP THIS OSCILATOR ALWAYS ENABLE
                                          // WHEN THERE IS VBAT ONLY , THIS OSCILATOR STOPPED AUTOMATICALLY
#define CTRL_BBSQW        (1 << 6)        // SQUARE-WAVE CLOK OUT ENABLE - DISABLE , AFTER RESET DISABLE
#define CTRL_CONV         (1 << 5)        // START TEMP CONVERSION
#define CTRL_RS2          (1 << 4)        // SQUARE-WAVE FREQUENCY SELECT BIT
#define CTRL_RS1          (1 << 3)        // SQUARE-WAVE FREQUENCY SELECT BIT
#define CTRL_INTCN        (1 << 2)        // INTERRUPT OUTPUT OR SQUARE-WAVE SELECT REGISTER
                                          // AFTER RESET INTERRUPT OUTPUT AUTOMATICALLY SELECTED
#define CTRL_A2IE         (1 << 1)        // ALARM_2 INTERRUPT ENABLE
#define CTRL_A1IE         (1 << 0)        // ALARM_1 INTERRUPT ENABLE

#define STAT_OSF          (1 << 7)        // OSCILATION STOP FLAG STATUS
                                          // THIS BIT REMAIN 1 UNTIL WRITE 0
#define STAT_EN32kHz      (1 << 3)        // 32kHz STATUS BIT
#define STAT_BSY          (1 << 2)        // DEVICE BUSY BIT
#define STAT_A2F          (1 << 1)        // ALARM_2 STATUS FLAG , WRITE 0 TO CLEAR THIS BIT
#define STAT_A1F          (1 << 0)        // ALARM_1 STATUS FLAG , WRITE 0 TO CLEAR THIS BIT


/*
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

*/


#define DS3231_SECOND_REG                   0x00
#define DS3231_MINUTE_REG                   0x01
#define DS3231_HOUR_REG                     0x02
#define DS3231_DAY_REG                      0x03
#define DS3231_DATE_REG                     0x04
#define DS3231_MONTH_REG                    0x05
#define DS3231_YEAR_REG                     0x06

#define DS3231_A1_REG_COUNT                 4
#define DS3231_A1_START_REG                 0x07
#define DS3231_A1_SECOND_REG                0x07
#define DS3231_A1_MINUTE_REG                0x08
#define DS3231_A1_HOUR_REG                  0x09
#define DS3231_A1_DAY_REG                   0x0A
#define DS3231_A1_DATE_REG                  0x0A
#define DS3231_A1_END_REG                   0x0A

#define DS3231_A2_REG_COUNT                 3
#define DS3231_A2_START_REG                 0x0B
#define DS3231_A2_MINUTE_REG                0x0B
#define DS3231_A2_HOUR_REG                  0x0C
#define DS3231_A2_DAY_REG                   0x0D
#define DS3231_A2_DATE_REG                  0x0D
#define DS3231_A2_END_REG                   0x0D

#define DS3231_CONTROL_REG                  0x0E
#define DS3231_STATUS_REG                   0x0F
#define DS3231_AGING_OFFSET_REG             0x10
#define DS3231_MSB_TEMP_REG                 0x11
#define DS3231_LSB_TEMP_REG                 0x12

unsigned char write_ds3231_second(unsigned char second);
unsigned char write_ds3231_minute(unsigned char minute);
unsigned char write_ds3231_hour(unsigned char hour);
unsigned char write_ds3231_day(unsigned char day);
unsigned char write_ds3231_date(unsigned char date);
unsigned char write_ds3231_month(unsigned char month);
unsigned char write_ds3231_year(unsigned char year);

unsigned char start_temp_conversion(void);
unsigned char read_ds3231_temp(unsigned char * temp_msb, unsigned char * temp_lsb);

unsigned char write_ds3231_control(unsigned char control);
unsigned char read_ds3231_conrol(unsigned char * control);

unsigned char write_ds3231_status(unsigned char status);
unsigned char read_ds3231_status(unsigned char * status);

unsigned char close_ds3231_alarm_1(void);
unsigned char close_ds3231_alarm_2(void);

unsigned char write_ds3231_alarm_1_according_to_second(unsigned char second);
unsigned char write_ds3231_alarm_1_according_to_minute(unsigned char minute);
unsigned char write_ds3231_alarm_1_according_to_hour(unsigned char hour);
unsigned char write_ds3231_alarm_1_according_to_day(unsigned char day);
unsigned char write_ds3231_alarm_1_according_to_date(unsigned char date);

unsigned char write_ds3231_alarm_2_according_to_minute(unsigned char minute);
unsigned char write_ds3231_alarm_2_according_to_hour(unsigned char hour);
unsigned char write_ds3231_alarm_2_according_to_day(unsigned char day);
unsigned char write_ds3231_alarm_2_according_to_date(unsigned char date);

unsigned char read_ds3231_second(unsigned char * second);
unsigned char read_ds3231_minute(unsigned char * minute);
unsigned char read_ds3231_hour(unsigned char * hour);
unsigned char read_ds3231_day(unsigned char * day);
unsigned char read_ds3231_date(unsigned char * date);
unsigned char read_ds3231_month(unsigned char * month);
unsigned char read_ds3231_year(unsigned char * year);

unsigned char read_ds3231_alarm_1_second(unsigned char * second);
unsigned char read_ds3231_alarm_1_minute(unsigned char * minute);
unsigned char read_ds3231_alarm_1_hour(unsigned char * hour);
unsigned char read_ds3231_alarm_1_day(unsigned char * day);
unsigned char read_ds3231_alarm_1_date(unsigned char * date);

unsigned char read_ds3231_alarm_2_second(unsigned char * second);
unsigned char read_ds3231_alarm_2_minute(unsigned char * minute);
unsigned char read_ds3231_alarm_2_hour(unsigned char * hour);
unsigned char read_ds3231_alarm_2_day(unsigned char * day);
unsigned char read_ds3231_alarm_2_date(unsigned char * date);

// static unsigned char time2reg(unsigned char time);
// static unsigned char reg2time(unsigned char reg);
// static void raw_to_ds_t(ds_t * ds,unsigned char array[19]);




