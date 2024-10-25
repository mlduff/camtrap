#include "nvs_helpers.h"

#define SERVER_ADDRESS_STORAGE_KEY "server_address"

esp_err_t get_server_address(char **value, size_t *length) {
    return get_string(SERVER_ADDRESS_STORAGE_KEY, value, length);
}

esp_err_t set_server_address(char *value) {
    return set_string(SERVER_ADDRESS_STORAGE_KEY, value);
}

esp_err_t delete_server_address() {
    return delete_value(SERVER_ADDRESS_STORAGE_KEY);
}