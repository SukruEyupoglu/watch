#include "LPC11xx.h"
void spi_init(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		        |=	(1 << 16);
	//	ENABLE GPIO CLK
	LPC_SYSCON->SYSAHBCLKCTRL			|=	(1 << 6);
	//	IOCONFIG SPI SETTINGS
	LPC_IOCON->PIO0_8		            	=	0x1;                //MISO
	LPC_IOCON->PIO0_9		            	=	0x1;                //MOSI
	LPC_IOCON->SWCLK_PIO0_10	        	=	0x2;                //SCK
	LPC_IOCON->PIO2_11		          	=	0x0;                //CSN
	//	ENABLE SPI CLK
	LPC_SYSCON->SYSAHBCLKCTRL 		      	|=	(1 << 11);
	//	SPI CLK DIVIDER SYSTEMCORECLK / SSP0CLKDIV = SPI CLK
	//	48000000 / 5 = 9600000 MHZ SPI CLK = 9,6MHZ
	LPC_SYSCON->SSP0CLKDIV		          	|=	0x5;
	//	CLEAR SPI0 RESET
	LPC_SYSCON->PRESETCTRL		          	|=	0x01;
	//	SET 8 BIT TRANSFER
	LPC_SSP0->CR0			                |=	0x07;
	//	ENABLE SPI
	LPC_SSP0->CR1			                |=	0x02;
  
  // LATCH SETTINGS FOR SHIFT REGISTERS
  LPC_IOCON->PIO2_10      = 0;
  LPC_GPIO2->DIR					|=	(1 << 10);
  // THERE IS A TRANSISTOR AT LINE ACTIVE LOW BUT BECAUSE TRANSISTOR ACTIVE HIGH
  // LOW IS INACTIVE (ACTIVE HIGH) SET LOW NOW
  LPC_GPIO2->DATA					&=	~(1 << 10);
}
unsigned char spi(unsigned char TX_Data)
{
	while ((LPC_SSP0->SR & (SSPSR_TNF | SSPSR_BSY)) != SSPSR_TNF);
	LPC_SSP0->DR = TX_Data;
	while ((LPC_SSP0->SR & (SSPSR_BSY | SSPSR_RNE)) != SSPSR_RNE);
	return LPC_SSP0->DR;
}




