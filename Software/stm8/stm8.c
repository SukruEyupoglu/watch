#include "stm8s.h"
#include "nrf.h"
#include "uart.h"
#include "delay.h"
#include "spi.h"
#include "led.h"


int main(void)
{
	unsigned char x1 = 0,x2 = 2,y1 = 3,y2 = 4;
	// SET CLK TO FULL SPEED (16MHZ)
	CLK_CKDIVR = 0;
	
	spi_init();
	uart_init();
	led_init();
	
	// SET GPIOs FOR NRF
	nrf_gpio_init();
	
	nrf24l01_init(NRF1);
	nrf24l01_init(NRF2);
	
	led_open();
	
	x1 = uart_get();
	uart_send(x1);
	x2 = uart_get();
	uart_send(x2);
	
	led_close();
	
	// SENDER SIDE
	while(1)
	{
		make_tx(NRF1);
		make_rx(NRF2);
		if(UART1_SR & (1 << UART1_SR_RXNE) )
		{
			x1 = UART1_DR;
		}
		else
		{
			x1 = 0;
		}
		UART1_DR = y1;
		nrf_write_buf(&x1,1,NRF1);
		nrf_send(NRF1);
		wait_irq(NRF1);
		clear_irq(NRF1);
		
		make_rx(NRF1);
		
		wait_irq(NRF2);
		nrf_read_buf(&y2,1,NRF2);
		clear_irq(NRF2);
		
		if(y2 == x1)
		{
			led_open();
		}
		make_tx(NRF2);
		nrf_write_buf(&x2,1,NRF2);
		nrf_send(NRF2);
		wait_irq(NRF2);
		clear_irq(NRF2);
		
		wait_irq(NRF1);
		nrf_read_buf(&y1,1,NRF1);
		clear_irq(NRF1);
	}
}










