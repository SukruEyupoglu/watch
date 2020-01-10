#include "stm8s.h"
#include "eeprom.h"

#define EEPROM_START_ADDR 0x4000
#define EEPROM_END_ADDR 0x407F

void eeprom_unlock(void) {
    FLASH_DUKR = FLASH_DUKR_KEY1;
    FLASH_DUKR = FLASH_DUKR_KEY2;
    while (!(FLASH_IAPSR & (1 << FLASH_IAPSR_DUL)));
}

void eeprom_lock(void) {
    FLASH_IAPSR &= ~(1 << FLASH_IAPSR_DUL);
}

void eeprom_wait_busy(void) {
    while (!(FLASH_IAPSR & (1 << FLASH_IAPSR_EOP)));
}
// len max 255 because of stm8s003-----beware end addr
void eeprom_read(unsigned char addr, unsigned char * data, unsigned char len)
{
  unsigned char f;
  for (f = 0 ; f < len; f++)
  {
        data[f] = _MEM_(addr + f + EEPROM_START_ADDR);
        eeprom_wait_busy();
  }
}
// len max 255 because of stm8s003-----beware end addr
void eeprom_write(unsigned char addr, unsigned char * data, unsigned char len)
{
  unsigned char f;
  for (f = 0 ; f < len; f++)
  {
        _MEM_(addr + f + EEPROM_START_ADDR) = data[f];
        eeprom_wait_busy();
  }
}


