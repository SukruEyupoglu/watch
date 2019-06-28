
#define WRITE_ENABLE_COMMAND 0x06
#define WRITE_DISABLE_COMMAND 0x04
#define CHIP_ERASE_COMMAND 0xC7
#define READ_ID_COMMAND 0x9F
#define READ_STATUS_COMMAND 0x05
#define PAGE_WRITE_COMMAND 0x02
#define READ_DATA_COMMAND 0x03
#define ERASE_4KB_SECTOR_COMMAND 0xD8
#define ERASE_64KB_SUBSECTOR_COMMAND 0x20
#define DUMMY_BYTE 0xFF
#define STATUS_BUSY          (1 << 0)
#define STATUS_WEL           (1 << 1)
#define STATUS_BP0           (1 << 2)
#define STATUS_BP1           (1 << 3)
#define STATUS_BP2           (1 << 4)
#define STATUS_TB            (1 << 5)
#define STATUS_SWDW          (1 << 7)

#define BUSY 0x2
#define OK 0x0
#define ERROR 0x1

#define SUBSECTOR_SIZE       (4*1024)
#define SECTOR_SIZE          (64*1024)
#define PAGE_PROGRAM_SIZE    (256)

// spi_init();
int erase_all_external_spi_flash(void)
{
  
  CS_LOW;
  spi(WRITE_ENABLE_COMMAND);  // for write anythink set this register
  CS_HIGH;
  CS_LOW;
  spi(CHIP_ERASE_COMMAND);  // for erase all chip
  CS_HIGH;
}
int check_error_or_busy(void)
{
  unsigned char status = 0;
  CS_LOW;
  spi(READ_STATUS_COMMAND);
  status = spi(DUMMY_BYTE);
  CS_HIGH;
  if((status & STATUS_BUSY) == 0)
  {
    if((status & STATUS_WEL) == 0)
    {
      CS_LOW;
      spi(WRITE_ENABLE_COMMAND);
      CS_HIGH;
      spi_check_delay();
      CS_LOW;
      spi(READ_STATUS_COMMAND);
      status = spi(DUMMY_BYTE);
      CS_HIGH;
      if((status & STATUS_WEL) != 0)
      {
        spi(WRITE_DISABLE_COMMAND);
        return OK;
      }
      else
      {
        return ERROR;
      }
    }
    else
    {
      CS_LOW;
      spi(WRITE_DISABLE_COMMAND);
      CS_HIGH;
      spi_check_delay();
      CS_LOW;
      spi(READ_STATUS_COMMAND);
      status = spi(DUMMY_BYTE);
      CS_HIGH;
      if((status & STATUS_WEL) == 0)
      {
        return OK;
      }
      else
      {
        return ERROR;
      }      
    }
  }
  else
  {
    return BUSY;
  }
}













