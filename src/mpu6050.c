/**
 * mpu6050.c
 *
 * MPU6050 Driver Implementation
 */

#include "mpu6050.h"
#include "i2c.h"

static uint8_t mpu6050_addr; // Device I2C address

static void mpu6050_write_reg(uint8_t reg, uint8_t value)
{
    i2c_start();
    i2c_address(mpu6050_addr, 0); // Write mode
    i2c_write(reg);
    i2c_write(value);
    i2c_stop();
}

static uint8_t mpu6050_read_reg(uint8_t reg)
{
    uint8_t data;

    i2c_start();
    i2c_address(mpu6050_addr, 0); // Write mode
    i2c_write(reg);

    i2c_start();                  // Repeated start
    i2c_address(mpu6050_addr, 1); // Read mode
    data = i2c_read_nack();

    return data;
}

static void mpu6050_read_bytes(uint8_t reg, uint8_t *buffer, uint8_t length)
{
    i2c_start();
    i2c_address(mpu6050_addr, 0); // Write mode
    i2c_write(reg);

    i2c_start();                  // Repeated start
    i2c_address(mpu6050_addr, 1); // Read mode

    for (uint8_t i = 0; i < length - 1; i++)
    {
        buffer[i] = i2c_read_ack();
    }
    buffer[length - 1] = i2c_read_nack();
}

void mpu6050_init(uint8_t device_addr)
{
    mpu6050_addr = device_addr;

    // Wake up MPU6050 (clear sleep bit)
    mpu6050_write_reg(MPU6050_PWR_MGMT_1, 0x00);
}

uint8_t mpu6050_who_am_i(void)
{
    return mpu6050_read_reg(MPU6050_WHO_AM_I);
}

void mpu6050_read_accel(int16_t *ax, int16_t *ay, int16_t *az)
{
    uint8_t data[6];
    mpu6050_read_bytes(MPU6050_ACCEL_XOUT_H, data, 6);

    *ax = (int16_t)((data[0] << 8) | data[1]);
    *ay = (int16_t)((data[2] << 8) | data[3]);
    *az = (int16_t)((data[4] << 8) | data[5]);
}

void mpu6050_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t data[6];
    mpu6050_read_bytes(MPU6050_GYRO_XOUT_H, data, 6);

    *gx = (int16_t)((data[0] << 8) | data[1]);
    *gy = (int16_t)((data[2] << 8) | data[3]);
    *gz = (int16_t)((data[4] << 8) | data[5]);
}
