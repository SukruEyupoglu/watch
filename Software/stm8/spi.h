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
 
void spi_init(void);

unsigned char spi(unsigned char data);

#endif /* SPI_H */

