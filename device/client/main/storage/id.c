#include "nvs_helpers.h"

#define ID_STORAGE_KEY "id"

esp_err_t get_id(int32_t *value) {
    return get_i32(ID_STORAGE_KEY, value);
}

esp_err_t set_id(int32_t value) {
    return set_i32(ID_STORAGE_KEY, value);
}