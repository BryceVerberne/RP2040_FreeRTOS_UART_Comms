/**
 * File:   main.c
 * Title:  FreeRTOS UART Comms on RPi Pico
 * Author: Bryce Verberne
 * Email:  bverbern@asu.edu
 * Date:   26-May-2024
 * 
 * Description: 
 * This program is designed for the Raspberry Pi Pico using the Pico SDK and 
 * FreeRTOS. It consists of two main tasks:
 * 
 * 1. The first task sends a message through a queue every 5 seconds. The 
 *    message contains the string "hello".
 * 2. The second task waits for messages from the first task. Upon receiving a 
 *    message, it transmits the string "hello" out of its UART.
 * 
 * This setup demonstrates basic inter-task communication using queues in 
 * FreeRTOS and provides a foundation for more complex RTOS-based applications 
 * on the Raspberry Pi Pico.
 * 
 * Revised: 26-May-2024 - Enable sending of message between tasks & transmission
 * 
 */



#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h> 
#include <queue.h>
#include "pico/stdlib.h"

static QueueHandle_t xQueue = NULL;

/**
 * message_send
 * This task sends a message through a queue to message_transmit to transmit "hello" on the hardline 
 * every 5 seconds
 */
void message_send(void *pvParameters){  
    char message[] = "hello";
    
    // Send "hello" message every 5 seconds to message_transmit task
    while (true) {
        xQueueSend(xQueue, &message, 0U);
        vTaskDelay(500);
    }
}

/**
 * message_transmit
 * This task sits waiting for messages from message_send, and when it recieves one, transmits "hello" 
 * out of its UART.
 */
void message_transmit(void *pvParameters) {
    char received_message[] = "";

    // Wait to receive a message & print when received
    while(true) {
        xQueueReceive(xQueue, &received_message, portMAX_DELAY);
        printf("%s\n", received_message);
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
