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
// FREERTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#ifdef __cplusplus
extern "C" {
#endif

// Puerto UART para consola (logs, info, debug)
#define UART_DEBUG UART_NUM_0

// CONFIGS (AGREGAR BLOQUE IFNDEF)
#define UI_PORT_ECHO_BY_PORT 1      // la ISR ya hace eco
#define UI_PORT_WRITE_BLOCKS 1      // si write espera cuando el buffer está lleno
#define UI_PORT_TX_BUFFER_SIZE 128  // si el core necesita fragmentar

#ifdef __cplusplus
}
#endif

#endif // ESP32S_H