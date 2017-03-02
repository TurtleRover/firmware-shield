////////////////////////////////////////////////////////////////////////////////////////
/* enter necessary header files for proper interrupt vector and UART/USART visibility */
////////////////////////////////////////////////////////////////////////////////////////
 
#include <sw_fifo.h>
 
typedef struct {
  uint8_t  data_buf[FIFO_BUFFER_SIZE]; // FIFO buffer
  uint16_t i_first;                    // index of oldest data byte in buffer
  uint16_t i_last;                     // index of newest data byte in buffer
  uint16_t num_bytes;                  // number of bytes currently in buffer
}sw_fifo_typedef;
 
sw_fifo_typedef rx_fifo = { {0}, 0, 0, 0 }; // declare a receive software buffer
sw_fifo_typedef tx_fifo = { {0}, 0, 0, 0 }; // declare a transmit software buffer
 
 
/***************************************************************************************************************/
// UART receive interrupt sub-routine
//  - interrupts when valid data exists in rx hardware buffer
//  - checks if there's room in the rx software buffer
//  - if there's room, it transfers the received data into the sw buffer
//  - automatically handles "uart_rx_buffer_full_flag"
//  - sets overflow flag upon software buffer overflow (doesn't overwrite existing data)
//////////////////////////////////////////////
/* enter name of UART RX IRQ Handler here */ {
//////////////////////////////////////////////
   
  /* Explicitly clear the source of interrupt if necessary */
   
  if(rx_fifo.num_bytes == FIFO_BUFFER_SIZE) {      // if the sw buffer is full
    uart_rx_fifo_ovf_flag = 1;                     // set the overflow flag
  }else if(rx_fifo.num_bytes < FIFO_BUFFER_SIZE) { // if there's room in the sw buffer
     
    ///////////////////////////////////////////////////
    /* read error/status reg here if desired         */
    /* handle any hardware RX errors here if desired */
    ///////////////////////////////////////////////////
     
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    rx_fifo.data_buf[rx_fifo.i_last] = /* enter pointer to UART rx hardware buffer here */ // store the received data as the newest data element in the sw buffer
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
    rx_fifo.i_last++;                              // increment the index of the most recently added element
    rx_fifo.num_bytes++;                           // increment the bytes counter
  }
  if(rx_fifo.num_bytes == FIFO_BUFFER_SIZE) {      // if sw buffer just filled up
    uart_rx_fifo_full_flag = 1;                    // set the RX FIFO full flag
  }
  if(rx_fifo.i_last == FIFO_BUFFER_SIZE) {         // if the index has reached the end of the buffer,
    rx_fifo.i_last = 0;                            // roll over the index counter
  }
  uart_rx_fifo_not_empty_flag = 1;                 // set received-data flag
} // end UART RX IRQ handler
/***************************************************************************************************************/
 
 
/***************************************************************************************************************/
// UART transmit interrupt sub-routine
//  - interrupts when the tx hardware buffer is empty
//  - checks if data exists in the tx software buffer
//  - if data exists, it places the oldest element of the sw buffer into the tx hardware buffer
//  - if the sw buffer is emptied, it disables the "hw buffer empty" interrupt
//  - automatically handles "uart_tx_buffer_full_flag"
//////////////////////////////////////////////
/* enter name of UART TX IRQ Handler here */ {
//////////////////////////////////////////////
   
  /* Explicitly clear the source of interrupt if necessary */
 
  if(tx_fifo.num_bytes == FIFO_BUFFER_SIZE) { // if the sw buffer is full
    uart_tx_fifo_full_flag = 0;               // clear the buffer full flag because we are about to make room
  }
  if(tx_fifo.num_bytes > 0) {                 // if data exists in the sw buffer
     
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* enter pointer to UART tx hardware buffer here */ = tx_fifo.data_buf[tx_fifo.i_first]; // place oldest data element in the TX hardware buffer
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
    tx_fifo.i_first++;                        // increment the index of the oldest element
    tx_fifo.num_bytes--;                      // decrement the bytes counter
  }
  if(tx_fifo.i_first == FIFO_BUFFER_SIZE) {   // if the index has reached the end of the buffer,
    tx_fifo.i_first = 0;                      // roll over the index counter
  }
  if(tx_fifo.num_bytes == 0) {                // if no more data exists
 
    uart_tx_fifo_not_empty_flag = 0;          // clear flag
 
    //////////////////////////////////////////////////////////////////////////
    /* disable UART "TX hw buffer empty" interrupt here                     */
    /* if using shared RX/TX hardware buffer, enable RX data interrupt here */
    //////////////////////////////////////////////////////////////////////////
     
  }
}// end UART TX IRQ handler
/***************************************************************************************************************/
 
 
/***************************************************************************************************************/
// UART data transmit function
//  - checks if there's room in the transmit sw buffer
//  - if there's room, it transfers data byte to sw buffer
//  - automatically handles "uart_tx_buffer_full_flag"
//  - sets the overflow flag upon software buffer overflow (doesn't overwrite existing data)
//  - if this is the first data byte in the buffer, it enables the "hw buffer empty" interrupt
void uart_send_byte(uint8_t byte) {
   
  ///////////////////////////////////////////////////////////
  /* disable interrupts while manipulating buffer pointers */
  ///////////////////////////////////////////////////////////
 
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
 
  ///////////////////////
  /* enable interrupts */
  ///////////////////////
 
  if(tx_fifo.num_bytes > 0) {                      // if there is data in the buffer
 
    uart_tx_fifo_not_empty_flag = 1;               // set flag
     
    ///////////////////////////////////////////////////////////////////////////
    /* if using shared RX/TX hardware buffer, disable RX data interrupt here */
    /* enable UART "TX hw buffer empty" interrupt here                       */
    ///////////////////////////////////////////////////////////////////////////
     
  }
}