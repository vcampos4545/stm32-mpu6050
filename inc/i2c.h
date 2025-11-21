/**
 * i2c.h
 *
 * I2C1 Driver for STM32F411
 * Master mode at 100 kHz
 */

#ifndef I2C_H
#define I2C_H

#include <stdint.h>

/**
 * Initialize I2C1
 * - PB6: SCL
 * - PB7: SDA
 * - Speed: 100 kHz
 */
void i2c_init(void);

/**
 * Send START condition
 */
void i2c_start(void);

/**
 * Send STOP condition
 */
void i2c_stop(void);

/**
 * Send device address
 * @param address: 7-bit device address
 * @param direction: 0 = write, 1 = read
 */
void i2c_address(uint8_t address, uint8_t direction);

/**
 * Write a byte
 */
void i2c_write(uint8_t data);

/**
 * Read a byte with ACK
 */
uint8_t i2c_read_ack(void);

/**
 * Read a byte with NACK (last byte)
 */
uint8_t i2c_read_nack(void);

#endif /* I2C_H */
