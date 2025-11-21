/**
 * uart.h
 *
 * UART2 Driver for STM32F411
 * Provides serial communication at 115200 baud
 */

#ifndef UART_H
#define UART_H

#include <stdint.h>

/**
 * Initialize UART2
 * - PA2: TX
 * - Baud rate: 115200
 */
void uart_init(void);

/**
 * Send a single character
 */
void uart_putc(char c);

/**
 * Send a null-terminated string
 */
void uart_puts(const char *str);

/**
 * Send a signed integer
 */
void uart_putint(int32_t num);

#endif /* UART_H */
