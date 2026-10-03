#ifndef UI_PORT_H
#define UI_PORT_H

/* INCLUDES
 * ui_port.h: incluye uiConfig.h, <stddef.h>, <stdint.h> y <stdbool.h>.
 *  Declara el tipo de status propio y las tres primitivas. 
 * Al final incluye ui_port_select.h.
*/
// INCLUDES
#include "uiConfig.h"
// LIBC
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
// SELECT THE PORT TO USE
#include "portable/ui_portSelect.h"

#endif // UI_PORT_H