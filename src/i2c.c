/**
 * i2c.c
 *
 * I2C1 Driver Implementation
 */

#include "i2c.h"
#include "stm32f411.h"

void i2c_init(void)
{
    // Enable clocks
    RCC_AHB1ENR |= (1 << 1);  // GPIOB
    RCC_APB1ENR |= (1 << 21); // I2C1

    // Configure PB6 (SCL) and PB7 (SDA)
    // Set to alternate function mode (10)
    GPIOB_MODER &= ~((3 << 12) | (3 << 14));
    GPIOB_MODER |= (2 << 12) | (2 << 14);

    // Open-drain output type
    GPIOB_OTYPER |= (1 << 6) | (1 << 7);

    // High speed
    GPIOB_OSPEEDR |= (3 << 12) | (3 << 14);

    // Pull-up
    GPIOB_PUPDR &= ~((3 << 12) | (3 << 14));
    GPIOB_PUPDR |= (1 << 12) | (1 << 14);

    // Set alternate function AF4 (I2C1)
    GPIOB_AFR[0] &= ~((0xF << 24) | (0xF << 28));
    GPIOB_AFR[0] |= (4 << 24) | (4 << 28);

    // Reset I2C1
    I2C1_CR1 |= (1 << 15);
    I2C1_CR1 &= ~(1 << 15);

    // Configure I2C1
    I2C1_CR2 = 16; // 16 MHz APB1 clock

    // CCR for 100 kHz: CCR = Freq/(2*I2C_Freq) = 16MHz/(2*100kHz) = 80
    I2C1_CCR = 80;

    // TRISE = Freq * rise_time + 1 = 16MHz * 1us + 1 = 17
    I2C1_TRISE = 17;

    // Enable I2C1
    I2C1_CR1 |= I2C_CR1_PE;
}

void i2c_start(void)
{
    I2C1_CR1 |= I2C_CR1_START;
    while (!(I2C1_SR1 & I2C_SR1_SB))
        ;
}

void i2c_stop(void)
{
    I2C1_CR1 |= I2C_CR1_STOP;
}

void i2c_address(uint8_t address, uint8_t direction)
{
    I2C1_DR = (address << 1) | direction;
    while (!(I2C1_SR1 & I2C_SR1_ADDR))
        ;
    (void)I2C1_SR2; // Clear ADDR flag
}

void i2c_write(uint8_t data)
{
    while (!(I2C1_SR1 & I2C_SR1_TXE))
        ;
    I2C1_DR = data;
    while (!(I2C1_SR1 & I2C_SR1_BTF))
        ;
}

uint8_t i2c_read_ack(void)
{
    I2C1_CR1 |= I2C_CR1_ACK;
    while (!(I2C1_SR1 & I2C_SR1_RXNE))
        ;
    return I2C1_DR;
}

uint8_t i2c_read_nack(void)
{
    I2C1_CR1 &= ~I2C_CR1_ACK;
    i2c_stop();
    while (!(I2C1_SR1 & I2C_SR1_RXNE))
        ;
    return I2C1_DR;
}
