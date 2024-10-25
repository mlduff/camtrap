#include <esp_camera.h>
#include <esp_http_server.h>
#include <esp_log.h>

static const char *TAG = "client:server:picture";

esp_err_t picture_handler(httpd_req_t *req)
{
    // Capture a picture using the ESP camera
    camera_fb_t *pic = esp_camera_fb_get();
    
    if (!pic) {
        ESP_LOGE(TAG, "Camera capture failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    // Set the HTTP content type to image/jpeg
    httpd_resp_set_type(req, "image/jpeg");

    // Send the picture as the HTTP response body
    esp_err_t res = httpd_resp_send(req, (const char *)pic->buf, pic->len);

    // Return the frame buffer back to the driver for reuse
    esp_camera_fb_return(pic);

    if (res != ESP_OK) {
        ESP_LOGE(TAG, "Failed to send image");
        return res;
    }

    return ESP_OK;
}