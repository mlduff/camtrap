#include <esp_log.h>
#include <esp_err.h>
#include "nvs_flash.h"
#include "esp_camera.h"

#include "communications/wifi.h"
#include "communications/network.h"
#include "communications/uart.h"
#include "communications/requests/connect.h"
#include "communications/requests/alarm.h"
#include "camera/camera.h"
#include "storage/enabled.h"
#include "storage/wifi_ssid.h"
#include "storage/wifi_password.h"
#include "led/led.h"

#ifdef CONFIG_DEFAULT_ENABLED
#define DEFAULT_ENABLED true
#else
#define DEFAULT_ENABLED false
#endif

static const char *TAG = "client:main";

void init_spiffs();
void start_webserver(void);

void app_main(void)
{
    led_init();

    esp_err_t err;
    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    bool enabled;
    err = get_enabled(&enabled);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Enabled status=%s.", enabled ? "true" : "false");
    }
    else if (err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGI(TAG, "Initializing enabled to %s.", DEFAULT_ENABLED ? "true" : "false");
        enabled = DEFAULT_ENABLED;
        set_enabled(enabled);
    }

    start_uart();
    ESP_LOGI(TAG, "Started UART task.");

    ESP_LOGI(TAG, "Performing common WiFi initialization.");
    wifi_init();

    network_start();

    start_webserver();

    init_spiffs();

    err = camera_init();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera initialization failed.");
        return;
    }

    ESP_LOGE(TAG, "Camera initialization succeeded.");
}
