#define E2PROM_ADDR                                       0xA2              // DEVICE ADDR FOR I2C
#define E2PROM_END_ADDR                                   0xFFF             // MAX ADDR



#define E2PROM_NAMAZ_ALERT_SETTING_ADDR                   0x001             // 1 or 0 NAMAZ SAATLERINDE CALSINMI
#define E2PROM_ALL_NAMAZ_ALERT_SETTING_ADDR               0x001             // 1 or 0 BUTUN NAMAZ SAATLERINDE CALSINMI
                                                                            // BAZI NAMAZ SAATLERINDE CALACKSA HANGISI 
                                                                            // ASAGIDAKILERDEN SEC
#define E2PROM_SABAH_NAMAZI_ALERT_SETTING_ADDR            0x002             // 1 or 0 SABAH NAMAZI CALSIN VEYA CALMASIN
#define E2PROM_GUNES_NAMAZI_ALERT_SETTING_ADDR            0x003             // 1 or 0 GUNES DOGUSU CALSIN VEYA CALMASIN
#define E2PROM_OGLE_NAMAZI_ALERT_SETTING_ADDR             0x004             // 1 or 0 OGLE NAMAZI CALSIN VEYA CALMASIN
#define E2PROM_IKINDI_NAMAZI_ALERT_SETTING_ADDR           0x005             // 1 or 0 IKINDI NAMAZI CALSIN VEYA CALMASIN
#define E2PROM_AKSAM_NAMAZI_ALERT_SETTING_ADDR            0x006             // 1 or 0 AKSAM NAMAZI CALSIN VEYA CALMASIN
#define E2PROM_YATSI_NAMAZI_ALERT_SETTING_ADDR            0x007             // 1 or 0 YATSI NAMAZI CALSIN VEYA CALMASIN

#define BEFORE_NAMAZ_SETTING_ADDR                         0x008             // 1 or 0 NAMAZ SAATINDEMI YOKSA ONCEMI CALSIN
                                                                            // NE KADAR SURE ONCE CALSIN DAKIKA OLARAK
#define MINUTE_FOR_BEFORE_NAMAZ_SETTING_ADDR              0x009             // EN FAZLA 255 DAKIKA ONCEDEN CALABILIR

#define HOURLY_ALERT_SETTING_ADDR                         0x00A             // HER SAAT BASI CALMA AYARI

#define REPEATED_ALARM_SETTING_ADDR                       0x00B             // 1 or 0 KOLAY UYANAMAYANLAR ICIN ALARM UZATMA
#define NUMBER_REPEATED_ALERT_SETTING_ADDR                0x00C             // 1 or 2 or 3 or 4 or 6 or 12 or 24

#define LED_LIGHT_SETTING_DUTY_ADDR                       0x03D             // MAX 0xFFFF 
#define LED_LIGHT_SETTING_PERCENT_ADDR                    0x064             // DEFAULT %50 IF EMPTY
