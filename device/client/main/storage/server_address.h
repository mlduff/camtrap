#ifndef SERVER_ADDRESS_H

#define SERVER_ADDRESS_H

#include <esp_err.h>

esp_err_t get_server_address(char **value, size_t *length);
esp_err_t set_server_address(char *value);
esp_err_t delete_server_address();

#endif