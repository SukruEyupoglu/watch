/*
 * board_init.h
 *
 *  Created on: 17 Eki 2020
 *      Author: Sukru
 */

#ifndef BOARD_INIT_H_
#define BOARD_INIT_H_

#define ACTIVE_MOTOR_1_CLK PA_ODR = 0
#define ACTIVE_MOTOR_2_CLK PA_ODR = 2
#define ACTIVE_MOTOR_3_CLK PA_ODR = 4
#define ACTIVE_MOTOR_4_CLK PA_ODR = 6
#define ACTIVE_OUT_SCK_CLK PA_ODR = 8
#define ACTIVE_FLASH_SCK_CLK PA_ODR = 10
#define ACTIVE_IN_SCK_CLK PA_ODR = 12
#define ACTIVE_RF_SCK_CLK PA_ODR = 14

#define LATCH PB_ODR |= (1 << 5);PB_ODR &= ~(1 << 5) // latch assert(LOW) ; latch deassert(HIGH)
/*
  		spi(0x00); // second 74HC595
		spi(0xFF); // first 74HC595
		PB_ODR |= (1 << 5); // latch assert(LOW)
		PB_ODR &= ~(1 << 5); // latch deassert(HIGH)
		delay_ms(255);
		spi(0x00); // second 74HC595
		spi(0x00); // first 74HC595
		PB_ODR |= (1 << 5);
		PB_ODR &= ~(1 << 5);
		delay_ms(255);
 */

void board_init(void);

#endif /* BOARD_INIT_H_ */
