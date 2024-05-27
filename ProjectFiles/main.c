#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h> // Include for serial I/O
#include "pico/stdlib.h"

enum LED_STATUS { OFF, ON };

void led_task(void *pvParameters){  
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    while (true) {
        gpio_put(LED_PIN, ON);
        vTaskDelay(100);
        gpio_put(LED_PIN, OFF);
        vTaskDelay(100);
    }
}

int main() {
    stdio_init_all(); // Include for serial I/O

    // Create & start the scheduler for both the led_task & usb_task programs
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(true){};
}
