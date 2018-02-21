/*
 * InchieKeyLED.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: owen
 */



#include "InchieKeyLED.h"

extern "C" {
#include "BlinkLed.h"
}

InchieKeyLED::InchieKeyLED(SLIPEncodedSerial &serial)
: slipSerial(serial)
{
    index = 254;
    keyState_1 = keyStateLast_1 = 0;
}

void InchieKeyLED::init (void){
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    // SETup LEDs
    // Enable GPIO Peripheral clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);


	// RGB LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	AUX_LED1_RED_OFF;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_OFF;

}

void InchieKeyLED::respond (const uint8_t *buf){

    uint8_t stat = buf[1];

	stat %= 8;

	if (stat == 0) {AUX_LED1_RED_OFF;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_OFF;}
	if (stat == 1) {AUX_LED1_RED_OFF;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_ON;}
	if (stat == 2) {AUX_LED1_RED_OFF;AUX_LED1_GREEN_ON;AUX_LED1_BLUE_OFF;}
	if (stat == 3) {AUX_LED1_RED_OFF;AUX_LED1_GREEN_ON;AUX_LED1_BLUE_ON;}
	if (stat == 4) {AUX_LED1_RED_ON;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_OFF;}
	if (stat == 5) {AUX_LED1_RED_ON;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_ON;}
	if (stat == 6) {AUX_LED1_RED_ON;AUX_LED1_GREEN_ON;AUX_LED1_BLUE_OFF;}
	if (stat == 7) {AUX_LED1_RED_ON;AUX_LED1_GREEN_ON;AUX_LED1_BLUE_ON;}

}

void InchieKeyLED::perform (void){

	uint8_t buf[3];

	buf[0] = 0;  // address of brain
	buf[1] = index;

    keyState_1 = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) ? 0 : 1;
    if (keyState_1 != keyStateLast_1){
        keyStateLast_1 = keyState_1;
        buf[2] = keyState_1;
        slipSerial.sendPacket(buf, 3);
    }

}


