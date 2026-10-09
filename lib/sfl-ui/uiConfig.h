#ifndef UICONFIG_H
#define UICONFIG_H

// LISTA DE PORTS DISPONIBLES
/*
 * uiConfig.h: incluye solo ui_port_list.h y define UI_PORT (con #ifndef, para pisarlo desde build_flags). 
 * Nunca incluye ui_port.h, para evitar ciclos.
*/
#include "portable/ui_portList.h"

// Select the port to use for the UI library
#ifndef UI_PORT
#define UI_PORT UI_PORT_ESP32S
#endif

#endif // UICONFIG_H