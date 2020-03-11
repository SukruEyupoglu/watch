
#include "e2prom.h"
#include "i2c.h"
#include "error.h"
#include "button.h"
#include "setting.h"

unsigned char e2prom_write(unsigned int addr,unsigned char data,unsigned int size)
{
    if(i2c(E2PROM_ADDR & 0xFE,addr,E2PROM_ADDR_SIZE,&data,size) == ERR)
    {
        return ERROR;
    }
    return OK;    
}

unsigned char e2prom_read(unsigned int addr,unsigned char * data,unsigned int size)
{
    if(i2c(E2PROM_ADDR | 0x01,addr,E2PROM_ADDR_SIZE,data,size) == ERR)
    {
      return ERROR;
    }
    return OK;
}
unsigned char set_e2prom(void)
{
  unsigned int reg_addr = 0,size = 1;
  unsigned char x,status = SKIP;
  if(e2prom_read(reg_addr,&x,size) == ERR)
  {
    return ERROR;
  }
  while(1)
  {
    set_led_write_reg(59 - reg_addr,x); // SET LED REGISTERS
    led_write(); //WRITE LEDS
    switch(check_button())
    {
      case BUTTON_UP:
        {
          if(status = SKIP)
          {
            return SET_SECOND;
          }
          x = increase_e2prom_data(x);
        }
        break;
      case BUTTON_DOWN:
        {
          if(status = SKIP)
          {
            return SET_ALR2_HOUR;
          }
          x = reduce_e2prom_data(x);
        }
        break;
      case BUTTON_CANCEL:
        {
          blink_off();
          return SET_E2PROM;
        }
        break;
      case BUTTON_OK:
        {
          status = WAIT_FOR_SETTING;
          blink_on();
        }
        break;
      case BUTTON_WRITE:
        {
          if(e2prom_write() == ERR)
          {
            return ERROR;
          }
          blink_off();
          status = SKIP;
        }
        break;
      default:
        {
          
        }
        break;
    }
  }
  return ERROR;
}




