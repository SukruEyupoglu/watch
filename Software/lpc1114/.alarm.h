/*
#define scream 1
#define quiet 0
// array for using settings start 0x001 not 0x000 and 0x000 is empty
// all address stored  +1 to arrays
#define E2PROM_NAMAZ_ALERT_SETTING_ADDR 0x001             // 1 or 0
#define E2PROM_SABAH_NAMAZI_ALERT_SETTING_ADDR 0x002      // 1 or 0
#define E2PROM_GUNES_NAMAZI_ALERT_SETTING_ADDR 0x003      // 1 or 0
#define E2PROM_OGLE_NAMAZI_ALERT_SETTING_ADDR 0x004       // 1 or 0
#define E2PROM_IKINDI_NAMAZI_ALERT_SETTING_ADDR 0x005     // 1 or 0
#define E2PROM_AKSAM_NAMAZI_ALERT_SETTING_ADDR 0x006      // 1 or 0
#define E2PROM_YATSI_NAMAZI_ALERT_SETTING_ADDR 0x007      // 1 or 0
#define BEFORE_NAMAZ_SETTING_ADDR 0x008                   // 1 or 0
#define MINUTE_FOR_BEFORE_NAMAZ_SETTING_ADDR 0x009        // max 60 minute
#define EXTRA_ALRT_NUMBER_SETTING_ADDR 0x00A              // max 10 alert
#define HOURLY_ALERT_SETTING_ADDR 0x00B                   // 1 or 0
#define NUMBER_HOURLY_ALERT_SETTING_ADDR 0x00C            // 1 or 2 or 3 or 4 or 6 or 12 or 24
#define EXTRA_ALARM_START_ADDR 0x03D // 61                // 
#define EXTRA_ALARM_LAST_ADDR 0x064 // 100                // 
*/
/*
#define e2prom_addr 0xA2
#define eeprom_last_addr 0xFFF
// 0xFFF = 4095
// 8. byte alert before namaz time if 1 look at 9. byte for how many minute
// 9. byte minute for prepare for namaz default 0
#define before_namaz_alert_addr 0x008
#define minute_for_before_namaz_alert_addr 0x009
// A. byte exta alert number how many alert saved read from here
#define how_many_extra_alert_addr 0x00A
// extra alarm start addr 0x03D == 61
// max extra alarm = 10
0x03D = dakika
0x03E = saat
0x03F = gun
0x040 = ay
if gun and ay equal to zero then daily alarm so every day of year
*/


unsigned char check_alarm(ds_t * ds3231,unsigned char * eeprom_data);
unsigned char check_ds3231_alert(unsigned char dakika,unsigned char saat,unsigned char alarm_dakika,unsigned char alarm_saat);
unsigned char check_eeprom_alert(unsigned char dakika,unsigned char saat,unsigned char gun,unsigned char ay,unsigned char * number);
unsigned char check_namaz_for_alert(unsigned char dakika,unsigned char saat,unsigned char gun,unsigned char ay,unsigned char * ayar);






