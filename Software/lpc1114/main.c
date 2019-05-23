volatile unsigned char tick_interrupt_count = 0;
volatile unsigned char tick_second = 10;


int main(void)
{
// DS3231 HAS 19 REGISTER ADDRESS
unsigned char saat[19];

ds_t ds3231;

main_init();
i2c_init();
spi_init();
systick_init();
  
//READ ALL REGISTER AND SAVE TO ARRAY  
i2c_read_multi_char(0xD0,0xD1,0x00,saat[19]);

ds3231.minute = reg2time(saat[1]);
ds3231.hour__am_pm = reg2time(saat[2]);
  
//WRITE MINUTE AND HOUR
led_write(ds3231.hour__am_pm,ds3231.minute,0);
  
//START SYSTICK AND 10 SECOND DEADLINE FOR POWERDOWN MODE
systick_second_sleep(10);

while(1){
  
//WAIT FOR SETTING BUTTON PRESSED
//EACH BUTTON PRESSED RESTART SYSTICK
  if(setting_clk_button_pressed == 0)
  {
    setting_clk_on();
  }
  if(setting_alarm_button_pressed == 0)
  {
  setting_alarm_on();
  }
}
return 0;
}
