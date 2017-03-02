/* https://eewiki.net/display/microcontroller/Software+FIFO+Buffer+for+UART+Communication */

#include <stdint.h>
#include "sw_fifo.h"
#include "usart.h"

typedef struct {
  uint8_t data_buf[FIFO_BUFFER_SIZE]; // FIFO buffer
  uint8_t i_first;                    // index of oldest data byte in buffer
  uint8_t i_last;                     // index of newest data byte in buffer
  uint8_t num_bytes;                  // number of bytes currently in buffer
}sw_fifo_typedef;
 
sw_fifo_typedef rx_fifo = { {0}, 0, 0, 0 }; // declare a receive software buffer
sw_fifo_typedef tx_fifo = { {0}, 0, 0, 0 }; // declare a transmit software buffer
 
void FIFO_receive_handler() {
  /* RECEIVE INTERRUPT */

  /***************************************************************************************************************/
  // UART receive interrupt sub-routine
  //  - interrupts when valid data exists in rx hardware buffer
  //  - checks if there's room in the rx software buffer
  //  - if there's room, it transfers the received data into the sw buffer
  //  - automatically handles "uart_rx_buffer_full_flag"
  //  - sets overflow flag upon software buffer overflow (doesn't overwrite existing data)

  if(rx_fifo.num_bytes == FIFO_BUFFER_SIZE) {      // if the sw buffer is full
    uart_rx_fifo_ovf_flag = 1;                     // set the overflow flag
  }
  else if(rx_fifo.num_bytes < FIFO_BUFFER_SIZE) { // if there's room in the sw buffer
    rx_fifo.data_buf[rx_fifo.i_last] = USART1->RDR; // store the received data as the newest data element in the sw buffer
    rx_fifo.i_last++;                              // increment the index of the most recently added element
    rx_fifo.num_bytes++;                           // increment the bytes counter
  }

  if(rx_fifo.num_bytes == FIFO_BUFFER_SIZE) {      // if sw buffer just filled up
    uart_rx_fifo_full_flag = 1;                    // set the RX FIFO full flag
  }

  /* if end of message call function which reads it */
  if (rx_fifo.data_buf[rx_fifo.i_last - 1] == '\n')

  if(rx_fifo.i_last == FIFO_BUFFER_SIZE) {         // if the index has reached the end of the buffer,
    rx_fifo.i_last = 0;                            // roll over the index counter
  }

  uart_rx_fifo_not_empty_flag = 1;                 // set received-data flag
}

void FIFO_transmit_handler() {
  /* TRANSMIT INTERRUPT */

  /***************************************************************************************************************/
  // UART transmit interrupt sub-routine
  //  - interrupts when the tx hardware buffer is empty
  //  - checks if data exists in the tx software buffer
  //  - if data exists, it places the oldest element of the sw buffer into the tx hardware buffer
  //  - if the sw buffer is emptied, it disables the "hw buffer empty" interrupt
  //  - automatically handles "uart_tx_buffer_full_flag"

  if(tx_fifo.num_bytes == FIFO_BUFFER_SIZE) { // if the sw buffer is full
    uart_tx_fifo_full_flag = 0;               // clear the buffer full flag because we are about to make room
  }
  if(tx_fifo.num_bytes > 0) {                 // if data exists in the sw buffer

    USART1->TDR = tx_fifo.data_buf[tx_fifo.i_first]; // place oldest data element in the TX hardware buffer */

    tx_fifo.i_first++;                        // increment the index of the oldest element
    tx_fifo.num_bytes--;                      // decrement the bytes counter
  }
  if(tx_fifo.i_first == FIFO_BUFFER_SIZE) {   // if the index has reached the end of the buffer,
    tx_fifo.i_first = 0;                      // roll over the index counter
  }
  if(tx_fifo.num_bytes == 0) {                // if no more data exists
    uart_tx_fifo_not_empty_flag = 0;          // clear flag

    /* no more data to be send
     * disable transmit interrupt */
    CLEAR_BIT(USART1->CR1, USART_CR1_TXEIE);
  }
}
 
/***************************************************************************************************************/
// UART data transmit function
//  - checks if there's room in the transmit sw buffer
//  - if there's room, it transfers data byte to sw buffer
//  - automatically handles "uart_tx_buffer_full_flag"
//  - sets the overflow flag upon software buffer overflow (doesn't overwrite existing data)
//  - if this is the first data byte in the buffer, it enables the "hw buffer empty" interrupt
void FIFO_send_byte(uint8_t byte) {

  if(tx_fifo.num_bytes == FIFO_BUFFER_SIZE) {      // no room in the sw buffer
    uart_tx_fifo_ovf_flag = 1;                     // set the overflow flag
  }else if(tx_fifo.num_bytes < FIFO_BUFFER_SIZE) { // if there's room in the sw buffer
    tx_fifo.data_buf[tx_fifo.i_last] = byte;       // transfer data byte to sw buffer
    tx_fifo.i_last++;                              // increment the index of the most recently added element
    tx_fifo.num_bytes++;                           // increment the bytes counter
  }
  if(tx_fifo.num_bytes == FIFO_BUFFER_SIZE) {      // if sw buffer is full
    uart_tx_fifo_full_flag = 1;                    // set the TX FIFO full flag
  }
  if(tx_fifo.i_last == FIFO_BUFFER_SIZE) {         // if the "new data" index has reached the end of the buffer,
    tx_fifo.i_last = 0;                            // roll over the index counter
  }

  if(tx_fifo.num_bytes > 0) {                      // if there is data in the buffer
 
    uart_tx_fifo_not_empty_flag = 1;               // set flag
     
    /* to send data
     * enable buffer empty interrupt */
    SET_BIT(USART1->CR1, USART_CR1_TXEIE);
  }
}

/***************************************************************************************************************/
// UART data receive function
//  - checks if data exists in the receive sw buffer
//  - if data exists, it returns the oldest element contained in the buffer
//  - automatically handles "uart_rx_buffer_full_flag"
//  - if no data exists, it clears the uart_rx_flag
uint8_t FIFO_get_byte(void) {
  uint8_t byte = 0;
  if(rx_fifo.num_bytes == FIFO_BUFFER_SIZE) { // if the sw buffer is full
    uart_rx_fifo_full_flag = 0;               // clear the buffer full flag because we are about to make room
  }
  if(rx_fifo.num_bytes > 0) {                 // if data exists in the sw buffer
    byte = rx_fifo.data_buf[rx_fifo.i_first]; // grab the oldest element in the buffer
    rx_fifo.i_first++;                        // increment the index of the oldest element
    rx_fifo.num_bytes--;                      // decrement the bytes counter
  }else{                                      // RX sw buffer is empty
    uart_rx_fifo_not_empty_flag = 0;          // clear the rx flag
  }
  if(rx_fifo.i_first == FIFO_BUFFER_SIZE) {   // if the index has reached the end of the buffer,
    rx_fifo.i_first = 0;                      // roll over the index counter
  }

  return byte;                                // return the data byte
}
/***************************************************************************************************************/
