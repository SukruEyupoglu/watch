#include "stm8s.h"

void spi_init(void);
unsigned char spi(unsigned char data);

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t data);
void i2c_write_addr(uint8_t addr);
uint8_t i2c_read();
void i2c_read_arr(uint8_t *buf, int len);

void beep_init(unsigned char beep_freq);

// active high
// #define LATCH PC_ODR |= (1 << 4);PC_ODR &= ~(1 << 4)




int main(void)
{
CLK_CKDIVR = 0; // 16mhz
BEEP_CSR = 0; // close beep look at datasheet
spi_init();






}


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

// beep frequency 500hz,1Khz,2Khz,4Khz
// 0 = 500hz , 1 = 1Khz , 2 = 2Khz , 4 = 4Khz
void beep_init(unsigned char beep_freq)
{
  BEEP_CSR = ( (1 << 5) | (32 / (2 * beep_freq) ) );
}






