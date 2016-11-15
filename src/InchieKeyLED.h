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
#include "OSC/OSCMessage.h"
#include "SLIPEncodedSerial.h"
#include "OSC/SimpleWriter.h"

#include "stm32f0xx.h"

#define AUX_LED_BLUE_ON GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED_RED_ON GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED_GREEN_ON GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define AUX_LED_BLUE_OFF GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED_RED_OFF GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED_GREEN_OFF GPIO_SetBits(GPIOA, GPIO_Pin_7)


class InchieKeyLED {

private:

public:
    InchieKeyLED(SimpleWriter &buf, SLIPEncodedSerial &serial);
    ~InchieKeyLED() {};

    // for communication
    SimpleWriter &oscBuf;
    SLIPEncodedSerial &slipSerial;

    // for address
    char const * type = "kled";
    int index = 0;
    char address[16];

    // every inchie must have these three fucntions
    void init (void);
    void respond (OSCMessage &msg);
    void perform (void);

    // specific for this inchie
    uint8_t keyState = 0;
    uint8_t keyStateLast = 0;

};


#endif /* InchieKeyLED_H_ */
