# FreeRTOS UART Communication on Raspberry Pi Pico

## Project Description

This project, developed for the Sun Devil Satellite Laboratory (SDSL) as a practice exercise, demonstrates a simple FreeRTOS-based program on the Raspberry Pi Pico (RP2040) with the following tasks:

1. **Message Sender Task:** Sends a "hello" message through a queue every 5 seconds.
2. **Message Receiver Task:** Waits for messages from the sender task and transmits the received "hello" message via UART.

## How to Run

1. Build and flash the program to your Raspberry Pi Pico.
2. Open a serial monitor to observe the UART output.

If the project runs successfully, you will see "hello" transmitted via UART every 5 seconds.
