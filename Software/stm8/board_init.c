#include "stm8s.h"
#include "board_init.h"


void board_init(void)
{
	// SET CLK TO FULL SPEED (16MHZ)
	CLK_CKDIVR = 0;

	// 74hc4051 output select pin direction
	// PA1,PA2,PA3 set output and set pin function
	PA_DDR |= ( (1 << 3) | (1 << 2) | (1 << 1) );
	// MAKE PUSH-PULL,DEFAULT OPEN DRAIN
	PA_CR1 |= ( (1 << 3) | (1 << 2) | (1 << 1) );
	// PA1,PA2,PA3 OUTPUT LOW IF NO NEED MAKE //
	PA_ODR &= ~( (1 << 3) | (1 << 2) | (1 << 1) );

	//  MAKE PC3 SETTING DIRECTION INPUT
	PC_DDR &= ~(1 << 3);

	//  MAKE PB4 LIMIT SWITCH ERROR INPUT
	PB_DDR &= ~(1 << 4);

	// MAKE PB5 LATCH OUTPUT
	PB_DDR |= (1 << 5);
	// MAKE PUSH-PULL,DEFAULT OPEN DRAIN
	PB_CR1 |= (1 << 5);

	// PC4 STANDBY OUTPUT CCO Fmaster OUTPUT
	// CONFIGURE PC4 AS OUTPUT
	PC_DDR |= (1 << 4);
	// PUSH PULL MODE
	PC_CR1 |= (1 << 4);
	// FAST MODE ENABLE
	PC_CR2 |= (1 << 4);
	// CLOCK OUTPUT ON PC4
	// (0xC << 1) = Fmaster
	CLK_CCOR |= ( (1 << 0) | (0xC << 1) );

	//  ADC SETTING
	//  LEFT AIGN SETTING DEFAULT
	//  WAKE UP ADC FROM POWER DOWN
	ADC1_CR1 |= (1 << ADC1_CR1_ADON);


	// MAKE PD4 BEEP



	// MAKE UART INIT



	// MAKE SPI INIT


}
