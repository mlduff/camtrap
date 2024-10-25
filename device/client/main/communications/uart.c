/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include <string.h>
#include "requests/alarm.h"
#include "requests/rfid.h"
#include "../camera/camera.h"
#include "../storage/enabled.h"

/**
 * This is an example which echos any data it receives on configured UART back to the sender,
 * with hardware flow control turned off. It does not use UART driver event queue.
 *
 * - Port: configured UART
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: off
 * - Pin assignment: see defines below (See Kconfig)
 */

#define UART_TXD_PIN 33
#define UART_RXD_PIN 32
#define ECHO_TEST_RTS UART_PIN_NO_CHANGE
#define ECHO_TEST_CTS UART_PIN_NO_CHANGE

#define UART_PORT_NUM 2
#define UART_BAUD_RATE 9600
#define TASK_STACK_SIZE 4096

static const char *TAG = "client:uart";

#define BUF_SIZE 1024

static const char *RFID_PREFIX = "rfid ";

static void setup_uart() {
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM, UART_TXD_PIN, UART_RXD_PIN, ECHO_TEST_RTS, ECHO_TEST_CTS));
}

esp_err_t write_uart(char* data) {
    ESP_LOGI(TAG, "Writing to UART: %s", data);
    int status = uart_write_bytes(UART_PORT_NUM, data, strlen(data));
    if (status < 0) {
        ESP_LOGE(TAG, "Failed to write data to UART.");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Successfully wrote %d bytes to UART.", status);

    return ESP_OK;
}

static void uart_task()
{
    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        if (len) {
            data[len] = '\0';
            char *message = (char *) data;
            ESP_LOGI(TAG, "Recv str: %s", message);
            if (strncmp(message, "start", len) == 0) {
                bool enabled;
                esp_err_t err = get_enabled(&enabled);
                if (err == ESP_OK) {
                    write_uart(enabled ? "enabled" : "disabled");
                }
            } else if (strncmp(message, "alarm", len) == 0) {
                ESP_LOGI(TAG, "Alarm signal received.");
                bool enabled;
                esp_err_t err = get_enabled(&enabled);
                if (err == ESP_OK) {
                    if (enabled) {
                        camera_capture(send_alarm);
                    } else {
                        ESP_LOGI(TAG, "Alarm is disabled.");
                    }
                }
            } else if (strncmp(message, RFID_PREFIX, strlen(RFID_PREFIX)) == 0) {
                size_t uid_length = len - strlen(RFID_PREFIX) + 1;
                char* uid = malloc(uid_length);

                strncpy(uid, message + strlen(RFID_PREFIX), uid_length - 1);
                uid[uid_length - 1] = '\0';
                
                ESP_LOGI(TAG, "Received RFID UID: %s", uid);

                send_rfid(uid);

                free(uid);
            }
        }
    }
}

static void setup_and_execute_uart_task(void *arg) {
    setup_uart();
    uart_task();
}

void start_uart() {
    xTaskCreate(setup_and_execute_uart_task, "uart_task", TASK_STACK_SIZE, NULL, 10, NULL);
}