// PORTABLE
#include "ui_port.h"

#if UI_PORT == UI_PORT_RP2350
/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
// PICO2
// DRIVERS
#include <pico/stdlib.h>
#define PICO_USE_USB    1
#define PICO_USE_UART   0

#if PICO_USE_UART
// UART defines
#define UART_ID uart1
#define BAUD_RATE 115200
// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#endif

bool consolaIniciada=false;

ui_status_t ui_port_init(void)
{
#if PICO_USE_UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
#endif
    stdio_init_all();      // inicializa el USB CDC (no repetir si la app ya lo llama)
    return UI_OK;
}

size_t ui_port_write(const char *data, size_t len)
{
#if PICO_USE_USB
    // false, false: sin '\n' extra y sin traducir '\n' a "\r\n"
    len = (size_t) stdio_put_string(data, (int)len, false, false);
    //len = (size_t) printf(data); 
#endif

#if PICO_USE_UART
    uart_write_blocking(UART_ID, (const uint8_t *)data, len);
#endif

    return len;
}

char ui_port_read_byte(void)
{
#if PICO_USE_USB
    return (char) getchar_timeout_us(0);  // 0: no bloquea
#endif

#if PICO_USE_UART
    if (!uart_is_readable(UART_ID)) return '\0';  // sin esto, uart_getc bloquea
    return uart_getc(UART_ID);
#endif
}

#if UI_LOG_ENABLE
void ui_log(ui_log_level_t lvl, const char *tag, const char *msg)
{
#if PICO_USE_USB
    static char log[256];
    switch (lvl) {
    case UI_LOG_ERROR:
        sprintf(log, "[ERROR] %s: %s\n", tag, msg);
        break;
    case UI_LOG_WARN:
        sprintf(log, "[WARN] %s: %s\n", tag, msg);
        break;
    case UI_LOG_INFO:
        sprintf(log, "[INFO] %s: %s\n", tag, msg);
        break;
    case UI_LOG_DEBUG:
        sprintf(log, "[DEBUG] %s: %s\n", tag, msg);
        break;
    case UI_LOG_VERBOSE:
        sprintf(log, "[VERBOSE] %s: %s\n", tag, msg);
        break;
    default:
        log[0] = '\0';
        break;
    }
    printf("%s", log);
#endif

#if PICO_USE_UART
    static char log[256];
    switch (lvl) {
    case UI_LOG_ERROR:
        sprintf(log, "[ERROR] %s: %s\n", tag, msg);
        break;
    case UI_LOG_WARN:
        sprintf(log, "[WARN] %s: %s\n", tag, msg);
        break;
    case UI_LOG_INFO:
        sprintf(log, "[INFO] %s: %s\n", tag, msg);
        break;
    case UI_LOG_DEBUG:
        sprintf(log, "[DEBUG] %s: %s\n", tag, msg);
        break;
    case UI_LOG_VERBOSE:
        sprintf(log, "[VERBOSE] %s: %s\n", tag, msg);
        break;
    default:
        log[0] = '\0';
        break;
    }
    uart_write_blocking(UART_ID, (const uint8_t *)log, strlen(log)); 
#endif
}

void ui_log_format(ui_log_level_t lvl, const char *tag, const char *fmt, ...)
{

}

void ui_port_log(ui_log_level_t lvl, const char *tag, const char *msg)
{
    
}
#endif
/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/
#endif // UI_PORT == UI_PORT_RP2350