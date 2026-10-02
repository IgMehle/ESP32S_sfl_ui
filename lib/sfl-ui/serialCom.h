#pragma once

#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
// PORT INCLUDES
#include "driver/uart.h"
#include "esp_err.h"
#include "esp_log.h"
#ifdef __cplusplus
extern "C" {
#endif

// Puerto UART para consola (logs, info, debug)
#define UART_DEBUG UART_NUM_0

esp_err_t initUart();
void sendUartDataln(const uint8_t* data, size_t len);
void sendUartData(const uint8_t* data, size_t len);
void writeSerialComln(const char* data);
void writeSerialCom(const char* data);
void clearScreen();
char readUserChar(void);
void updateUartBuffers();

void print(const char* str);
void printFormat(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif // SERIAL_COM_H