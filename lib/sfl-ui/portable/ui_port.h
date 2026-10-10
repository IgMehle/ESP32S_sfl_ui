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

// UI_STATUS
typedef UI_STATUS_TYPE ui_status_t;
#define UI_OK   0
#define UI_ERR  1

// PROTOTIPOS DEL PORT
ui_status_t ui_port_init(void);
size_t      ui_port_write(const char* data, size_t len);
char        ui_port_read_byte(void);

// UI LOGS
typedef enum { UI_LOG_ERROR, UI_LOG_WARN, UI_LOG_INFO, UI_LOG_DEBUG, UI_LOG_VERBOSE } ui_log_level_t;

#if UI_LOG_ENABLE
void ui_log(ui_log_level_t lvl, const char *tag, const char *msg); // core
void ui_log_format(ui_log_level_t lvl, const char *tag, const char *fmt, ...); // core
void ui_port_log(ui_log_level_t lvl, const char *tag, const char *msg); // port
#else
#define ui_log(...)  ((void)0)
#endif

#endif // UI_PORT_H