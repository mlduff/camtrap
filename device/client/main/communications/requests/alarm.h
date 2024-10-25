#ifndef ALARM_H

#include "esp_camera.h"

#define ALARM_H

esp_err_t send_alarm(camera_fb_t *fb);

#endif