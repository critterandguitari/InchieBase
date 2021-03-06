/*
 * Inchie4KeyLED.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: owen
 */



#include "Inchie4KeyLED.h"

extern "C" {
#include "BlinkLed.h"
}

Inchie4KeyLED::Inchie4KeyLED(SLIPEncodedSerial &serial)
: slipSerial(serial)
{
    index = 254;
    keyState_1 = keyStateLast_1 = keyState_2 = keyStateLast_2 = keyState_3 = keyStateLast_3 = keyState_4 = keyStateLast_4 = 0;
}

void Inchie4KeyLED::init (void){
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0 |GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    // SETup LEDs
    // Enable GPIO Peripheral clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);


	// RGB LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	AUX_LED1_RED_OFF;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_OFF;
	AUX_LED2_RED_OFF;AUX_LED2_GREEN_OFF;AUX_LED2_BLUE_OFF;
	AUX_LED3_RED_OFF;AUX_LED3_GREEN_OFF;AUX_LED3_BLUE_OFF;
	AUX_LED4_RED_OFF;AUX_LED4_GREEN_OFF;AUX_LED4_BLUE_OFF;

}

void Inchie4KeyLED::respond (const uint8_t *buf){

    uint8_t led = buf[1];
    uint8_t stat = buf[2];

	stat %= 8;
	if (led == 1) {
		if (stat == 0) {AUX_LED1_RED_OFF;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_OFF;}
		if (stat == 1) {AUX_LED1_RED_OFF;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_ON;}
		if (stat == 2) {AUX_LED1_RED_OFF;AUX_LED1_GREEN_ON;AUX_LED1_BLUE_OFF;}
		if (stat == 3) {AUX_LED1_RED_OFF;AUX_LED1_GREEN_ON;AUX_LED1_BLUE_ON;}
		if (stat == 4) {AUX_LED1_RED_ON;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_OFF;}
		if (stat == 5) {AUX_LED1_RED_ON;AUX_LED1_GREEN_OFF;AUX_LED1_BLUE_ON;}
		if (stat == 6) {AUX_LED1_RED_ON;AUX_LED1_GREEN_ON;AUX_LED1_BLUE_OFF;}
		if (stat == 7) {AUX_LED1_RED_ON;AUX_LED1_GREEN_ON;AUX_LED1_BLUE_ON;}
	}
	if (led == 2) {
		if (stat == 0) {AUX_LED2_RED_OFF;AUX_LED2_GREEN_OFF;AUX_LED2_BLUE_OFF;}
		if (stat == 1) {AUX_LED2_RED_OFF;AUX_LED2_GREEN_OFF;AUX_LED2_BLUE_ON;}
		if (stat == 2) {AUX_LED2_RED_OFF;AUX_LED2_GREEN_ON;AUX_LED2_BLUE_OFF;}
		if (stat == 3) {AUX_LED2_RED_OFF;AUX_LED2_GREEN_ON;AUX_LED2_BLUE_ON;}
		if (stat == 4) {AUX_LED2_RED_ON;AUX_LED2_GREEN_OFF;AUX_LED2_BLUE_OFF;}
		if (stat == 5) {AUX_LED2_RED_ON;AUX_LED2_GREEN_OFF;AUX_LED2_BLUE_ON;}
		if (stat == 6) {AUX_LED2_RED_ON;AUX_LED2_GREEN_ON;AUX_LED2_BLUE_OFF;}
		if (stat == 7) {AUX_LED2_RED_ON;AUX_LED2_GREEN_ON;AUX_LED2_BLUE_ON;}
	}
	if (led == 3) {
		if (stat == 0) {AUX_LED3_RED_OFF;AUX_LED3_GREEN_OFF;AUX_LED3_BLUE_OFF;}
		if (stat == 1) {AUX_LED3_RED_OFF;AUX_LED3_GREEN_OFF;AUX_LED3_BLUE_ON;}
		if (stat == 2) {AUX_LED3_RED_OFF;AUX_LED3_GREEN_ON;AUX_LED3_BLUE_OFF;}
		if (stat == 3) {AUX_LED3_RED_OFF;AUX_LED3_GREEN_ON;AUX_LED3_BLUE_ON;}
		if (stat == 4) {AUX_LED3_RED_ON;AUX_LED3_GREEN_OFF;AUX_LED3_BLUE_OFF;}
		if (stat == 5) {AUX_LED3_RED_ON;AUX_LED3_GREEN_OFF;AUX_LED3_BLUE_ON;}
		if (stat == 6) {AUX_LED3_RED_ON;AUX_LED3_GREEN_ON;AUX_LED3_BLUE_OFF;}
		if (stat == 7) {AUX_LED3_RED_ON;AUX_LED3_GREEN_ON;AUX_LED3_BLUE_ON;}
	}
	if (led == 4) {
		if (stat == 0) {AUX_LED4_RED_OFF;AUX_LED4_GREEN_OFF;AUX_LED4_BLUE_OFF;}
		if (stat == 1) {AUX_LED4_RED_OFF;AUX_LED4_GREEN_OFF;AUX_LED4_BLUE_ON;}
		if (stat == 2) {AUX_LED4_RED_OFF;AUX_LED4_GREEN_ON;AUX_LED4_BLUE_OFF;}
		if (stat == 3) {AUX_LED4_RED_OFF;AUX_LED4_GREEN_ON;AUX_LED4_BLUE_ON;}
		if (stat == 4) {AUX_LED4_RED_ON;AUX_LED4_GREEN_OFF;AUX_LED4_BLUE_OFF;}
		if (stat == 5) {AUX_LED4_RED_ON;AUX_LED4_GREEN_OFF;AUX_LED4_BLUE_ON;}
		if (stat == 6) {AUX_LED4_RED_ON;AUX_LED4_GREEN_ON;AUX_LED4_BLUE_OFF;}
		if (stat == 7) {AUX_LED4_RED_ON;AUX_LED4_GREEN_ON;AUX_LED4_BLUE_ON;}
	}

}

void Inchie4KeyLED::perform (void){

	uint8_t buf[4];

	buf[0] = 0;  // address of brain
	buf[1] = index;

    keyState_1 = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) ? 0 : 1;
    if (keyState_1 != keyStateLast_1){
        keyStateLast_1 = keyState_1;
        buf[2] = 1;
        buf[3] = keyState_1;
        slipSerial.sendPacket(buf, 4);
    }

    keyState_2 = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) ? 0 : 1;
    if (keyState_2 != keyStateLast_2){
        keyStateLast_2 = keyState_2;
        buf[2] = 2;
        buf[3] = keyState_2;
        slipSerial.sendPacket(buf, 4);
    }

    keyState_3 = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) ? 0 : 1;
    if (keyState_3 != keyStateLast_3){
        keyStateLast_3 = keyState_3;
        buf[2] = 3;
        buf[3] = keyState_3;
        slipSerial.sendPacket(buf, 4);
    }

    keyState_4 = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) ? 0 : 1;
    if (keyState_4 != keyStateLast_4){
        keyStateLast_4 = keyState_4;
        buf[2] = 4;
        buf[3] = keyState_4;
        slipSerial.sendPacket(buf, 4);
    }
}


