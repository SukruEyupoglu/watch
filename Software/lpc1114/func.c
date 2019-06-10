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
	tick_second = 50;
	  if(light_up_down_button_pressed == 0)
  {
  
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


