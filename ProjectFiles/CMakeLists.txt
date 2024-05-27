add_executable(uart_comms
        main.c
)

pico_enable_stdio_usb(uart_comms 1)  # Enable usb for serial I/O
pico_enable_stdio_uart(uart_comms 0) # Disable uart for serial I/O

target_link_libraries(uart_comms pico_stdlib freertos)

pico_add_extra_outputs(uart_comms)