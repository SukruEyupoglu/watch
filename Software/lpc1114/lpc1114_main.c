

#include "LPC11xx.h"
#include "lpc1114_init.h"
#include "lpc1114_button.h"
#include "lpc1114_i2c.h"
#include "lpc1114_spi.h"
#include "lpc1114_led.h"


// SAAT DATA FROM DS3231 EVERY FUNCTION REACABLE OPTION
// volatile ds_t ds3231;

// FOR LED DATA HOLDER ARRAY EVERY FUNCTION REACABLE OPTION
volatile unsigned char led[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

int main(void)
{
  init();               // lpc1114_init.h     --> only set 12MHZ frequency
  gpio_init();          // lpc1114_button.h   --> button settings and latch settings
  i2c_init();           // lpc1114_i2c.h      --> i2c settings
  spi_init();           // lpc1114_spi.h      --> spi settings
  
  show_watch();         // show hour and minute from ds3231
  
  while(1)
  {
    switch(check_button())
    {
      case SLP:
        {
          
        }
        break;
      case SETTING_LRM:
        {
          
        }
        break;
      case SETTING_CLK:
        {
          
        }
        break;
      default:
        {
          show_watch();         // show hour and minute from ds3231          
        }
        break;
    }
  }
  
  return 0;
}




