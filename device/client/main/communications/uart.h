#ifndef UART_H
#define UART_H

#include <esp_err.h>

void start_uart(void);
esp_err_t write_uart(char* message);

#endif