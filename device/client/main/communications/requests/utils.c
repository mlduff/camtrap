#include "./utils.h"

#include "../../storage/server_address.h"

esp_err_t make_server_url(char url[], char* path) {
    char* server_address = NULL;
    size_t server_address_length;
    esp_err_t err = get_server_address(&server_address, &server_address_length);

    if (err == ESP_OK) {
        snprintf(url, URL_SIZE, "http://%s%s", server_address, path);
    }

    return err;
}