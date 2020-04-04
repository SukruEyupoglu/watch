#include "LPC11xx.h"
#include "init.h"
#include "button.h"
#include "i2c.h"
#include "spi.h"
#include "led.h"
#include "ds3231.h"
#include "error.h"
#include "setting.h"
#include "systick.h"
//#include "alarm.h"

void show_watch(void);
void stop_alarm(void);
void check_alarm(void);
void alert(void);

void stop_alarm(void)
{
  
}

void check_alarm(void)
{
  
}

void alert(void)
{
  
}

void show_watch(void)
{
  unsigned char minute,hour;
  if(read_ds3231_minute(&minute) == ERR)
  {
    error();
  }
  if(read_ds3231_hour(&hour) == ERR)
  {
    error();
  }
  set_led_write_reg(minute,hour); // SET LED REGISTERS
  led_write(); //WRITE LEDS  
}

int main(void)
{
  init(MHZ_12);         // init.h     --> only set 12MHZ frequency
  button_init();        // button.h   --> button settings
  i2c_init();           // i2c.h      --> i2c settings
  spi_init();           // spi.h      --> spi settings
  led_init();           // led.h      --> latch and output enable settings
//  led_power_init();     // alarm.h    --> look at e2prom and set pwm output for leds
  
  if(ds3231_every_minute_alarm_init() == ERR)
  {
    error();
  }
  
  deadline_systick_sec(SEC_10);
  
  while(1)
  {
    switch(check_button()) //there is a delay in check button
    {
      case STP_LRM:
        {
          stop_alarm();
        }
        break;
      case SLP:
        {
          sleep_or_powerdown(POWER_DOWN);
        }
        break;        
      case SETTING_LRM:
        {/*
          relax_systick_sec();
          if(setting_e2prom() == ERR)
          {
            error();
          }
          deadline_systick_sec(SEC_10);*/
        }
        break;
      case SETTING_CLK:
        {
          relax_systick_sec();
          if(setting_ds3231() == ERR)
          {
            error();
          }
          deadline_systick_sec(SEC_10);
        }
        break;
      default:
        {
          show_watch();         // show hour and minute from ds3231
          check_alarm();
        }
        break;
    }
  }
  
  return 0;
}

