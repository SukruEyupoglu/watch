#ifndef SPI_H
#define SPI_H

// if using uint8_t or uint16_t or uint32_t
// this must include
// #include <stdint.h>

/*
 * Initialize SPI in MODE1.
 *
 * Pinout:
 * SCK  -> PC5
 * MOSI -> PC6
 * MISO -> PC7
 * CS   -> user defined
 */
 
// spi clock channel select
// stm8s has A1,A2,A3 pins not A0 pin
// directly write to PA DATA register this calculated values
#define CLK_CH_M0        0x0
#define CLK_CH_M1        0x2
#define CLK_CH_M2        0x4
#define CLK_CH_M3        0x6
#define CLK_CH_GPIO_OUT  0x8
#define CLK_CH_GPIO_IN   0xC
#define CLK_CH_FLASH     0xA
#define CLK_CH_SRAM      0xE

void spi_init(void);
unsigned char spi(unsigned char data);
void change_spi_clk_channel(unsigned char channel);

#endif /* SPI_H */

