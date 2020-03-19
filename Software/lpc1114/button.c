
#include "LPC11xx.h"
#include "button.h"
#include "delay.h"

#define setting_alarm_button_pressed (LPC_GPIO1->DATA & (1 << 5))
#define setting_clk_button_pressed (LPC_GPIO1->DATA & (1 << 11))
#define stop_alarm_button_pressed (LPC_GPIO2->DATA & (1 << 4))
#define sleep_button_pressed (LPC_GPIO2->DATA & (1 << 5))
#define boot_button_pressed (LPC_GPIO0->DATA & (1 << 1))
#define write_setting_button_pressed (LPC_GPIO3->DATA & (1 << 4))

#define DELAY_FOR_BUTTON 0x0FFFFFFF
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
	LPC_IOCON->PIO1_11	            		=	0x0; //setting clk
	LPC_IOCON->PIO2_4       	        	=	0x0; //stop alarm
	LPC_IOCON->PIO2_5 		          	=	0x0; //sleep
	LPC_IOCON->PIO0_1       	       		=	0x0; //boot
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
  delay(DELAY_FOR_BUTTON);
  if(setting_alarm_button_pressed != 0)
  {
    return SET_LRM;
  }
  if(setting_clk_button_pressed != 0)
  {
    return SET_CLK;
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
return 0;
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
  
return 0;
}

*/




