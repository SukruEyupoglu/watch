
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




