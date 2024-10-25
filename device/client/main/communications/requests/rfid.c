#include <esp_log.h>
#include <esp_err.h>
#include "esp_check.h"
#include "esp_http_client.h"
#include "stdio.h"
#include <cJSON.h>

#include "../../storage/id.h"
#include "../../storage/enabled.h"
#include "./utils.h"

// The number of characters required (including null terminator) to represent the ID
#define BUFFER_SIZE 256

static const char *TAG = "client:connect";


// TODO: Refactor to remove duplication
esp_err_t _rfid_http_event_handle(esp_http_client_event_t *evt)
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

esp_err_t send_rfid(char* uid)
{
    esp_err_t ret;

    char url[URL_SIZE];

    ESP_RETURN_ON_ERROR(make_server_url(url, "/devices/rfid"), TAG, "Failed to connect to the server.");

    esp_http_client_config_t config = {
        .url = url,
        .event_handler = _rfid_http_event_handle,
    };
    
    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL) {
        return ESP_FAIL;
    }

    // Maximum number represnted by int8 has 10 digits
    // Therefore need to store 10 digits and a null terminator
    char post_data[BUFFER_SIZE] = {0};
    strncpy(post_data, uid, strlen(uid));

    // Set the HTTP method to POST
    ESP_GOTO_ON_ERROR(esp_http_client_set_method(client, HTTP_METHOD_POST), err, TAG, "Error setting HTTP method.");
    ESP_GOTO_ON_ERROR(esp_http_client_set_header(client, "Content-Type", "text/plain"), err, TAG, "Error setting HTTP header.");
    ESP_GOTO_ON_ERROR(esp_http_client_set_post_field(client, post_data, strlen(post_data)), err, TAG, "Error setting HTTP post field.");
    ret = esp_http_client_perform(client);

    if (ret == ESP_OK)
    {
        int status_code = esp_http_client_get_status_code(client);
        int content_length = esp_http_client_get_content_length(client);
        ESP_LOGI(TAG, "Status = %d, content_length = %d", status_code, content_length);
    }
    else
    {
        ESP_LOGE(TAG, "Failed to connect to the server: %s", esp_err_to_name(ret));
    }

err:
    esp_http_client_cleanup(client);

    return ret;
}