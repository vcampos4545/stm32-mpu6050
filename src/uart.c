/**
 * uart.c
 *
 * UART2 Driver Implementation
 */

#include "uart.h"
#include "stm32f411.h"

void uart_init(void)
{
    // Enable clocks
    RCC_AHB1ENR |= (1 << 0);  // GPIOA
    RCC_APB1ENR |= (1 << 17); // USART2

    // Configure PA2 (TX) as alternate function
    GPIOA_MODER &= ~(3 << 4); // Clear PA2 mode bits
    GPIOA_MODER |= (2 << 4);  // Set PA2 to alternate function mode

    // Set high speed
    GPIOA_OSPEEDR |= (3 << 4);

    // Set alternate function AF7 for USART2
    GPIOA_AFR[0] &= ~(0xF << 8); // Clear PA2 AF bits
    GPIOA_AFR[0] |= (7 << 8);    // AF7 = USART2

    // Configure USART2
    // Baud rate = 115200, APB1 clock = 16 MHz
    // BRR = 16MHz / 115200 = 138.88 ≈ 139 (0x8B)
    USART2_BRR = 139;

    // Enable USART2 and transmitter
    USART2_CR1 |= USART_CR1_TE; // Enable transmitter
    USART2_CR1 |= USART_CR1_UE; // Enable USART
}

void uart_putc(char c)
{
    while (!(USART2_SR & USART_SR_TXE))
        ; // Wait for transmit buffer to be empty
    USART2_DR = c;
}

void uart_puts(const char *str)
{
    while (*str)
    {
        uart_putc(*str++);
    }
}

void uart_putint(int32_t num)
{
    char buffer[12]; // Enough for -2147483648
    int i = 0;

    // Handle negative numbers
    if (num < 0)
    {
        uart_putc('-');
        num = -num;
    }

    // Handle zero
    if (num == 0)
    {
        uart_putc('0');
        return;
    }

    // Convert to string (reverse order)
    while (num > 0)
    {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    // Print in correct order
    while (i > 0)
    {
        uart_putc(buffer[--i]);
    }
}
