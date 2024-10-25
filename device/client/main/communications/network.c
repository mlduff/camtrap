#include "esp_wifi.h"
#include <esp_err.h>
#include <esp_log.h>

#include "../storage/wifi_password.h"
#include "../storage/wifi_ssid.h"
#include "../storage/server_address.h"
#include "../storage/id.h"
#include "wifi.h"
#include "requests/connect.h"

static const char* TAG = "client:network";

void network_start() {
    char* wifi_ssid = NULL;
    size_t wifi_ssid_length;
    esp_err_t err = get_wifi_ssid(&wifi_ssid, &wifi_ssid_length);

    char* wifi_password = NULL;
    size_t wifi_password_length;
    err = get_wifi_password(&wifi_password, &wifi_password_length);

    wifi_stop();

    err = wifi_init_sta(
        wifi_ssid,
        wifi_ssid_length,
        wifi_password,
        wifi_password_length
    );

    if (err == ESP_OK) {
        int32_t id;
        err = get_id(&id);
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Stored device ID=%ld.", id);
        } else {
            ESP_LOGE(TAG, "Error reading device ID.");
        }

        err = send_connect(id);
    }
    
    if (err != ESP_OK) {
        ESP_LOGI(TAG, "Couldn't connect to network or server, creating AP.");
        wifi_init_ap();
    }
}