void spi_init(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		          |=	(1 << 16);
	//	ENABLE GPIO CLK
	LPC_SYSCON->SYSAHBCLKCTRL			        |=	(1 << 6);
  //	IOCONFIG SPI SETTINGS
	LPC_IOCON->PIO0_8					            =	0x1;                //MISO
	LPC_IOCON->PIO0_9					            =	0x1;                //MOSI
	LPC_IOCON->SWCLK_PIO0_10		        	=	0x2;                //SCK
	LPC_IOCON->PIO2_11				          	=	0x0;                //CSN
	//	ENABLE SPI CLK
	LPC_SYSCON->SYSAHBCLKCTRL 		      	|=	(1 << 11);
	//	SPI CLK DIVIDER SYSTEMCORECLK / SSP0CLKDIV = SPI CLK
	//	48000000 / 5 = 9600000 MHZ SPI CLK = 9,6MHZ
	LPC_SYSCON->SSP0CLKDIV		          	|=	0x5;
	//	CLEAR SPI0 RESET
	LPC_SYSCON->PRESETCTRL		          	|=	0x01;
	//	SET 8 BIT TRANSFER
	LPC_SSP0->CR0					                |=	0x07;
	//	ENABLE SPI
	LPC_SSP0->CR1					                |=	0x02;
}
