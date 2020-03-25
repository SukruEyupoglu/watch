
//to main file added
//#define setting_alarm_button_pressed (LPC_GPIO1->DATA & (1 << 5))
//#define setting_clk_button_pressed (LPC_GPIO1->DATA & (1 << 11))

void gpio_output_init(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		        |=	(1 << 16);
	//	ENABLE GPIO CLK
	LPC_SYSCON->SYSAHBCLKCTRL			|=	(1 << 6);
  	//  IOCON PIN FUNCTION SELECT (NO NEED DEFAULT IS GOOD)
	//  LATCH SETTING
 	//  LPC_IOCON->PIO2_10      = 0;
	//  BUZZER SETTING
  	//  LPC_IOCON->PIO2_3       = 0;
  	//  LATCH
  	LPC_GPIO2->DIR					|=	(1 << 10);
  	//  BUZZER
	LPC_GPIO2->DIR					|=	(1 << 3);
	//  BUZZER AND LATCH INACTIVE
	LPC_GPIO2->DATA					&=	~((1 << 3) | (1 << 10));	
}
