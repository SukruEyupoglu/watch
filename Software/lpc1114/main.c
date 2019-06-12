#include "LPC11xx.h"

#define setting_alarm_button_pressed (LPC_GPIO1->DATA & (1 << 5))
#define setting_clk_button_pressed (LPC_GPIO1->DATA & (1 << 11))
#define stop_alarm_button_pressed (LPC_GPIO2->DATA & (1 << 4))
#define sleep_button_pressed (LPC_GPIO2->DATA & (1 << 5))
#define alarm_gpio_output (LPC_GPIO2->DATA & (1 << 3))
// FOR SYSTICK TIMER SETTING
volatile unsigned char tick_interrupt_count = 0;
volatile unsigned char tick_second = 10;
// FOR PWM LIGHT SETTING lowtime + hightime == MUST BE SHORT
volatile unsigned short lowtime = 0xFF , hightime = 0xFF;
// FOR ALARM STATUS
volatile unsigned char alarm_status = 0;

int main(void)
{
  unsigned char l;
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
  if(setting_clk_button_pressed == 0)
  {
  stop_alarm();
  setting_clk_on();
  }
  if(setting_alarm_button_pressed == 0)
  {
  stop_alarm();
  setting_alarm_on();
  }
  if(stop_alarm_button_pressed == 0)
  {
  stop_alarm();
  }
  if(sleep_button_pressed == 0)
  {
  sleep();
  }
  l = adc_2_light_up_down_read();
  if(l == 20)
  {
    brightness_up();
  }
  if(l == 5)
  {
    brightness_down();
  }
  if(alarm_status)
  {
  alert(100);
  }
}
return 0;
}
