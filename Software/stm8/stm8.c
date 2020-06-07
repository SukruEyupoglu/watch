#include "stm8s.h"
#include "nrf.h"
#include "uart.h"
#include "nrf_gpio_init.h"
#include "delay.h"
#include "spi.h"

int main(void)
{
	unsigned char x,y;
	// SET CLK TO FULL SPEED (16MHZ)
	CLK_CKDIVR = 0;
	
	spi_init();
	uart_init();
	
	// SET GPIOs FOR NRF
	nrf_gpio_init();
	
	nrf24l01_init(NRF1);
	nrf24l01_init(NRF2);
	
	// SENDER SIDE
	while(1)
	{
		make_tx(NRF1);
		if(UART1_SR & (1 << UART1_SR_RXNE) )
		{
			x = UART1_DR;
		}
		else
		{
			x = 0;
		}
		UART1_DR = y;
		nrf_write_buf(&x,1);
		nrf_send();
		wait_irq();
		make_rx();
		wait_irq();
		nrf_read_buf(&y,1);
	}
	
	// RECEIVER SIDE
	/*
	while(1)
	{
		make_rx();
		wait_irq();
		nrf_read_buf(&y,1);
		make_tx();
		if(UART1_SR & (1 << UART1_SR_RXNE) )
		{
			x = UART1_DR;
		}
		else
		{
			x = 0;
		}
		UART1_DR = y;
		nrf_write_buf(&x,1);
		nrf_send();
		wait_irq();
	}
	*/




}
