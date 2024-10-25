#ifndef CAMERA_H

#define CAMERA_H

#include <esp_err.h>
#include "esp_camera.h"

typedef esp_err_t (*capture_func)(camera_fb_t *fb);

esp_err_t camera_init();
esp_err_t camera_capture(capture_func func);

#endif