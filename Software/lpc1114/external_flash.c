
#define WRITE_ENABLE_REGISTER 0x06
#define CHIP_ERASE_COMMAND 0xC7
// spi_init();
void erase_all_external_spi_flash(void)
{
  CS_LOW;
  spi(WRITE_ENABLE_REGISTER);  // for write anythink set this register
  CS_HIGH;
  CS_LOW;
  spi(CHIP_ERASE_COMMAND);  // for erase all chip
  CS_HIGH;
}
