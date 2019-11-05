#define E2PROM_ADDR                                       0xA2              // DEVICE ADDR FOR I2C
#define E2PROM_END_ADDR                                   0xFFF             // MAX ADDR



#define E2PROM_NAMAZ_ALERT_SETTING_ADDR                   0x001             // 1 or 0
#define E2PROM_SABAH_NAMAZI_ALERT_SETTING_ADDR            0x002             // 1 or 0
#define E2PROM_GUNES_NAMAZI_ALERT_SETTING_ADDR            0x003             // 1 or 0
#define E2PROM_OGLE_NAMAZI_ALERT_SETTING_ADDR             0x004             // 1 or 0
#define E2PROM_IKINDI_NAMAZI_ALERT_SETTING_ADDR           0x005             // 1 or 0
#define E2PROM_AKSAM_NAMAZI_ALERT_SETTING_ADDR            0x006             // 1 or 0
#define E2PROM_YATSI_NAMAZI_ALERT_SETTING_ADDR            0x007             // 1 or 0
#define BEFORE_NAMAZ_SETTING_ADDR                         0x008             // 1 or 0
#define MINUTE_FOR_BEFORE_NAMAZ_SETTING_ADDR              0x009             // max 60 minute
#define EXTRA_ALRT_NUMBER_SETTING_ADDR                    0x00A             // max 10 alert
#define HOURLY_ALERT_SETTING_ADDR                         0x00B             // 1 or 0
#define NUMBER_HOURLY_ALERT_SETTING_ADDR                  0x00C             // 1 or 2 or 3 or 4 or 6 or 12 or 24
#define EXTRA_ALARM_START_ADDR                            0x03D             // 61                // 
#define EXTRA_ALARM_LAST_ADDR                             0x064             // 100                // 
