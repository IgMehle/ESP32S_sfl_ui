#include <sfl_ui_esp32.h>

static void update_menu_task(void *pvParameters) {
    while (1) {
        userInterfaceUpdate();
        vTaskDelay(pdMS_TO_TICKS(50)); // Ajusta el tiempo de espera según sea necesario
    }
}

void app_main(void) 
{
    userInterfaceInit();
    xTaskCreate(update_menu_task, "updateMenuTask", 4096, NULL, 5, NULL);
}