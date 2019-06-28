
#define WRITE_ENABLE_COMMAND 0x06
#define WRITE_DISABLE_COMMAND 0x04
#define CHIP_ERASE_COMMAND 0xC7
#define READ_ID_COMMAND 0x9F
#define READ_STATUS_COMMAND 0x05
#define PAGE_WRITE_COMMAND 0x02
#define READ_DATA_COMMAND 0x03
#define ERASE_4KB_SECTOR_COMMAND 0xD8
#define ERASE_64KB_SUBSECTOR_COMMAND 0x20
// spi_init();
void erase_all_external_spi_flash(void)
{
  CS_LOW;
  spi(WRITE_ENABLE_COMMAND);  // for write anythink set this register
  CS_HIGH;
  CS_LOW;
  spi(CHIP_ERASE_COMMAND);  // for erase all chip
  CS_HIGH;
}
