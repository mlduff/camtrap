#include <esp_log.h>
#include "esp_http_client.h"
#include <esp_err.h>
#include "esp_check.h"

#include "alarm.h"
#include "utils.h"

static const char *TAG = "client:alarm";
// Define the boundary for multipart form-data
static const char *BOUNDARY = "----Boundary";

esp_err_t _alarm_http_event_handle(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER");
        printf("%.*s", evt->data_len, (char *)evt->data);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        if (!esp_http_client_is_chunked_response(evt->client))
        {
            printf("%.*s", evt->data_len, (char *)evt->data);
        }

        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    case HTTP_EVENT_REDIRECT:
        ESP_LOGI(TAG, "HTTP_EVENT_REDIRECT");
        break;
    }
    return ESP_OK;
}

esp_err_t send_alarm(camera_fb_t *fb)
{
    esp_err_t ret;

    char url[URL_SIZE];

    ESP_RETURN_ON_ERROR(make_server_url(url, "/alarms/"), TAG, "Failed to connect to the server.");

    // Prepare the multipart form-data headers
    char header[128];
    snprintf(header,
        sizeof(header),
        "--%s\r\n"
        "Content-Disposition: form-data; name=\"file\"; filename=\"image.jpg\"\r\n"
        "Content-Type: image/jpeg\r\n\r\n",
        BOUNDARY
    );

    char footer[64];
    snprintf(footer, sizeof(footer), "\r\n--%s--\r\n", BOUNDARY);

    // Calculate the total length of the POST data
    int content_length = strlen(header) + fb->len + strlen(footer);

    esp_http_client_config_t config = {
        .url = url,
        .event_handler = _alarm_http_event_handle,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    // Set the HTTP method to POST
    esp_http_client_set_method(client, HTTP_METHOD_POST);

    // Set the Content-Type header for multipart form-data
    char content_type[64];
    snprintf(content_type, sizeof(content_type), "multipart/form-data; boundary=%s", BOUNDARY);
    esp_http_client_set_header(client, "Content-Type", content_type);

    // Open the POST request
    esp_http_client_open(client, content_length);

    // Write the multipart headers
    esp_http_client_write(client, header, strlen(header));

    // Write the image data
    esp_http_client_write(client, (const char *)fb->buf, fb->len);

    // Write the multipart footer
    esp_http_client_write(client, footer, strlen(footer));

    ret = esp_http_client_perform(client);

    if (ret == ESP_OK)
    {
        int status_code = esp_http_client_get_status_code(client);
        int content_length = esp_http_client_get_content_length(client);
        ESP_LOGI(TAG, "Status = %d, content_length = %d", status_code, content_length);
    }
    else
    {
        ESP_LOGE(TAG, "Failed to upload image: %s", esp_err_to_name(ret));
    }

    esp_http_client_cleanup(client);

    return ret;
}