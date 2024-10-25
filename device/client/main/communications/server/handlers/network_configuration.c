#include <esp_camera.h>
#include <esp_http_server.h>
#include <esp_log.h>
#include <sys/param.h>
#include <cJSON.h>
#include "../../../storage/wifi_ssid.h"
#include "../../../storage/wifi_password.h"
#include "../../../storage/server_address.h"
#include "../../../communications/network.h"

#define BUFFER_SIZE 256

static const char *TAG = "client:server:enabled";

esp_err_t network_configuration_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Received network configuration POST request.");
    /* Destination buffer for content of HTTP POST request.
     * httpd_req_recv() accepts char* only, but content could
     * as well be any binary data (needs type casting).
     * In case of string data, null termination will be absent, and
     * content length would give length of string */
    char content[BUFFER_SIZE];

    /* Truncate if content length larger than the buffer */
    size_t recv_size = MIN(req->content_len, sizeof(content));

    int ret = httpd_req_recv(req, content, recv_size);
    if (ret <= 0) {  /* 0 return value indicates connection closed */
        /* Check if timeout occurred */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            /* In case of timeout one can choose to retry calling
             * httpd_req_recv(), but to keep it simple, here we
             * respond with an HTTP 408 (Request Timeout) error */
            httpd_resp_send_408(req);
        }
        /* In case of error, returning ESP_FAIL will
         * ensure that the underlying socket is closed */
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Received configuration request: %s.", content);

    cJSON *json = cJSON_Parse(content);

    cJSON *ssid = cJSON_GetObjectItem(json, "ssid");
    if (cJSON_IsString(ssid)) {
        char* ssid_value = ssid->valuestring;
        set_wifi_ssid(ssid_value);
    } else if (cJSON_IsNull(ssid)) {
        delete_wifi_password();
    }

    cJSON *password = cJSON_GetObjectItem(json, "password");
    if (cJSON_IsString(password)) {
        char* password_value =  password->valuestring;
        set_wifi_password(password_value);
    } else if (cJSON_IsNull(password)) {
        delete_wifi_password();
    }

    cJSON *server_address = cJSON_GetObjectItem(json, "server_address");
    if (cJSON_IsString(server_address)) {
        char* server_address_value =  server_address->valuestring;
        set_server_address(server_address_value);
    } else if (cJSON_IsNull(server_address)) {
        delete_server_address();
    }

    cJSON_Delete(json);

    /* Send a simple response */
    const char resp[] = "URI POST Response";
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);

    network_start();

    return ESP_OK;
}

esp_err_t network_configuration_options_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Received network configuration OPTIONS request.");
    
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");

    // Send an empty response
    httpd_resp_send(req, NULL, 0);
    ESP_LOGI(TAG, "OPTIONS request handled");
    return ESP_OK;
}