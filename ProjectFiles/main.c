#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h> // Include for serial I/O
#include <queue.h> // Include to manipulate task queues
#include "pico/stdlib.h"

enum LED_STATUS { OFF, ON };

static QueueHandle_t xQueue = NULL; // Declare & initialize queue structure for tasks

void led_task(void *pvParameters){  
    uint current_status = OFF;
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    while (true) {
        current_status = ON;
        gpio_put(LED_PIN, ON);
        xQueueSend(xQueue, &current_status, 0U); // Send current LED status (ON or OFF).
                                                 // 0U represents the 'ticks' to wait, and we sent zero 
                                                 // as the queue should always be empty.
        vTaskDelay(100);

        current_status = OFF;
        gpio_put(LED_PIN, OFF);
        xQueueSend(xQueue, &current_status, 0U); // Send current LED status (ON or OFF)


        vTaskDelay(100);
    }
}

void usb_task(void *pvParameters) {
    uint received_status;

    while(true) {
        /*
         * xQueueReceive() grabs the data from the queue.
         * Format: xQueueReceive(QueueHandle_t xQueue, void *const pvBuffer, TickType_t xTicksToWait)
         *
         * portMAX_DELAY 
         * This means that the queue will wait the max amount of time for the status data.
         */
        xQueueReceive(xQueue, &received_status, portMAX_DELAY);

        if (received_status == ON) {
            printf("The LED is ON\n");
        }
        else if (received_status == OFF) {
            printf("The LED is OFF\n");
        }
        else {
            printf("ERROR: Invalid LED status\n");
        }
    }

}

int main() {
    stdio_init_all(); // Include for serial I/O

    /* 
     * Format: xQueueCreate(uxQueueLength, uxItemSize)
     *
     * uxQueueLength
     * We have length set to 1 since whenever led_task writes to the queue it will immediately
     * be read & taken out of the queue by usb_task. So, we should never need it longer than for 
     * one piece of data. 
     * 
     * uxItemSize
     * We're communicating with unsigned integers, so we use `sizeof(uint)`.
     */
    xQueue = xQueueCreate(1, sizeof(uint));

    // Create & start the scheduler for both the led_task & usb_task programs
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(usb_task, "USB_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(true){};
}
