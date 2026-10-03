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

#endif // SERIAL_COM_H