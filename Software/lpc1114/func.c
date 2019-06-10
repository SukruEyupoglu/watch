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
	unsigned char s,t = 0;
	tick_second = 100;
	delay(blink_time);
	while(1)
	{
	if(t == 0)
	{
	led_write(ds3231.hour__am_pm,ds3231.minute,0);
	delay(blink_time);
	led_write(ds3231.hour__am_pm,0,0);
	delay(blink_time);
	}
	else
	{
	led_write(ds3231.hour__am_pm,ds3231.minute,0);
	delay(blink_time);
	led_write(100,ds3231.minute,0);
	delay(blink_time);		
	}
	if(setting_clk_button_pressed == 0)
	{
		if(t == 0)
		{
			led_write(ds3231.hour__am_pm,ds3231.minute,0);
			t = 1;
		}
		else
		{
			led_write(ds3231.hour__am_pm,ds3231.minute,0);
			t = 0;
		}
	}
	s = adc_1_time_up_down_read();
	if(s == 5)
  	{
		if(t == 0)
		{
		increase_minute();
		}
		else
		{
		increase_hour();
		}
  	}
	if(s == 20)
	{
		if(t == 0)
		{
		reduce_minute();
		}
		else
		{
		reduce_hour();
		}
	}
	}

	
}
void setting_alarm_on(void)
{
	tick_second = 100;
	
}
void stop_alarm(void)
{
	LPC_GPIO2->DATA &= ~(1 << 3);
	alarm_status = 0;	
}
void sleep(void)
{
	SYSTICK_RVR = 0xF;
	restart_systick();
}
void increase_hour(void)
{
	if(ds3231.hour__am_pm == 23)
	{
		ds3231.hour__am_pm = 0;
	}
	else
	{
		ds3231.hour__am_pm++;
	}
}
void increase_minute(void)
{	
	if(ds3231.minute == 59)
	{
		ds3231.minute = 0;
	}
	else
	{
		ds3231.minute++;
	}	
}
void reduce_hour(void)
{
	if(ds3231.hour__am_pm == 0)
	{
		ds3231.hour__am_pm = 23;
	}
	else
	{
		ds3231.hour__am_pm--;
	}
}
void reduce_minute(void)
{	
	if(ds3231.minute == 00)
	{
		ds3231.minute = 59;
	}
	else
	{
		ds3231.minute--;
	}	
}

