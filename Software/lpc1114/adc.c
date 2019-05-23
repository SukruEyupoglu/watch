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
	LPC_IOCON->R_PIO1_3 		            	=	0x2;
	// ADC CONTROL REGISTER
	// ACTIVATE AD0,AD1,AD2,AD4
	LPC_ADC->CR					|=	(1 << 0) | (1 << 1) | (1 << 2) | (1 << 4);
	// SET ADC CLK DIVIDER TO (PCLK / (CLKDIV +1)) 100KHZ --> 12000000/120=100000 --> CLKDIV = (120 - 1) = 0x77
	LPC_ADC->CR					|=	(0x77 << 8);
	// START CONVERSION
	//LPC_ADC->CR					|=	(1 << 24);
	
}



