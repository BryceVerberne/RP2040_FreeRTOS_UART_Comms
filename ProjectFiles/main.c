#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h> 
#include <queue.h>
#include "pico/stdlib.h"

static QueueHandle_t xQueue = NULL;

/*
 * message_send
 * This task sends a message through a queue to message_transmit to transmit "hello" on the hardline 
 * every 5 seconds
 */
void message_send(void *pvParameters){  
    char message[] = "hello";
    
    while (true) {
        xQueueSend(xQueue, &message, 0U); // Send "hello" message
        vTaskDelay(500);                  // Block task for 5 seconds before sending message again
    }
}

/*
 * message_transmit
 * This task sits waiting for messages from message_send, and when it recieves one, transmits "hello" 
 * out of its UART.
 */
void message_transmit(void *pvParameters) {
    char received_message[] = "";

    while(true) {
        xQueueReceive(xQueue, &received_message, portMAX_DELAY); // Wait to receive a string message
        printf("%s\n", received_message);                        // Print message when received
    }
}

int main() {
    stdio_init_all();

    xQueue = xQueueCreate(5, sizeof(char) * 6); // Prepare the queue to hold the size of "hello"

    // Create & start the scheduler for both tasks
    xTaskCreate(message_send, "Message Send", 256, NULL, 1, NULL);
    xTaskCreate(message_transmit, "Message Transmit", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(true){};
}
