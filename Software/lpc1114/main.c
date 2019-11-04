#include "LPC11xx.h"
#define ERR 1
#define ds3231_addr 0xD0
#define eeprom_addr 0xA2
#define alarm_gpio_output (LPC_GPIO2->DATA & (1 << 3))

// FOR SYSTICK TIMER SETTING
volatile unsigned char tick_interrupt_count = 0;
volatile unsigned char tick_second = 10;
// FOR PWM LIGHT SETTING
volatile unsigned short percent = 50 , duty = 0xFFFF;
// FOR ALARM STATUS
volatile unsigned char alarm_status = 0;

// SAAT DATA FROM DS3231 EVERY FUNCTION REACABLE OPTION
volatile ds_t ds3231;

// FOR LED DATA HOLDER ARRAY EVERY FUNCTION REACABLE OPTION
volatile unsigned char led[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

int main(void)
{
  // DS3231 HAS 19 REGISTER ADDRESS
  unsigned char saat[19];
  // EEPROM ALERT SETTING REGISTERS
  unsigned char alrm[60];
  // FOR CONVERTING DS REGISTERS TO REASONABLE DATA
  // ds_t ds3231;
  //  INIT ALL NECESSARY FUNCTIONS
  main_init();
  gpio_init();
  i2c_init();
  spi_init();
  tmr16b1_pwm_init();
  gpio_output_init();
  systick_init();
  
  read_eeprom_data();
  
  //READ ALL REGISTER AND SAVE TO RAW ARRAY  
  if(i2c(ds3231_addr,0,1,1,saat,19) == ERR)
  {
    error();
  }
    //READ ALL REGISTER AND SAVE TO RAW ARRAY  
  if(i2c(eeprom_addr,1,2,1,alrm,60) == ERR)
  {
    error();
  }
  // CONVERT RAW REGISTER DATA TO REASONABLE DATA
  raw_to_ds_t(&ds3231,saat);
  //  CHECK ALL ALARMS
  check_alarm(&ds3231,alrm);  
  
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
