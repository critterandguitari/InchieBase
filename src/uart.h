/*
 * uart.h
 *
 *  Created on: May 23, 2014
 *      Author: owen
 */

#ifndef UART_H_
#define UART_H_

#define UART_BUFFER_SIZE 256

#include "stm32f0xx.h"

// each uart has a tx and rx buffer, and a function to enable tx interrupt
typedef struct {
    uint8_t  rx_buf[UART_BUFFER_SIZE];
    uint16_t  rx_buf_head;
    uint16_t  rx_buf_tail;

    uint8_t  tx_buf[UART_BUFFER_SIZE];
    uint16_t  tx_buf_head;
    uint16_t  tx_buf_tail;

    void (*tx_it_en) (void);

} hardware_uart;


void uart_init(void);

void uart1_tx_it_en(void);
void uart2_tx_it_en(void);


#endif /* UART_H_ */
