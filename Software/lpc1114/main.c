#include "LPC11xx.h"
#include "init.h"
#include "button.h"
#include "i2c.h"
#include "spi.h"
#include "led.h"
#include "ds3231.h"
// #include "lpc1114_error.h"
#include "setting.h"

void show_watch(void);

void show_watch(void)
{
  unsigned char minute,hour;
  if(read_ds3231_minute(&minute) == ERR)
  {
    //error();
  }
  if(read_ds3231_hour(&hour) == ERR)
  {
    //error();
  }
  set_led_write_reg(minute,hour); // SET LED REGISTERS
  led_write(); //WRITE LEDS  
}

int main(void)
{
  init();               // lpc1114_init.h     --> only set 12MHZ frequency
  gpio_init();          // lpc1114_button.h   --> button settings
  i2c_init();           // lpc1114_i2c.h      --> i2c settings
  spi_init();           // lpc1114_spi.h      --> spi settings
  led_init();           // latch and output enable settings
  
  
  
  while(1)
  {
    switch(check_button())
    {
      case STP_LRM:
        {
          //stop_alarm();
        }
        break;
      case SLP:
        {
          //sleep();
        }
        break;        
      case SETTING_LRM:
        {
          if(ds3231_clock_setting(AL1) == ERR)
          {
            //error();
          }
        }
        break;
      case SETTING_CLK:
        {
          if(ds3231_clock_setting(CLOCK) == ERR)
          {
            //error();
          }          
        }
        break;
      default:
        {
          show_watch();         // show hour and minute from ds3231
          // check_alarm();
        }
        break;
    }
  }
  
  return 0;
}

