#ifndef I2C_H
#define I2C_H

// this line must be true path, making error :)
#include </home/qwe/soft/stm8/sdcc-3.6.0/share/sdcc/include/stdint.h>

#define I2C_READ            0x01
#define I2C_WRITE           0x00

/**
 * newly 400khz added to init
 * Initialize I2C at 100kHz, 7-bit addressing mode.
 *
 * SDA -> PB5
 * SCL -> PB4
 */
void i2c_init(void);

/**
 * Generate START condition.
 */
void i2c_start(void);

/**
 * Generate STOP condition.
 */
void i2c_stop(void);

/**
 * Write one byte.
 *
 * @param data
 */

void i2c_write(uint8_t data);

/**
 * Write slave address.
 *
 * @param addr slave address (must be shifted!)
 */
void i2c_write_addr(uint8_t addr);

/**
 * Read >= 2 bytes. STOP is generated automatically.
 *
 * @param buf destination buffer
 * @param len buffer length
 */
void i2c_read_arr(uint8_t *buf, int len);

/*
 * Read one byte. STOP is generated automatically.
 */
uint8_t i2c_read();

#endif /* I2C_H */








