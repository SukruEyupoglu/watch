#include "stm8s.h"
#include "spi.h"

void spi_init(void)
{
  // 500KHZ spi clk
  // SPI_CR1_MSTR  = spi master bit
  // SPI_CR1_SPE = spi enable bit
  // SPI_CR1_BR = baud rate bits[3,4,5] divider 
  // SPI_CR1_BR = 000; --> FMASTER / 2 --> 16 / 2 = 8 mhz
  // SPI_CR1_BR = 100; --> FMASTER / 32 --> 16 / 32 = 500 khz
  // SPI_CR1 = (1 << SPI_CR1_MSTR) | (1 << SPI_CR1_SPE) | (1 << SPI_CR1_BR1);
  
  // 8MHZ spi clk
  SPI_CR1 = (1 << SPI_CR1_MSTR) | (1 << SPI_CR1_SPE);
  // NOT CHANGE THIS READ DATASHEET
  //SPI_CR2 = (1 << SPI_CR2_SSM) | (1 << SPI_CR2_SSI) | (1 << SPI_CR2_BDM) | (1 << SPI_CR2_BDOE);
}

unsigned char spi(unsigned char data)
{
  while ( (SPI_SR & (1 << SPI_SR_TXE) ) != (1 << SPI_SR_TXE) );
  SPI_DR = data;
  while ( (SPI_SR & (1 << SPI_SR_RXNE) ) != (1 << SPI_SR_RXNE) );
  return SPI_DR;
}
void hc595_init(void)
{
  spi_init();
  PC_DDR |= (1 << 7); // SPI MISO PIN SET AS GPIO OUTPUT FOR LATCH
  PC_CR1 |= (1 << 7); // MAKE PUSH-PULL,DEFAULT MAYBE OPEN DRAIN FOR LATCH
  PC_ODR &= ~(1 << 7); // LATCH OUTPUT LOW
}
void hc595_latch(void)
{
  // ACTIVE HIGH FOR 74HC595 LATCH(STCP) PIN LOW-TO-HIGH FOR ENABLE
  PC_ODR |= (1 << 7);
  PC_ODR &= ~(1 << 7);
}



