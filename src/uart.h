/*
 * uart.h
 *
 *  Created on: May 23, 2014
 *      Author: owen
 */

#ifndef UART_H_
#define UART_H_

#define UART2_BUFFER_SIZE 256

#include "stm32f0xx.h"

typedef struct {
    uint8_t  rx_buf[UART2_BUFFER_SIZE];
    uint16_t  rx_buf_head;
    uint16_t  rx_buf_tail;

    uint8_t  tx_buf[UART2_BUFFER_SIZE];
    uint16_t  tx_buf_head;
    uint16_t  tx_buf_tail;

} hardware_uart;


void uart2_init(void);
void uart2_send(uint8_t c);
int uart2_available(void);
int uart2_peek(void);
int uart2_read(void);

void uart_tx_it_en(void);


#endif /* UART_H_ */
