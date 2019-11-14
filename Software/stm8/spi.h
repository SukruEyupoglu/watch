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
#define CLK_CH_M0
#define CLK_CH_M1
#define CLK_CH_M2
#define CLK_CH_M3
#define CLK_CH_GPIO_OUT
#define CLK_CH_GPIO_IN
#define CLK_CH_FLASH
#define CLK_CH_SRAM

void spi_init(void);
unsigned char spi(unsigned char data);
void change_spi_clk_channel(unsigned char channel);

#endif /* SPI_H */

