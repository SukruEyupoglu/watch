

#include "LPC11xx.h"
#include "lpc1114_init.h"
#include "lpc1114_button.h"
#include "lpc1114_i2c.h"
#include "lpc1114_spi.h"

// SAAT DATA FROM DS3231 EVERY FUNCTION REACABLE OPTION
volatile ds_t ds3231;

// FOR LED DATA HOLDER ARRAY EVERY FUNCTION REACABLE OPTION
volatile unsigned char led[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

int main(void)
{
  init();               // lpc1114_init.h
  gpio_init();          // lpc1114_button.h
  i2c_init();           // lpc1114_i2c.h
  spi_init();           // lpc1114_spi.h
  
  
  
  while(1);
  return 0;
}




