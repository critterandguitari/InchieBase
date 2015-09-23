/*
 * uart.c
 *
 *  Created on: May 23, 2014
 *      Author: owen
 */


#include "uart.h"
#include "BlinkLed.h"


// the upstream is uart 1
// downstream is uart 2
hardware_uart uart_upstream;
hardware_uart uart_downstream;

void uart1_tx_it_en(void){
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE); // turn on tx interrupt
}

void uart2_tx_it_en(void){
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE); // turn on tx interrupt
}

void uart2_init(void){


    // zero things out
    uart_upstream.rx_buf_head = 0;
    uart_upstream.rx_buf_tail = 0;
    uart_upstream.tx_buf_head = 0;
    uart_upstream.tx_buf_tail = 0;
    uart_upstream.tx_it_en = uart1_tx_it_en;


    uart_downstream.rx_buf_head = 0;
    uart_downstream.rx_buf_tail = 0;
    uart_downstream.tx_buf_head = 0;
    uart_downstream.tx_buf_tail = 0;
    uart_downstream.tx_it_en = uart2_tx_it_en;

    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    // uart 2 init
/*    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

    //Configure USART2 pins:  Rx and Tx ----------------------------
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Configure USART2 setting:         ----------------------------
   // USART_InitStructure.USART_BaudRate = 500000;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    // setup irq
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt

    // Enable USART1 IRQ
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART2,ENABLE);*/

    // end uart 2 init


    // uart 1 init
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

     RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

     GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
     GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

     //Configure USART1 pins:  Rx and Tx ----------------------------
     GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
     GPIO_Init(GPIOA, &GPIO_InitStructure);

     //Configure USART1 setting:         ----------------------------
    // USART_InitStructure.USART_BaudRate = 500000;
     USART_InitStructure.USART_BaudRate = 115200;
     USART_InitStructure.USART_WordLength = USART_WordLength_8b;
     USART_InitStructure.USART_StopBits = USART_StopBits_1;
     USART_InitStructure.USART_Parity = USART_Parity_No;
     USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
     USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
     USART_Init(USART1, &USART_InitStructure);

     // setup irq
     USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt
     USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

     // Enable USART1 IRQ
     NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);

     USART_Cmd(USART1,ENABLE);

     //end uart 1 init

}

void uart2_send(uint8_t c){
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // Wait for Empty

    USART_SendData(USART1, c); // Send 'I'
 /*
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty

    USART_SendData(USART2, c); // Send 'I'
    */
}

void USART2_IRQHandler(void) {
   /* if( USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
        //blink_led_on();
        //char t = USART1->DR; // the character from the USART1 data register is saved in t
        uart2_recv_buf[uart2_recv_buf_head] = USART_ReceiveData(USART2);


        uart2_recv_buf_head++;
        uart2_recv_buf_head %= UART2_BUFFER_SIZE;  //
        //blink_led_off();
    }*/
}

void USART1_IRQHandler(void) {
    if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
        uart_upstream.rx_buf[uart_upstream.rx_buf_head] = USART_ReceiveData(USART1);
        uart_upstream.rx_buf_head++;
        uart_upstream.rx_buf_head %= UART2_BUFFER_SIZE;  //
    }

    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
        uint8_t tx;

        if (uart_upstream.tx_buf_head != uart_upstream.tx_buf_tail){
            tx = uart_upstream.tx_buf[uart_upstream.tx_buf_tail++];
            uart_upstream.tx_buf_tail %= UART2_BUFFER_SIZE;
            USART_SendData(USART1, (uint16_t)tx); // Transmit the character
        }
        else {
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE); // Suppress interrupt when nothing to send
        }
      /*if (fifo_read(TxFifo, &tx, 1) == 1) // Anything to send?
        USART_SendData(USART1, (uint16_t)tx); // Transmit the character
      else
        USART_ITConfig(USART1, USART_IT_TXE, DISABLE); // Suppress interrupt when empty*/
    }
}
