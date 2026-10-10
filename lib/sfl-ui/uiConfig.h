#ifndef UICONFIG_H
#define UICONFIG_H

// LISTA DE PORTS DISPONIBLES
#include "portable/ui_portList.h"

// PORT SELECT
#ifndef UI_PORT
#define UI_PORT UI_PORT_ESP32S
#endif

// UI_LOG_ENABLE
#ifndef UI_LOG_ENABLE
#define UI_LOG_ENABLE 1
#endif

// UI_STATUS TYPE
#ifndef UI_STATUS_TYPE
#define UI_STATUS_TYPE int
#endif

// ECHO BY PORT
#ifndef UI_PORT_ECHO_BY_PORT
#define UI_PORT_ECHO_BY_PORT 1
#endif

#endif // UICONFIG_H