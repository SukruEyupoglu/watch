
#define SET_SECOND        0x00
#define SET_MINUTE        0x01
#define SET_HOUR          0x02
#define SET_WEEKDAY       0x03
#define SET_MONTHDAY      0x04
#define SET_MONTH         0x05
#define SET_YEAR          0x06


#define BUTTON_UP          201
#define BUTTON_DOWN       202
#define BUTTON_CANCEL     203
#define BUTTON_OK         204
#define BUTTON_WRITE      205

#define SKIP                0
#define WAIT_FOR_SETTING    1
#define EXIT                9
#define SET_ERROR           10


unsigned char setting_ds3231(void);
unsigned char set_second(void);
unsigned char set_minute(void);
unsigned char set_hour(void);
unsigned char set_weekday(void);
unsigned char set_monthday(void);
unsigned char set_month(void);
unsigned char set_year(void);



unsigned char increase_second(unsigned char second);
unsigned char reduce_second(unsigned char second);
unsigned char increase_minute(unsigned char minute);
unsigned char reduce_minute(unsigned char minute);
unsigned char increase_hour(unsigned char hour);
unsigned char reduce_hour(unsigned char hour);
unsigned char increase_weekday(unsigned char weekday);
unsigned char reduce_weekday(unsigned char weekday);
unsigned char increase_monthday(unsigned char monthday,unsigned char month_number,unsigned char year_number);
unsigned char reduce_monthday(unsigned char monthday,unsigned char month_number);
unsigned char increase_month(unsigned char month);
unsigned char reduce_month(unsigned char month);
unsigned char increase_year(unsigned char year);
unsigned char reduce_year(unsigned char year);

