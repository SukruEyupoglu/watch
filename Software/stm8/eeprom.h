


#define EEPROM_START_ADDR 0x4000
#define EEPROM_END_ADDR 0x407F


void eeprom_unlock(void);
void eeprom_lock(void);
void eeprom_wait_busy(void);
void eeprom_read(unsigned char addr, unsigned char * data, unsigned char len);
void eeprom_write(unsigned char addr, unsigned char * data, unsigned char len);








