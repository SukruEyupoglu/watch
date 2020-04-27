#include "stm8s.h

void gpio_interrupt_init(void)
{
  PC_DDR &= ~(1 << 3);          // DIRECTION INPUT SETTING FOR PC3
  PC_CR1 |= (1 << 3);           // PULLUP PC3 (HARDWARE RELATED LOOK AT PCB)
  PC_CR2 |= (1 << 3);           // INTERRUPT ENABLE PC3
  
  // 0 AND 1 BITS FOR PA
  // 2 AND 3 BITS FOR PB
  // 4 AND 5 BITS FOR PC
  // OTHERS SAME ,SAME CR1, CR2 IS CONTINUATION TO CR1
  // 0,0 = FALLING EDGE AND LOW LEVEL INTERRUPT
  // 1,0 = FALLING EDGE ONLY INTERRUPT
  // 0,1 = RISING EDGE ONLY
  // 1,1 = FALLING EDGE AND RISING EDGE INTERRUPT
  EXTI_CR1 &= ~( (1 << 4) | (1 << 5) ); // FALLING EDGE AND LOW LEVEL INTERRUPT
}

void gpio_isr(void) __interrupt(EXTI2_ISR)
{
  PC_CR2 &= ~(1 << 3);           // INTERRUPT DISABLE PC3
  limit_interrupt = LIMIT_ERROR;
}

void PC3_interrupt_enable(void)
{
  PC_CR2 |= (1 << 3);           // INTERRUPT ENABLE PC3
}

void nrf_gpio_init(void)
{
  //	NRF IRQ SETTINGS
	//	MAKE DIRECTION INPUT PC4,PC3
	PC_DDR &= ~( (1 << 3) | (1 << 4) ); // 3 FOR NRF1 --- 4 FOR NRF2
  
	//	NRF CE SETTINGS CHIP ENABLE ACTIVES RX - TX MODE --- ACTIVE HIGH 
	//	RX MODE CE MUST BE HIGH 
	//	TX MODE CE MUST BE A PULSE MORE THAN 10us -- 4ms DEADLINE FOR CE HIGH TIME
	//	YOU CAN USE 15us FOR COMMINICATION BEWARE FOR TX MODE DEADLINE
	PA_DDR |= (1 << 3); // NRF1
	PD_DDR |= (1 << 3); // NRF2
	PA_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1
	PD_CR1 |= (1 << 3); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2
	PA_ODR &= ~(1 << 3); // OUTPUT LOW
	PD_ODR &= ~(1 << 3); // OUTPUT LOW
  
	//	NRF CSN SETTINGS SPI CHIP SELECT ACTIVE LOW
	PA_DDR |= (1 << 2); // NRF1
	PD_DDR |= (1 << 2); // NRF2
	PA_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF1
	PD_CR1 |= (1 << 2); // PUSH-PULL,DEFAULT OPEN DRAIN // NRF2
	PA_ODR |= (1 << 3); // OUTPUT HIGH
	PD_ODR |= (1 << 3); // OUTPUT HIGH
	
 	//	100ms delay for nrf24l01 wakeup ---  FROM DATASHEET
	// delay(100000);
  // For double device 
        
}

