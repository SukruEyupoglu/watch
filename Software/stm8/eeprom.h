





#define EEPROM_START_ADDR     0x4000
#define EEPROM_END_ADDR       0x407F



#define CONFIG_EE_ADDR			0x0A
#define EN_AA_EE_ADDR			0x0B
#define EN_RXADDR_EE_ADDR		0x0C
#define SETUP_AW_EE_ADDR		0x0D
#define SETUP_RETR_EE_ADDR		0x0E
#define RF_CH_EE_ADDR			0x0F
#define RF_SETUP_EE_ADDR		0x10
#define RX_ADDR_P0_EE_ADDR		0x11 // 5 byte length
#define RX_ADDR_P1_EE_ADDR		0x16 // 5 byte length
#define RX_ADDR_P2_EE_ADDR		0x1B
#define RX_ADDR_P3_EE_ADDR		0x1C
#define RX_ADDR_P4_EE_ADDR		0x1D
#define RX_ADDR_P5_EE_ADDR		0x1E
#define TX_ADDR_EE_ADDR			0x1F // 5 byte length
#define RX_PW_P0_EE_ADDR		0x25
#define RX_PW_P1_EE_ADDR		0x26
#define RX_PW_P2_EE_ADDR		0x27
#define RX_PW_P3_EE_ADDR		0x28
#define RX_PW_P4_EE_ADDR		0x29
#define RX_PW_P5_EE_ADDR		0x2A
#define DYNPD_EE_ADDR			0x2B
#define FEATURE_EE_ADDR   0x2C


void eeprom_unlock(void);
void eeprom_lock(void);
void eeprom_wait_busy(void);
void eeprom_read(unsigned char addr, unsigned char * data, unsigned char len);
void eeprom_write(unsigned char addr, unsigned char * data, unsigned char len);








