/*
 * Inchie4KeyLED.h
 *
 *  Created on: Jan 25, 2018
 *      Author: owen
 */

#ifndef INCHIE4KEYLED_H_
#define INCHIE4KEYLED_H_

#include <stdint.h>
#include <stdio.h>
#include "OSC/OSCMessage.h"
#include "SLIPEncodedSerial.h"
#include "OSC/SimpleWriter.h"

#include "stm32f0xx.h"

#define AUX_LED1_RED_ON    GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED1_GREEN_ON  GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define AUX_LED1_BLUE_ON   GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define AUX_LED1_RED_OFF   GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED1_GREEN_OFF GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define AUX_LED1_BLUE_OFF  GPIO_SetBits(GPIOA, GPIO_Pin_6)

#define AUX_LED2_RED_ON    GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define AUX_LED2_GREEN_ON  GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define AUX_LED2_BLUE_ON   GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define AUX_LED2_RED_OFF   GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define AUX_LED2_GREEN_OFF GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define AUX_LED2_BLUE_OFF  GPIO_SetBits(GPIOA, GPIO_Pin_8)

#define AUX_LED3_RED_ON    GPIO_ResetBits(GPIOA, GPIO_Pin_11)
#define AUX_LED3_GREEN_ON  GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define AUX_LED3_BLUE_ON   GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define AUX_LED3_RED_OFF   GPIO_SetBits(GPIOA, GPIO_Pin_11)
#define AUX_LED3_GREEN_OFF GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define AUX_LED3_BLUE_OFF  GPIO_SetBits(GPIOA, GPIO_Pin_15)

#define AUX_LED4_RED_ON    GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED4_GREEN_ON  GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define AUX_LED4_BLUE_ON   GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define AUX_LED4_RED_OFF   GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED4_GREEN_OFF GPIO_SetBits(GPIOB, GPIO_Pin_4)
#define AUX_LED4_BLUE_OFF  GPIO_SetBits(GPIOB, GPIO_Pin_5)



class Inchie4KeyLED {

private:

public:
    Inchie4KeyLED(SimpleWriter &buf, SLIPEncodedSerial &serial);
    ~Inchie4KeyLED() {};

    // for communication
    SimpleWriter &oscBuf;
    SLIPEncodedSerial &slipSerial;

    // for address
    char const * type = "4kled";
    int index;
    char address[16];

    // every inchie must have these three fucntions
    void init (void);
    void respond (OSCMessage &msg);
    void perform (void);

    // specific for this inchie
    uint8_t keyState_1;
    uint8_t keyStateLast_1;

    uint8_t keyState_2;
    uint8_t keyStateLast_2;

    uint8_t keyState_3;
    uint8_t keyStateLast_3;

    uint8_t keyState_4;
    uint8_t keyStateLast_4;

};




#endif /* INCHIE4KEYLED_H_ */
