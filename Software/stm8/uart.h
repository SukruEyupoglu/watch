#ifndef UART_H
#define UART_H

// #include "stdint.h"

// #define F_CPU 16000000UL
// #define BAUDRATE 115200

// 8N1,FLOW CONTROL NONE

#define UART1_CR2_RIEN 5

void uart_init(void);
void uart_send(unsigned char data);
unsigned char uart_get(void);

//void uart_isr() __interrupt(UART1_RXC_ISR);

#endif // UART_H




