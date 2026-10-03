#ifndef UICONFIG_H
#define UICONFIG_H

// LISTA DE PORTS DISPONIBLES
/*
 * uiConfig.h: incluye solo ui_port_list.h y define UI_PORT (con #ifndef, para pisarlo desde build_flags). 
 * Nunca incluye ui_port.h, para evitar ciclos.
*/
#include "portable/ui_portList.h"

// Select the port to use for the UI library
#define UI_PORT UI_PORT_ESP32S

// CONFIGS
#define UI_PORT_ECHO_BY_PORT 1      // la ISR ya hace eco
#define UI_PORT_WRITE_BLOCKS 1      // si write espera cuando el buffer está lleno
#define UI_PORT_TX_BUFFER_SIZE 128  // si el core necesita fragmentar

#endif // UICONFIG_H