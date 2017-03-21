/* communication between raspberry and STM */

#include <stdint.h>
#include "sw_fifo.h"
#include "rpi_communication.h"
#include "tim.h"

volatile uint8_t uart_rx_fifo_not_empty_flag; // this flag is automatically set and cleared by the software buffer
volatile uint8_t uart_rx_fifo_full_flag;      // this flag is automatically set and cleared by the software buffer
volatile uint8_t uart_rx_fifo_ovf_flag;       // this flag is not automatically cleared by the software buffer
volatile uint8_t uart_tx_fifo_full_flag;      // this flag is automatically set and cleared by the software buffer
volatile uint8_t uart_tx_fifo_ovf_flag;       // this flag is not automatically cleared by the software buffer
volatile uint8_t uart_tx_fifo_not_empty_flag; // this flag is automatically set and cleared by the software buffer

void read_receive_buffer(uint8_t size) {
  uint8_t data[size];

  for(uint8_t i = 0; uart_rx_fifo_not_empty_flag; i++) data[i] = FIFO_get_byte();

  // choose action according to the command
  switch (data[0]) {
    case 0x10:
      /* set all motors */
      TIM3->CCR1 = data[1] << 8;
      TIM3->CCR2 = data[2] << 8;
      TIM3->CCR3 = data[3] << 8;
      TIM3->CCR4 = data[4] << 8;
      break;
    case 0x30:
      /* read battery voltage */
      break;
    case 0x84:
      /* set servo position */
      break;
    default:
      break;
  }
}
