volatile unsigned char tick_interrupt_count = 0;
volatile unsigned char tick_second = 0;


int main(void)
{
unsigned char saat[19];
ds_t ds3231;
main_init();
i2c_init();
spi_init();
i2c_read_multi_char(0xD0,0xD1,0x00,saat[19]);
ds3231.minute = reg2time(saat[1]);
ds3231.hour__am_pm = reg2time(saat[2]);
led_write(ds3231.hour__am_pm,ds3231.minute,0);
systick_second_sleep(10);
while(1){

}
return 0;
}
