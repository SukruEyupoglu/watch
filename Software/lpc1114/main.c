#include "LPC11xx.h"

#define alarm_gpio_output (LPC_GPIO2->DATA & (1 << 3))
// FOR LED DATA HOLDER ARRAY EVERY FUNCTION REACABLE OPTION
volatile unsigned char led[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
// FOR SYSTICK TIMER SETTING
volatile unsigned char tick_interrupt_count = 0;
volatile unsigned char tick_second = 10;
// FOR PWM LIGHT SETTING lowtime + hightime == MUST BE SHORT
volatile unsigned short lowtime = 0xFF , hightime = 0xFF;
// FOR ALARM STATUS
volatile unsigned char alarm_status = 0;

int main(void)
{
  // DS3231 HAS 19 REGISTER ADDRESS
  unsigned char saat[19];
  // FOR CONVERTING DS REGISTERS TO REASONABLE DATA
  ds_t ds3231;
  //  INIT ALL NECESSARY FUNCTIONS
  main_init();
  i2c_init();
  spi_init();
  systick_init();
  
  //READ ALL REGISTER AND SAVE TO RAW ARRAY  
  i2c_read_multi_char(0xD0,0xD1,0x00,saat);
  // CONVERT RAW REGISTER DATA TO REASONABLE DATA
  raw_to_ds_t(&ds3231,saat);
  //  CHECK ALL ALARMS
  check_alarm(&ds3231);  
  
//WRITE MINUTE AND HOUR
led_write(ds3231.hour__am_pm,ds3231.minute,0);
  
//START SYSTICK AND 10 SECOND DEADLINE FOR POWERDOWN MODE
systick_second_sleep(10);

while(1){
  //WAIT FOR SETTING BUTTON PRESSED
  //EACH BUTTON PRESSED RESTART SYSTICK
  switch(check_button())
  {
    case 201 :
      {
          stop_alarm();
          setting_alarm_on();
      }
    break;
    case 202 :
      {
          stop_alarm();
          setting_clk_on();
      }
    break;
    case 203 :
      {
          stop_alarm();
      }
    break;
    case 204 :
      {
          stop_alarm();
          sleep();
      }
    break;
    case 205 :
      {
          stop_alarm();
      }
    break;
    case 206 :
      {
          stop_alarm();
      }
    break;
    case 207 :
      {
          stop_alarm();
          brightness_down();
      }
    break;
    case 208 :
      {
          stop_alarm();
          brightness_up();
      }
    break;
    case 209 :
      {
          stop_alarm();
      }
    break;
    case 210 :
      {
          stop_alarm();
      }
    break;
    default :
    {
    }
    break;
  }
}
return 0;
}
