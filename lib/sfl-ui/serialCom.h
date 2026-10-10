#pragma once

#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

// CONFIG Y PORTABLE
#include "uiConfig.h"
#include "portable/ui_port.h"

// INIT
int initUart(void);

// WRITE
void sendUartData(const uint8_t* data, size_t len);
void sendUartDataln(const uint8_t* data, size_t len);
void ui_print(const char* str);
void ui_printFormat(const char* format, ...);
void writeSerialCom(const char* data);
void writeSerialComln(const char* data);
void clearScreen(void);
//void updateUartBuffers(void);

// READ
char readUserChar(void);

#endif // SERIAL_COM_H