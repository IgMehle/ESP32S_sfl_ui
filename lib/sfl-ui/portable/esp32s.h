#ifndef ESP32S_H
#define ESP32S_H

// PORT INCLUDES
/*
 * esp32s.h: solo macros y valores por defecto (puerto, baud, tamaños de buffer, UI_LOG). 
 * Conviene que no incluya driver/uart.h, para que el SDK no se filtre a todo el que incluya serialCom.h. 
 * Esos includes van en el .c.
*/
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

#endif // ESP32S_H