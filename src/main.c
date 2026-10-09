#include <sfl_ui_esp32.h>

/*----------------------------------------------------------
 * LED DE RUN
 *----------------------------------------------------------*/
#include "freertos/timers.h"
#include "driver/gpio.h"
#define LED_PIN 2
volatile uint32_t led_value = 0;
static TimerHandle_t tmr_led;
static void led_run_toggle(TimerHandle_t tmr_led)
{
    led_value ^= 0x1;
    gpio_set_level(LED_PIN, led_value);
}

static void update_menu_task(void *pvParameters) {
    while (1) {
        userInterfaceUpdate();
        vTaskDelay(pdMS_TO_TICKS(50)); // Ajusta el tiempo de espera según sea necesario
    }
}
/*----------------------------------------------------------*/

void app_main(void) 
{
    userInterfaceInit();
    xTaskCreate(update_menu_task, "updateMenuTask", 4096, NULL, 5, NULL);

    /*----------------------------------------------------------*/
    // led run xtimer
    gpio_config_t out_config = {};
    // creo config basica de output
    out_config.mode = GPIO_MODE_OUTPUT;
    out_config.intr_type = GPIO_INTR_DISABLE;
    out_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    out_config.pull_up_en = GPIO_PULLUP_DISABLE;
    // mapeo mascara con pines de salida
    out_config.pin_bit_mask = (1ULL << LED_PIN);
    // configuro salidas
    gpio_config(&out_config);
    // creo timer periodico
    tmr_led = xTimerCreate(
        "TMR_LED",
        pdMS_TO_TICKS(500),
        pdTRUE,
        NULL,
        led_run_toggle);
    // start timer
    xTimerStart(tmr_led, 0);
    /*----------------------------------------------------------*/
}