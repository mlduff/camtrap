#ifndef ID_H

#define ID_H

#include <esp_err.h>

esp_err_t set_id(int32_t value);
esp_err_t get_id(int32_t *value);

#endif