#ifndef UART_H
#define UART_H

// #include "stdint.h"

// #define F_CPU 16000000UL
// #define BAUDRATE 115200

// 8N1,FLOW CONTROL NONE

void uart_init(void);
void uart_send(unsigned char data);
unsigned char uart_get(void);

#endif // UART_H




