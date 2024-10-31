#include "nvs_helpers.h"
#include "../led/led.h"

#define ENABLED_STORAGE_KEY "enabled"

esp_err_t get_enabled(bool *value) {
    return get_bool(ENABLED_STORAGE_KEY, value);
}

esp_err_t set_enabled(bool value) {
    led_set(value);
    return set_bool(ENABLED_STORAGE_KEY, value);
}