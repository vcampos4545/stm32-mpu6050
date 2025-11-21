/**
 * led.h
 *
 * LED Driver for STM32F411 Black Pill
 * PC13: Built-in LED (active low)
 */

#ifndef LED_H
#define LED_H

/**
 * Initialize LED GPIO
 */
void led_init(void);

/**
 * Turn LED on
 */
void led_on(void);

/**
 * Turn LED off
 */
void led_off(void);

/**
 * Toggle LED state
 */
void led_toggle(void);

/**
 * Flash LED for ms milliseconds
 */
void blink_led(int ms);

#endif /* LED_H */
