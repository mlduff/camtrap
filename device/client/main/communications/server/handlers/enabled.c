#include <esp_camera.h>
#include <esp_http_server.h>
#include <esp_log.h>
#include <sys/param.h>
#include <cJSON.h>
#include "driver/gpio.h"
#include "../../../storage/enabled.h"
#include "../../uart.h"

#define BUFFER_SIZE 256

static const char *TAG = "client:server:enabled";

esp_err_t enabled_handler(httpd_req_t *req)
{
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

    ESP_LOGI(TAG, "Received enable request: %s.", content);

    cJSON *json = cJSON_Parse(content);

    cJSON *enabled = cJSON_GetObjectItem(json, "enabled");
    if (cJSON_IsBool(enabled)) {
        if (cJSON_IsTrue(enabled)) {
            set_enabled(true);
            write_uart("enabled\n");
        } else {
            set_enabled(false);
            write_uart("disabled\n");
        }
    }

    cJSON_Delete(json);

    /* Send a simple response */
    const char resp[] = "URI POST Response";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}