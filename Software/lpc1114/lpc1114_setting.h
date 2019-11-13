#define HOUR_SELECT 0
#define MINUTE_SELECT 1

#define CLOCK 0
#define AL1 1
#define AL2 2

#define ERR 1
#define ERROR 1

#define OK 0

unsigned char ds3231_clock_setting(unsigned char select_clock_alarm1_alarm2);
unsigned char increase_minute(unsigned char minute);
unsigned char reduce_minute(unsigned char minute);
unsigned char increase_hour(unsigned char hour);
unsigned char reduce_hour(unsigned char hour);
