#ifndef REQUESTS_UTILS_H
#define REQUESTS_UTILS_H

#include <esp_err.h>

#define URL_SIZE 128

esp_err_t make_server_url(char url[], char* path);

#endif