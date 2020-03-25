#include "LPC11xx.h"
void uart_init(void)
{
	//	ENABLE IOCON CLK
	LPC_SYSCON->SYSAHBCLKCTRL		        |=	(1 << 16);
	//	IOCONFIG UART SETTINGS
	LPC_IOCON->PIO1_6 			        =	0x1;				//RX
	LPC_IOCON->PIO1_7 				=	0x1; 				//TX
	//	ENABLE UART CLK
	LPC_SYSCON->SYSAHBCLKCTRL 			|=	(1 << 12);
	//	UART CLK DIVIDER AND UART_CLK_ON
	LPC_SYSCON->UARTCLKDIV			        =	0x4;
	//	8 BIT AND OTHER NECESSERY SETTINGS
	LPC_UART->LCR					=	3	|	128;
	LPC_UART->DLM					=	0x0;
	LPC_UART->DLL					=	0x4;
	LPC_UART->LCR					=	0x3;
	//	MULVAL DIADDVAL
	LPC_UART->FDR					=	(8 << 4)	|	5;
	//	UART TX-RX FIFO ENABLE
	LPC_UART->FCR					=	0x1;
	// UART MODEM CONTROL DISABLE
	LPC_UART->MCR					=	0x0;
	//	UART TRANSMIT ENABLE
	LPC_UART->TER					=	(1 << 7);
	//	UART AUTOBAUD ENABLE
	//	LPC_UART->ACR				|=	0x1;
	//	UART IRQ SETTINS
	//  NVIC_EnableIRQ(UART_IRQn);
	//  LPC_UART->IER				=	0x1;
}
void uart_send(unsigned char x)
{
	LPC_UART->THR = x;
	while ( !(LPC_UART->LSR & 0x40) );
}
unsigned char uart_get(void)
{
	while(!(LPC_UART->LSR & (0x01)));
	return LPC_UART->RBR;
}
void Char_To_Bit(unsigned char bit)
{
	unsigned int turn;
	for(turn = 8;turn > 0;turn--)
	{
		if((bit & (1 << (turn - 1))) == 0)uart_send('0');
		else uart_send('1');
	}
	uart_send('\r');uart_send('\n');
}
