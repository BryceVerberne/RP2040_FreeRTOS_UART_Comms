# RP2040 FreeRTOS UART Communication

## Project Description
This program is designed for the Raspberry Pi Pico using the Pico SDK and FreeRTOS. It consists of two main tasks:

1. The first task sends a message through a queue every 5 seconds. The message contains the string "hello".
2. The second task waits for messages from the first task. Upon receiving a message, it transmits the string "hello" out of its UART.

This setup demonstrates basic inter-task communication using queues in FreeRTOS and provides a foundation for more complex RTOS-based applications on the Raspberry Pi Pico.

## How to Run
1. Build and flash the program to your Raspberry Pi Pico.
2. Open a serial monitor to observe the UART output.

If the project runs successfully, you will see "hello" transmitted via UART every 5 seconds.
