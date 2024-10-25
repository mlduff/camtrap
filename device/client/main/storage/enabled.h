#ifndef ENABLED_H

#define ENABLED_H

#include <esp_err.h>

esp_err_t set_enabled(bool value);
esp_err_t get_enabled(bool *value);

#endif