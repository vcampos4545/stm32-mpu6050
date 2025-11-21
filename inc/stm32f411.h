/**
 * stm32f411.h
 *
 * STM32F411CEU6 Register Definitions
 * Contains all hardware register addresses and bit definitions
 */

#ifndef STM32F411_H
#define STM32F411_H

#include <stdint.h>

/* Base Addresses */
#define PERIPH_BASE     0x40000000UL
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)

/* ========== RCC (Reset and Clock Control) ========== */
#define RCC_BASE    (AHB1PERIPH_BASE + 0x3800UL)
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x40))

/* ========== GPIO Port A ========== */
#define GPIOA_BASE    (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOA_MODER   (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_OSPEEDR (*(volatile uint32_t *)(GPIOA_BASE + 0x08))
#define GPIOA_AFR     ((volatile uint32_t *)(GPIOA_BASE + 0x20))

/* ========== GPIO Port B ========== */
#define GPIOB_BASE    (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOB_MODER   (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPER  (*(volatile uint32_t *)(GPIOB_BASE + 0x04))
#define GPIOB_OSPEEDR (*(volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_PUPDR   (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
#define GPIOB_AFR     ((volatile uint32_t *)(GPIOB_BASE + 0x20))

/* ========== GPIO Port C ========== */
#define GPIOC_BASE  (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOC_MODER (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR   (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

/* ========== I2C1 ========== */
#define I2C1_BASE  (APB1PERIPH_BASE + 0x5400UL)
#define I2C1_CR1   (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2   (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_DR    (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_SR1   (*(volatile uint32_t *)(I2C1_BASE + 0x14))
#define I2C1_SR2   (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_CCR   (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define I2C1_TRISE (*(volatile uint32_t *)(I2C1_BASE + 0x20))

/* I2C CR1 Bits */
#define I2C_CR1_PE    (1 << 0)
#define I2C_CR1_START (1 << 8)
#define I2C_CR1_STOP  (1 << 9)
#define I2C_CR1_ACK   (1 << 10)

/* I2C SR1 Bits */
#define I2C_SR1_SB   (1 << 0)
#define I2C_SR1_ADDR (1 << 1)
#define I2C_SR1_BTF  (1 << 2)
#define I2C_SR1_RXNE (1 << 6)
#define I2C_SR1_TXE  (1 << 7)

/* ========== USART2 ========== */
#define USART2_BASE (APB1PERIPH_BASE + 0x4400UL)
#define USART2_SR   (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR   (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR  (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1  (*(volatile uint32_t *)(USART2_BASE + 0x0C))

/* USART Bits */
#define USART_SR_TC  (1 << 6)
#define USART_SR_TXE (1 << 7)
#define USART_CR1_TE (1 << 3)
#define USART_CR1_UE (1 << 13)

#endif /* STM32F411_H */
