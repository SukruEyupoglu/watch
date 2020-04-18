#include "LPC11xx.h"

unsigned char adc_read(unsigned char adcx)
{
	LPC_ADC->CR	|=	(1 << adcx);
	LPC_ADC->CR	|=	AD0CR_START_CONVERSION_BIT;
	while((LPC_ADC->DR[adcx] < AD0DR_DONE));
	return ((LPC_ADC->DR[adcx] & AD0DR_V_VREF) >> 8);
}


void adc_init(void)
{
  	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		        |=	(1 << 16);
	//	ENABLE ADC CLK
	LPC_SYSCON->SYSAHBCLKCTRL			|=	(1 << 13);
	//	POWER UP ADC
	LPC_SYSCON->PDRUNCFG				&=	~(1 << 4);
	//	IOCONFIG ADC SETTINGS
    //  MIC ADC SETTING
	LPC_IOCON->R_PIO0_11		            	=	0x2;
    //  TIME UP DOWN ADC SETTING
	LPC_IOCON->R_PIO1_0		            	=	0x2;
    //  LIGHT UP DOWN ADC SETTING
	LPC_IOCON->R_PIO1_1 		            	=	0x2;
    //  PIR ADC SETTING
	LPC_IOCON->SWDIO_PIO1_3 		        =	0x2;
	// ADC CONTROL REGISTER
	// ACTIVATE AD0,AD1,AD2,AD4
	// LPC_ADC->CR					|=	(1 << 0) | (1 << 1) | (1 << 2) | (1 << 4);
	// SET ADC CLK DIVIDER TO (PCLK / (CLKDIV +1)) 100KHZ --> 12000000/120=100000 --> CLKDIV = (120 - 1) = 0x77
	LPC_ADC->CR					|=	(0x77 << 8);
	// START CONVERSION
	//LPC_ADC->CR					|=	(1 << 24);
}
unsigned char adc_0_mic_read(void)
{
		return 0;
}
unsigned char adc_1_time_up_down_read(void)
{
	unsigned int x;
	// START CONVERSION
	LPC_ADC->CR					|=	(1 << 24);
	while((LPC_ADC->DR[0] < 0x7FFFFFFF));
	{
		x = LPC_ADC->DR[1];
		if(x & (1 << 31))
		   {
			   // STOP CONVERSION
			   LPC_ADC->CR	&=	~(1 << 24);
			   x >>= 6;
			   x  &= 0x3FF;
			   // 0x3FF = 1023 and %60 is up %30 is down
			   // between %70 and %50 is up
			   // between %40 and %20 is down
			   // %70 = 716 --> %50 = 512 --> %40 = 409 --> %20 = 204
			   if((x < 716) & (x > 512))
			   {
				   return 20;
			   }
			   if((x < 409) & (x > 204))
			   {
				   return 5;
			   }
			break;
		   }
	}
	return 0;
}
unsigned char adc_2_light_up_down_read(void)
{
	unsigned int x;
	// START CONVERSION
	LPC_ADC->CR					|=	(1 << 24);
	while(1)
	{
		x = LPC_ADC->DR[2];
		if(x & (1 << 31))
		   {
			   // STOP CONVERSION
			   LPC_ADC->CR	&=	~(1 << 24);
			   x >>= 6;
			   x  &= 0x3FF;
			   // 0x3FF = 1023 and %60 is up %30 is down
			   // between %70 and %50 is up
			   // between %40 and %20 is down
			   // %70 = 716 --> %50 = 512 --> %40 = 409 --> %20 = 204
			   if((x < 716) & (x > 512))
			   {
				   return 20;
			   }
			   if((x < 409) & (x > 204))
			   {
				   return 5;
			   }
			break;
		   }
	}
	return 0;		
}
unsigned char adc_4_pir_read(void)
{
		return 0;
}
