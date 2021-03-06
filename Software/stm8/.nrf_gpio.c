#include "stm8s.h"
#include "nrf_gpio.h"



// RENEW CONNECTIONS FROM STM8
void nrf_gpio_init(void)
{
  //	NRF IRQ SETTINGS
	//	MAKE DIRECTION INPUT PC4,PC3
	PC_DDR &= ~( (1 << 3) | (1 << 4) ); // 3 FOR NRF1 --- 4 FOR NRF2
  
	//	NRF CE SETTINGS CHIP ENABLE ACTIVES RX - TX MODE --- ACTIVE HIGH 
	//	RX MODE CE MUST BE HIGH 
	//	TX MODE CE MUST BE A PULSE MORE THAN 10us -- 4ms DEADLINE FOR CE HIGH TIME
	//	YOU CAN USE 15us FOR COMMINICATION BEWARE FOR TX MODE DEADLINE
	/* OLD
	PA_DDR |= (1 << 3); // NRF1 CE
	PD_DDR |= (1 << 3); // NRF2 CE
	PA_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1
	PD_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2
	PA_ODR &= ~(1 << 3); // OUTPUT LOW
	PD_ODR &= ~(1 << 3); // OUTPUT LOW
  
	//	NRF CSN SETTINGS SPI CHIP SELECT ACTIVE LOW
	PA_DDR |= (1 << 2); // NRF1
	PD_DDR |= (1 << 2); // NRF2
	PA_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1
	PD_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2
	PA_ODR |= (1 << 2); // OUTPUT HIGH
	PD_ODR |= (1 << 2); // OUTPUT HIGH
	*/
	
 	//	100ms delay for nrf24l01 wakeup ---  FROM DATASHEET
	// delay(100000);
  // For double device 
	PA_DDR |= (1 << 3); // NRF1 CE
	PA_DDR |= (1 << 2); // NRF2 CE
	PA_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1 CE
	PA_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2 CE
	PA_ODR &= ~(1 << 3); // OUTPUT LOW NRF1 CE
	PA_ODR &= ~(1 << 2); // OUTPUT LOW NRF2 CE
	
	//	NRF CSN SETTINGS SPI CHIP SELECT ACTIVE LOW
	PD_DDR |= (1 << 3); // NRF1 CSN
	PD_DDR |= (1 << 2); // NRF2 CSN
	PD_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1 CSN
	PD_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2 CSN
	PD_ODR |= (1 << 3); // OUTPUT HIGH NRF1 CSN
	PD_ODR |= (1 << 2); // OUTPUT HIGH NRF2 CSN
}

void wait_irq(unsigned char which_nrf)
{
	// NRF1 IRQ PIN IS PC3 ---- READ PC3 PIN UNTIL BE LOW
	if(which_nrf == 3)
	{
		while( !(PC_IDR & (1 << 3) ) );
	}
	else
	{
		while( !(PC_IDR & (1 << 4) ) );
	}
}



