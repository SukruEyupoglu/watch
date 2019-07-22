#define setting_alarm_button_pressed (LPC_GPIO1->DATA & (1 << 5))
#define setting_clk_button_pressed (LPC_GPIO1->DATA & (1 << 11))
#define stop_alarm_button_pressed (LPC_GPIO2->DATA & (1 << 4))
#define sleep_button_pressed (LPC_GPIO2->DATA & (1 << 5))
#define boot_button_pressed (LPC_GPIO0->DATA & (1 << 1))
#define write_setting_button_pressed (LPC_GPIO3->DATA & (1 << 4))

#define SET_LRM 201
#define SET_CLK 202
#define STP_LRM 203
#define SLP 204
#define BOO 205
#define WRT_SET 206
#define LIG_DWN 207
#define LIG_UP 208
#define TM_DWN 209
#define TM_UP 210

void gpio_init(void)
{
  	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		        |=	(1 << 16);
	//	ENABLE GPIO CLK
	LPC_SYSCON->SYSAHBCLKCTRL			|=	(1 << 6);
	//	IOCONFIG SPI SETTINGS
	LPC_IOCON->PIO1_5		            	=	0x0; //setting alarm
	LPC_IOCON->PIO1_11	            	=	0x0; //setting clk
	LPC_IOCON->PIO2_4       	        =	0x0; //stop alarm
	LPC_IOCON->PIO2_5 		          	=	0x0; //sleep
	LPC_IOCON->PIO0_1       	        =	0x0; //boot
	LPC_IOCON->PIO3_4 		          	=	0x0; //write setting
    LPC_GPIO1->DIR					&=	~(1 << 5);
    LPC_GPIO1->DIR					&=	~(1 << 11);
    LPC_GPIO2->DIR					&=	~(1 << 4);
    LPC_GPIO2->DIR					&=	~(1 << 5);
    LPC_GPIO0->DIR					&=	~(1 << 1);
    LPC_GPIO3->DIR					&=	~(1 << 4);
}

unsigned char check_button(void)
{
  if(setting_alarm_button_pressed != 0)
  {
    return 201;
  }
  if(setting_clk_button_pressed != 0)
  {
    return 202;
  }
  if(stop_alarm_button_pressed != 0)
  {
    return 203;
  }
  if(sleep_button_pressed != 0)
  {
    return 204;
  }
  if(boot_button_pressed != 0)
  {
    return 205;
  }
  if(write_setting_button_pressed != 0)
  {
    return 206;
  }
  switch (adc_2_light_up_down_read())
  {
    case 5:
    {
      return 207;
    }
    case 20:
    {
      return 208;
    }
  }
  switch (adc_1_time_up_down_read())
  {
    case 5:
    {
      return 209;
    }
    case 20:
    {
      return 210;
    }
  }
return 0;
}
