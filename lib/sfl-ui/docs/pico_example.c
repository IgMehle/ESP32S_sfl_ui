#include <stdio.h>
#include "pico/stdlib.h"

// Headers de FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

// Headers de SFL-UI
#include "sfl-ui/userInterface.h"

/*----------------------------------------------------------
 * LED DE RUN
 *----------------------------------------------------------*/
#define LED_PIN 25
volatile uint32_t led_value = 0;
static TimerHandle_t tmr_led;
static void led_run_toggle(TimerHandle_t tmr_led)
{
    led_value ^= 0x1;
    gpio_put(LED_PIN, led_value);
    //printf("tick\n");
}
/*----------------------------------------------------------*/

static void update_menu_task(void *pvParameters) 
{
    while (1) {
        userInterfaceUpdate();
        vTaskDelay(pdMS_TO_TICKS(50)); // Ajusta el tiempo de espera según sea necesario
    }
}

int main()
{
    userInterfaceInit();

    // Configuro el pin del LED como salida
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // creo timer periodico
    tmr_led = xTimerCreate(
        "TMR_LED",
        pdMS_TO_TICKS(250),
        pdTRUE,
        NULL,
        led_run_toggle);
    
    // start timer
    xTimerStart(tmr_led, 0);
    
    xTaskCreate(update_menu_task, "updateMenuTask", 512, NULL, 1, NULL);
    vTaskStartScheduler();
    while (true);
}
