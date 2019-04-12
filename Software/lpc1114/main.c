int main(void)
{
unsigned char saat[19];
unsigned char watch_reg;
unsigned char minute_reg;
main_init();
i2c_init();
spi_init();
while(1){
i2c_read_multi_char(0xD0,0xD1,0x00,saat[19]);
watch_reg   = reg2time(saat[2]);
minute_reg  = reg2time(saat[1]);
led_write(watch_reg,minute_reg,0);
}
return 0;
}
