/* communication between raspberry and STM */

#include <stdint.h>

volatile uint8_t uart_rx_fifo_not_empty_flag; // this flag is automatically set and cleared by the software buffer
volatile uint8_t uart_rx_fifo_full_flag;      // this flag is automatically set and cleared by the software buffer
volatile uint8_t uart_rx_fifo_ovf_flag;       // this flag is not automatically cleared by the software buffer
volatile uint8_t uart_tx_fifo_full_flag;      // this flag is automatically set and cleared by the software buffer
volatile uint8_t uart_tx_fifo_ovf_flag;       // this flag is not automatically cleared by the software buffer
volatile uint8_t uart_tx_fifo_not_empty_flag; // this flag is automatically set and cleared by the software buffer
