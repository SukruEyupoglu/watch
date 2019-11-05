#define E2PROM_ADDR                                       0xA2              // DEVICE ADDR FOR I2C
#define E2PROM_END_ADDR                                   0xFFF             // MAX ADDR



#define E2PROM_NAMAZ_ALERT_SETTING_ADDR                   0x001             // 1 or 0 NAMAZ SAATLERINDE CALSINMI
#define E2PROM_ALL_NAMAZ_ALERT_SETTING_ADDR               0x002             // 1 or 0 BUTUN NAMAZ SAATLERINDE CALSINMI
                                                                            // BAZI NAMAZ SAATLERINDE CALACKSA HANGISI 
                                                                            // ASAGIDAKILERDEN SEC
#define E2PROM_SABAH_NAMAZI_ALERT_SETTING_ADDR            0x003             // 1 or 0 SABAH NAMAZI CALSIN VEYA CALMASIN
#define E2PROM_GUNES_NAMAZI_ALERT_SETTING_ADDR            0x004             // 1 or 0 GUNES DOGUSU CALSIN VEYA CALMASIN
#define E2PROM_OGLE_NAMAZI_ALERT_SETTING_ADDR             0x005             // 1 or 0 OGLE NAMAZI CALSIN VEYA CALMASIN
#define E2PROM_IKINDI_NAMAZI_ALERT_SETTING_ADDR           0x006             // 1 or 0 IKINDI NAMAZI CALSIN VEYA CALMASIN
#define E2PROM_AKSAM_NAMAZI_ALERT_SETTING_ADDR            0x007             // 1 or 0 AKSAM NAMAZI CALSIN VEYA CALMASIN
#define E2PROM_YATSI_NAMAZI_ALERT_SETTING_ADDR            0x008             // 1 or 0 YATSI NAMAZI CALSIN VEYA CALMASIN

#define BEFORE_NAMAZ_SETTING_ADDR                         0x009             // 1 or 0 NAMAZ SAATINDEMI YOKSA ONCEMI CALSIN
                                                                            // NE KADAR SURE ONCE CALSIN DAKIKA OLARAK
#define MINUTE_FOR_BEFORE_NAMAZ_SETTING_ADDR              0x00A             // EN FAZLA 255 DAKIKA ONCEDEN CALABILIR

#define REPEATED_ALARM_SETTING_ADDR                       0x00B             // 1 or 0 KOLAY UYANAMAYANLAR ICIN ALARM UZATMA
#define NUMBER_REPEATED_ALERT_SETTING_ADDR                0x00C             // 1 or 2 or 3 or 4 or 6 or 12 or 24

                                                                            // MSB+LSB = DUTY
#define LED_LIGHT_SETTING_DUTY_LSB_ADDR                   0x00D             // MAX 0xFF 
#define LED_LIGHT_SETTING_DUTY_MSB_ADDR                   0x00E             // MAX 0xFF 
#define LED_LIGHT_SETTING_PERCENT_ADDR                    0x00F             // DEFAULT %50 IF EMPTY MAX 99 MIN 1

#define HOURLY_ALERT_SETTING_ADDR                         0x010             // 1 or 0 HER SAAT BASI CALMA AYARI
#define TWO_HOURLY_ALERT_SETTING_ADDR                     0x011             // 1 or 0 HER IKI SAAT BASI CALMA AYARI
#define THREE_HOURLY_ALERT_SETTING_ADDR                   0x012             // 1 or 0 HER UC SAAT BASI CALMA AYARI
#define FOUR_HOURLY_ALERT_SETTING_ADDR                    0x013             // 1 or 0 HER DORT SAAT BASI CALMA AYARI
#define FIVE_HOURLY_ALERT_SETTING_ADDR                    0x014             // 1 or 0 HER BES SAAT BASI CALMA AYARI
#define SIX_HOURLY_ALERT_SETTING_ADDR                     0x015             // 1 or 0 HER ALTI SAAT BASI CALMA AYARI
#define TWEVE_HOURLY_ALERT_SETTING_ADDR                   0x016             // 1 or 0 HER ONIKI SAAT BASI CALMA AYARI
#define HOURLY_ALERT_START_SETTING_ADDR                   0x017             // SAAT BASI CALMA AYARI BASLANGIC SAATI
                                                                            // HANGI SAATTEN SONRA SAYMAYA BASLASIN

#define EXTRA_ALARM_COUNT_ADDR                            0x018              // BIRTDAY AND LIKE THAT DATES COUNT MAX 255
#define EXTRA_ALARM_START_ADDR                            0x100              // 1 BYTE MINUTE             MAX 59 MIN 0
                                                                             // 1 BYTE WATCH OR CLOCK     MAX 23 MIN 0
                                                                             // 1 BYTE DAY IN MOUNT       MAX 31 MIN 1
                                                                             // 3 BYTE TOTAL PER 1 SPECIAL DATE
                                                                             // 0x100 FIRST DATA

