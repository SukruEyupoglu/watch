#include "stm8s.h"
#include "uart.h"

void uart_init(void)
{
  // ROUND TO NEAREST INTEGER
  // uint16_t div = (F_CPU + (BAUDRATE / 2 ) ) / BAUDRATE;
  // UART1_BRR2 = ( (div >> 8) & 0xF0) + (div & 0x0F);
  // UART1_BRR1 = (div >> 4);
  
  // no need calculating look at user manual for other bauds
  UART_DIV    = 0x008B // F_MASTER = 16MHZ
  UART1_BRR1  = 0x08;
  UART1_BRR2  = 0x0B;
  // ENABLE TRANSMITTER AND RECEIVER
  UART1_CR2 = ( (1 << UART1_CR2_TEN) | (1 << UART1_CR2_REN) );
}

void uart_send(unsigned char data)
{
  UART1_DR = data;
  while( ! (UART1_SR & (1 << UART1_SR_TC) ) );
}

unsigned char uart_get(void)
{
  while( ! (UART1_SR & (1 << UART1_SR_RXNE) ) );
  return UART1_DR;
}
