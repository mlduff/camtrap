#ifndef LED_H
#define LED_H

#include <stdbool.h>

#define LED_PIN GPIO_NUM_2

void led_init();
void led_set(bool enabled);

#endif