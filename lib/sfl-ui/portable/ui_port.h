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

// UI STATUS
typedef int ui_status_t;
#define UI_OK   0
#define UI_ERR  1

// PROTOTIPOS
ui_status_t ui_port_init(void);
size_t      ui_port_write(const char* data, size_t len);
char        ui_port_read_byte(void);

#endif // UI_PORT_H