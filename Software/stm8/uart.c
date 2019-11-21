#include "stm8s.h"
#include "uart.h"

void uart_init(void)
{
  // ROUND TO NEAREST INTEGER
  uint16_t div = (F_CPU + (BAUDRATE / 2 ) ) / BAUDRATE;
  
  UART1_BRR2 = ( (div >> 8) & 0xF0) + (div & 0x0F);
  UART1_BRR1 = (div >> 4);
  
  // ENABLE TRANSMITTER AND RECEIVER
  UART1_CR2 = ( (1 << UART1_CR2_TEN) | (1 << UART1_CR2_REN) );
}




