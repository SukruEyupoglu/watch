
//to main file added
//#define setting_alarm_button_pressed (LPC_GPIO1->DATA & (1 << 5))
//#define setting_clk_button_pressed (LPC_GPIO1->DATA & (1 << 11))

void gpio_init(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		        |=	(1 << 16);
	//	ENABLE GPIO CLK
	LPC_SYSCON->SYSAHBCLKCTRL			|=	(1 << 6);
  //  IOCON PIN FUNCTION SELECT (NO NEED DEFAULT IS GOOD)
  //LPC_IOCON->PIO1_11      = 0;
  //LPC_IOCON->PIO1_5       = 0;
  //  DIRECTION INPUT FOR SET ALARM BUTTON
  LPC_GPIO1->DIR					&=	~(1 << 5);
  //  DIRECTION INPUT FOR SET CLK BUTTON
	LPC_GPIO1->DIR					&=	~(1 << 11);
}
