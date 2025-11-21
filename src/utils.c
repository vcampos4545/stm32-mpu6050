/**
 * utils.c
 *
 * Utility Functions Implementation
 */

#include "utils.h"

void delay_ms(uint32_t ms)
{
    // Approximate delay at 16 MHz
    for (uint32_t i = 0; i < ms * 4000; i++)
    {
        __asm__ volatile("nop");
    }
}
