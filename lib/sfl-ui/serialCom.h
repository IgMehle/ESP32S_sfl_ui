#pragma once

#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

// CONFIGURACIONES Y PORTS
/*
 * serialCom.h ─► uiConfig.h ─► portable/ui_port_list.h   (catálogo + UI_PORT)
 *       ─► portable/ui_port.h  (contrato + tipo de status)
 *      └─► portable/ui_port_select.h ─► port.h
*/
#include "uiConfig.h"
#include "portable/ui_port.h"

esp_err_t initUart(void);
void sendUartDataln(const uint8_t* data, size_t len);
void sendUartData(const uint8_t* data, size_t len);
void writeSerialComln(const char* data);
void writeSerialCom(const char* data);
void clearScreen(void);
char readUserChar(void);
void updateUartBuffers(void);

void print(const char* str);
void printFormat(const char* format, ...);

#endif // SERIAL_COM_H