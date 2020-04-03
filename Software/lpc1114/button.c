
#include "LPC11xx.h"
#include "button.h"



void button_delay(volatile unsigned int wait)
{
	while(wait)wait--;
}

void button_init(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		|=	(1 << 16);
	//	ENABLE GPIO CLK
	LPC_SYSCON->SYSAHBCLKCTRL		|=	(1 << 6);
	//	IOCONFIG gpio SETTINGS
	LPC_IOCON->PIO1_5		        =	0x0; //setting alarm
	LPC_IOCON->PIO1_11	            	=	0x0; //setting clk
	LPC_IOCON->PIO2_4       	        =	0x0; //stop alarm
	LPC_IOCON->PIO2_5 		        =	0x0; //sleep
	LPC_IOCON->PIO0_1       	       	=	0x0; //boot
	LPC_IOCON->PIO3_4 		        =	0x0; //write setting
  // make direction input button pins
  LPC_GPIO1->DIR				&=	~(1 << 5);
  LPC_GPIO1->DIR				&=	~(1 << 11);
  LPC_GPIO2->DIR				&=	~(1 << 4);
  LPC_GPIO2->DIR				&=	~(1 << 5);
  LPC_GPIO0->DIR				&=	~(1 << 1);
  LPC_GPIO3->DIR				&=	~(1 << 4);
}

unsigned char check_button(void)
{
  button_delay( (ONE_SECOND / 4) );	// ONE_SECOND = Systemcoreclock = 12 000 000
  if(setting_alarm_button_pressed != 0)
  {
	if(boot_button_pressed != 0)
  	{
    		return SETTING_LRM;
  	}
	else
	{
		return SET_LRM;
	}
  }
  if(setting_clk_button_pressed != 0)
  {
	if(boot_button_pressed != 0)
  	{
    		return SETTING_CLK;
  	}
	else
	{
    		return SET_CLK;
	}
  }
  if(stop_alarm_button_pressed != 0)
  {
    return STP_LRM;
  }
  if(sleep_button_pressed != 0)
  {
    return SLP;
  }
  if(boot_button_pressed != 0)
  {
    return BOO;
  }
  if(write_setting_button_pressed != 0)
  {
    return WRT_SET;
  }
/*
  switch (adc_2_light_up_down_read())
  {
    case 5:
    {
      return LIG_DWN;
    }
    case 20:
    {
      return LIG_UP;
    }
  }
  switch (adc_1_time_up_down_read())
  {
    case 5:
    {
      return TM_DWN;
    }
    case 20:
    {
      return TM_UP;
    }
  }
  */
return 0;
}
