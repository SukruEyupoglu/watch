#include "../../stm8s.h"
#include "spi/spi.h"
#include "hc595.h"

// RISING EDGE TRIGGERED
// ACTIVE HIGH FOR 74HC595 LATCH(STCP) PIN LOW-TO-HIGH FOR ENABLE
//#define LATCH PC_ODR |= (1 << 7);PC_ODR &= ~(1 << 7)

void hc595_init(void)
{
  // SPI SIMPLEX MODE , ONLY MOSI AS SPI
  SPI_CR2 |= ( (1 << SPI_CR2_BDM) | (1 << SPI_CR2_BDOE) );
  SPI_CR1 = (1 << SPI_CR1_MSTR) | (1 << SPI_CR1_SPE);
  // SPI MISO PIN FREE FOR GPIO
  PC_DDR |= (1 << 7); // SPI MISO PIN SET AS GPIO OUTPUT FOR LATCH
  PC_CR1 |= (1 << 7); // MAKE PUSH-PULL,DEFAULT MAYBE OPEN DRAIN FOR LATCH
  PC_ODR &= ~(1 << 7); // LATCH OUTPUT LOW
}
void hc595_send(unsigned char data)
{
  while ( (SPI_SR & (1 << SPI_SR_TXE) ) != (1 << SPI_SR_TXE) );
  SPI_DR = data;
  //LATCH;
  PC_ODR |= (1 << 7);
  PC_ODR &= ~(1 << 7);
}
