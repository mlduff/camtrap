#include <esp_http_server.h>
#include <esp_log.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "esp_check.h"
#include <sys/param.h>
#include "esp_camera.h"

static const char *TAG = "client:server:enable";

esp_err_t index_handler(httpd_req_t *req);
esp_err_t picture_handler(httpd_req_t *req);
esp_err_t enabled_handler(httpd_req_t *req);
esp_err_t network_configuration_handler(httpd_req_t *req);
esp_err_t network_configuration_options_handler(httpd_req_t *req);

/* URI handler structure for GET /uri */
httpd_uri_t get_index = {
    .uri      = "/",
    .method   = HTTP_GET,
    .handler  = index_handler,
    .user_ctx = NULL
};

/* URI handler structure for GET /uri */
httpd_uri_t get_picture = {
    .uri      = "/picture",
    .method   = HTTP_GET,
    .handler  = picture_handler,
    .user_ctx = NULL
};

/* URI handler structure for POST /uri */
httpd_uri_t post_enabled = {
    .uri      = "/enabled",
    .method   = HTTP_POST,
    .handler  = enabled_handler,
    .user_ctx = NULL
};

httpd_uri_t post_network_configuration = {
    .uri      = "/network",
    .method   = HTTP_POST,
    .handler  = network_configuration_handler,
    .user_ctx = NULL
};

httpd_uri_t options_network_configuration = {
    .uri      = "/network",
    .method   = HTTP_OPTIONS,
    .handler  = network_configuration_options_handler,
    .user_ctx = NULL
};

/* Function for starting the webserver */
httpd_handle_t start_webserver(void)
{
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK) {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &get_index);
        httpd_register_uri_handler(server, &get_picture);
        httpd_register_uri_handler(server, &post_enabled);
        httpd_register_uri_handler(server, &post_network_configuration);
        httpd_register_uri_handler(server, &options_network_configuration);
    }
    if (server != NULL) {
        ESP_LOGI(TAG, "Server started successfully.");
    } else {
        ESP_LOGE(TAG, "Server did not start correctly.");
    }
    /* If server failed to start, handle will be NULL */
    return server;
}

/* Function for stopping the webserver */
void stop_webserver(httpd_handle_t server)
{
    if (server) {
        /* Stop the httpd server */
        httpd_stop(server);
    }
}