/**
 * CONTENIDO
 * #if UI_PORT == UI_PORT_ESP32_UART, e incluye driver/uart.h y esp_log.h. 
 * Implementa ui_port_init (uart_param_config, driver_install, la guarda de reinicio y el flag consolaIniciada), 
 * ui_port_write (uart_write_bytes) y ui_port_read_byte (uart_read_bytes con timeout 0). 
 * La config de uart_config1 y UART_NUM_0 van acá.
 */
// PORTABLE
#include "ui_port.h" 

#if UI_PORT == UI_PORT_ESP32S
/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/
// ESP32
#include "esp_err.h"
#include "esp_log.h"
// FREERTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// DRIVERS
#include <driver/uart.h>

// Puerto UART para consola (logs, info, debug)
#ifndef UART_DEBUG
#define UART_DEBUG UART_NUM_0
#endif
// BAUDRATE
#ifndef UI_UART_BAUD
#define UI_UART_BAUD 115200
#endif

uart_config_t uart_config1;
bool consolaIniciada=false;

ui_status_t ui_port_init(void)
{
    esp_err_t ret;
    //ui_status_t status;

    // Guarda: ya inicializada -> verificar consistencia y salir
    if (consolaIniciada) {
        if (uart_is_driver_installed(UART_DEBUG)) {
            ESP_LOGW("SerialCom", "UART ya inicializada, se omite reinit");
            return UI_OK;
        } else {
            // Bandera desincronizada del estado real del driver
            ESP_LOGW("SerialCom", "Flag inconsistente, reinicializando");
            consolaIniciada = false;
        }
    }

    // ===== UART0 (CONSOLA) =====
    uart_config1 = (uart_config_t){
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0
    };

    ret = uart_param_config(UART_DEBUG, &uart_config1);
    if (ret != ESP_OK) {
        ESP_LOGE("SerialCom", "uart_param_config fallo: %s", esp_err_to_name(ret));
        return UI_ERR;
    }

    ret = uart_driver_install(UART_DEBUG, 1024, 1024, 0, NULL, 0);
    if (ret != ESP_OK) {
        ESP_LOGE("SerialCom", "uart_driver_install fallo: %s", esp_err_to_name(ret));
        return UI_ERR;
    }

    consolaIniciada = true;
    ESP_LOGI("SerialCom", "Consola iniciada");
    return UI_OK;
}

size_t ui_port_write(const char *data, size_t len)
{
    int bytesWritten = 0;
    // escritura de bytes de UART ESP32S
    bytesWritten = uart_write_bytes(UART_DEBUG, data, len);
    // aseguro que no devuelva -1 ante un error
    if (bytesWritten < 0) bytesWritten = 0;
    return (size_t)(bytesWritten);
}

char ui_port_read_byte(void)
{
    char ch;

    int len = uart_read_bytes(UART_DEBUG, &ch, 1, 0);
    if (len > 0) {
        // Echo del carácter
        uart_write_bytes(UART_DEBUG, (const char *)&ch, 1);

        // Si la terminal envía \r, lo descartamos si viene seguido de \n,
        // lo convierto a \n directamente.
        if (ch == '\r') {
            return '\n'; // Normaliza cualquier Enter (\r o \n) a '\n'
        }
        else return ch;
    }
    return '\0';
}

#if UI_LOG_ENABLE
void ui_log(ui_log_level_t lvl, const char *tag, const char *msg)
{
    switch (lvl) {
    case UI_LOG_ERROR:  ESP_LOGE(tag, "%s", msg); break;
    case UI_LOG_WARN:   ESP_LOGW(tag, "%s", msg); break;
    case UI_LOG_INFO:   ESP_LOGI(tag, "%s", msg); break;
    case UI_LOG_DEBUG:  ESP_LOGD(tag, "%s", msg); break;
    case UI_LOG_VERBOSE: ESP_LOGV(tag, "%s", msg); break;
    default: break;
    }
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
#endif // UI_PORT == UI_PORT_ESP32S