#include "nvs_helpers.h"
#include "../led/led.h"

#define ENABLED_STORAGE_KEY "enabled"

esp_err_t get_enabled(bool *value) {
    esp_err_t ret = get_bool(ENABLED_STORAGE_KEY, value);
    if (ret == ESP_OK) {
        led_set(*value);
    }
    return ret;
}

esp_err_t set_enabled(bool value) {
    led_set(value);
    return set_bool(ENABLED_STORAGE_KEY, value);
}