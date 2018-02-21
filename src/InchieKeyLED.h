/*
 * InchieKeyLED.h
 *
 *  Created on: Oct 2, 2015
 *      Author: owen
 */

#ifndef InchieKeyLED_H_
#define InchieKeyLED_H_


#include <stdint.h>
#include <stdio.h>
#include "SLIPEncodedSerial.h"

#include "stm32f0xx.h"

#define AUX_LED1_RED_ON    GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED1_GREEN_ON  GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define AUX_LED1_BLUE_ON   GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define AUX_LED1_RED_OFF   GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED1_GREEN_OFF GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define AUX_LED1_BLUE_OFF  GPIO_SetBits(GPIOA, GPIO_Pin_6)

class InchieKeyLED {

private:

public:
    InchieKeyLED(SLIPEncodedSerial &serial);
    ~InchieKeyLED() {};

    // for communication
    SLIPEncodedSerial &slipSerial;

    // for address
    char const * type = "kled";
    uint8_t index;
    char address[16];

    // every inchie must have these three fucntions
    void init (void);
    void respond (const uint8_t *buf);
    void perform (void);

    // specific for this inchie
    uint8_t keyState_1;
    uint8_t keyStateLast_1;

};


#endif /* InchieKeyLED_H_ */
