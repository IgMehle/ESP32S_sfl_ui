#ifndef UI_PORTSELECT_H
#define UI_PORTSELECT_H

// CONFIGURACIONES Y PORTS
#include "../uiConfig.h"

// SELECT THE PORT TO USE
#if UI_PORT == UI_PORT_ESP32S
    #include "esp32s.h"
#endif // UI_PORT == UI_PORT_ESP32S

#endif // UI_PORTSELECT_H