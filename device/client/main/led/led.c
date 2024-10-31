#include "led.h"
#include "driver/gpio.h"

void led_init() {
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
}

void led_set(bool enabled) {
    gpio_set_level(LED_PIN, enabled);
}