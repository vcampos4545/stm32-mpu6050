/**
 * led.c
 *
 * LED Driver Implementation
 */

#include "led.h"
#include "stm32f411.h"
#include "utils.h"

void led_init(void)
{
    // Enable GPIOC clock
    RCC_AHB1ENR |= (1 << 2);

    // Set PC13 as output mode (01)
    GPIOC_MODER &= ~(3 << 26);
    GPIOC_MODER |= (1 << 26);
}

void led_on(void)
{
    GPIOC_ODR &= ~(1 << 13); // Active low
}

void led_off(void)
{
    GPIOC_ODR |= (1 << 13);
}

void led_toggle(void)
{
    GPIOC_ODR ^= (1 << 13);
}

void blink_led(int ms)
{
    led_on();
    delay_ms(ms);
    led_off();
}