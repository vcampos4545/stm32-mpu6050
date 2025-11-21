/**
 * mpu6050.h
 *
 * MPU6050 6-axis IMU Driver
 * Accelerometer + Gyroscope sensor
 */

#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

/* MPU6050 I2C Addresses */
#define MPU6050_ADDR_LOW  0x68 // AD0 pin = GND
#define MPU6050_ADDR_HIGH 0x69 // AD0 pin = VCC

/* MPU6050 Register Addresses */
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_PWR_MGMT_1   0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_GYRO_XOUT_H  0x43

/**
 * Initialize MPU6050
 * Wakes up the sensor from sleep mode
 */
void mpu6050_init(uint8_t device_addr);

/**
 * Read WHO_AM_I register
 * Should return 0x68
 */
uint8_t mpu6050_who_am_i(void);

/**
 * Read accelerometer data
 * @param ax, ay, az: Pointers to store X, Y, Z acceleration
 */
void mpu6050_read_accel(int16_t *ax, int16_t *ay, int16_t *az);

/**
 * Read gyroscope data
 * @param gx, gy, gz: Pointers to store X, Y, Z angular velocity
 */
void mpu6050_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz);

#endif /* MPU6050_H */
