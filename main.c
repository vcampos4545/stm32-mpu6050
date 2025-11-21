/**
 * main.c
 *
 * STM32F411CEU6 Black Pill - MPU6050 I2C Data Logger
 *
 * Hardware Connections:
 * - I2C1: PB6 (SCL), PB7 (SDA)
 * - UART2: PA2 (TX) - 115200 baud
 * - LED: PC13 (built-in, active low)
 * - MPU6050: I2C address 0x68 (AD0 = GND)
 */

#include "inc/led.h"
#include "inc/uart.h"
#include "inc/i2c.h"
#include "inc/mpu6050.h"
#include "inc/utils.h"

int main(void)
{
    uint8_t who_am_i;
    int16_t ax, ay, az; // Accelerometer X, Y, Z
    int16_t gx, gy, gz; // Gyroscope X, Y, Z

    // Initialize all peripherals
    led_init();
    uart_init();
    i2c_init();

    // Send startup message
    uart_puts("\r\n=== STM32 MPU6050 Data Logger ===\r\n");
    uart_puts("Initializing...\r\n");

    // Blink LED to indicate initialization
    blink_led(1000);

    // Initialize MPU6050
    mpu6050_init(MPU6050_ADDR_LOW);
    delay_ms(200);

    // Blink twice for successful led init
    for (int i = 0; i < 2; ++i)
    {
        blink_led(100);
    }

    // Verify MPU6050 is present
    who_am_i = mpu6050_who_am_i();
    uart_puts("MPU6050 WHO_AM_I: 0x");
    uart_putint(who_am_i);
    uart_puts("\r\n");

    if (who_am_i == 0x68)
    {
        uart_puts("MPU6050 found! Starting data logging...\r\n\r\n");
        led_on();

        // Main loop: Read and log sensor data
        while (1)
        {
            // Read accelerometer and gyroscope
            mpu6050_read_accel(&ax, &ay, &az);
            mpu6050_read_gyro(&gx, &gy, &gz);

            // Log data to UART
            uart_puts("Accel: X=");
            uart_putint(ax);
            uart_puts(" Y=");
            uart_putint(ay);
            uart_puts(" Z=");
            uart_putint(az);

            uart_puts(" | Gyro: X=");
            uart_putint(gx);
            uart_puts(" Y=");
            uart_putint(gy);
            uart_puts(" Z=");
            uart_putint(gz);
            uart_puts("\r\n");

            // Toggle LED to show activity
            led_toggle();

            // Wait before next reading
            delay_ms(200);
        }
    }
    else
    {
        // MPU6050 not found - error state
        uart_puts("ERROR: MPU6050 not found!\r\n");

        // Slow blink to indicate error
        while (1)
        {
            led_toggle();
            delay_ms(1000);
        }
    }

    return 0;
}
