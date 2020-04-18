#include "LPC11xx.h"
#include "adc.h"

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
	return adc_read(ADC0);
}
unsigned char adc_1_time_up_down_read(void)
{
	unsigned char x
	x = adc_read(ADC1);
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
	return 0;
}
unsigned char adc_2_light_up_down_read(void)
{
	unsigned char x
	x = adc_read(ADC2);
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
	return 0;
}
unsigned char adc_4_pir_read(void)
{
	return adc_read(ADC4);
}
