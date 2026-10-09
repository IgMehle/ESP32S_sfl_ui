#include "esp32s.h"
#include "ui_port.h"
// DRIVERS
#include "driver/uart.h"

/**
 * CONTENIDO
 * #if UI_PORT == UI_PORT_ESP32_UART, e incluye driver/uart.h y esp_log.h. 
 * Implementa ui_port_init (uart_param_config, driver_install, la guarda de reinicio y el flag consolaIniciada), 
 * ui_port_write (uart_write_bytes) y ui_port_read_byte (uart_read_bytes con timeout 0). 
 * La config de uart_config1 y UART_NUM_0 van acá.
 */

#if UI_PORT == UI_PORT_ESP32S

uart_config_t uart_config1;
bool consolaIniciada=false;

ui_status_t ui_port_init(void)
{

}

size_t ui_port_write(const uint8_t *buf, size_t len)
{

}

int ui_port_read_byte(void)
{

}

esp_err_t initUart(void)
{
    esp_err_t ret;

    // Guarda: ya inicializada -> verificar consistencia y salir
    if (consolaIniciada) {
        if (uart_is_driver_installed(UART_DEBUG)) {
            ESP_LOGW("SerialCom", "UART ya inicializada, se omite reinit");
            return ESP_OK;
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
        return ret;
    }

    ret = uart_driver_install(UART_DEBUG, 1024, 1024, 0, NULL, 0);
    if (ret != ESP_OK) {
        ESP_LOGE("SerialCom", "uart_driver_install fallo: %s", esp_err_to_name(ret));
        return ret;
    }

    consolaIniciada = true;
    ESP_LOGI("SerialCom", "Consola iniciada");
    return ESP_OK;
}



#endif // UI_PORT == UI_PORT_ESP32S