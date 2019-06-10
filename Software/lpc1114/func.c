void delay(volatile unsigned int bekle)
{
	while(bekle)bekle--;
}
void alert(unsigned int freq)
{
	if(alarm_gpio_output)
	{
		LPC_GPIO2->DATA &= ~(1 << 3);
	}
	else
	{
		LPC_GPIO2->DATA |= (1 << 3);
	}
	delay(freq);
}
void setting_clk_on(void)
{
	unsigned char s;
	tick_second = 50;
	while(1)
	{
	s = adc_1_time_up_down_read();
	if(s == 5)
  	{
		increase_time();
  	}
	if(s == 20)
	{
		reduce_time();
	}
	}

	
}
void setting_alarm_on(void)
{
	tick_second = 50;
	
}
void stop_alarm(void)
{
	alarm_status = 0;	
}
void sleep(void)
{
	SYSTICK_RVR = 0xF;
	restart_systick();
}
void increase_time(void)
{
	if(ds3231.hour__am_pm == 23)
	{
		ds3231.hour__am_pm = 0;
	}
	else
	{
		ds3231.hour__am_pm++;
	}
	led_write(ds3231.hour__am_pm,ds3231.minute,0);	
	
	
	if(ds3231.minute == 59)
	{
		ds3231.minute = 0;
	}
	else
	{
		ds3231.minute++;
	}
	led_write(ds3231.hour__am_pm,ds3231.minute,0);	
}



