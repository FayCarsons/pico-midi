#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"

#define UART_ID uart0
#define BAUD_RATE 31250

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define TRIG1 2
#define TRIG2 3
#define TRIG3 4
#define TRIG4 5
#define TRIG5 6
#define TRIG6 7
#define TRIG7 8
#define TRIG8 9

#define TRIG_LEN 10

const unsigned int TRIG_PINS[8] = {TRIG1, TRIG2, TRIG3, TRIG4, TRIG5, TRIG6, TRIG7, TRIG8};

volatile int chars_rx = 0;

void do_trig(unsigned int pin) {
    gpio_put(TRIG_PINS[pin], 1);
    sleep_ms(TRIG_LEN);
    gpio_put(TRIG_PINS[pin], 0);
}

void uart_rx_callback() 
{
    uint8_t msg = 0;
    while (uart_is_readable(UART_ID) && chars_rx <= 3) 
    {
        msg += uart_getc(UART_ID) - 60;
        chars_rx++;
    }
    do_trig(c);
    if (uart_is_writable(UART_ID) && chars_rx >= 0) 
    {
        uart_putc(UART_ID, msg);
        chars_rx--;
    }
}

int main() 
{
    uart_init(UART_ID, BAUD_RATE);
    
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    for (int pin : TRIG_PINS) 
    {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }

    int __unused_actual = uart_set_baudrate(UART_ID, BAUD_RATE);

    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, false);

    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    irq_set_exclusive_handler(UART_IRQ, uart_rx_callback);
    irq_set_enabled(UART_IRQ, true);

    uart_set_irq_enables(UART_ID, true, false);

    while (1)
    {
        tight_loop_contents();
    }

}