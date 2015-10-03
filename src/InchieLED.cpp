/*
 * InchieLED.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: owen
 */

#include "InchieLED.h"

#define AUX_LED_BLUE_ON GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED_RED_ON GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED_GREEN_ON GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define AUX_LED_BLUE_OFF GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED_RED_OFF GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED_GREEN_OFF GPIO_SetBits(GPIOA, GPIO_Pin_7)

//InchieLED::~InchieLED(void) {};

void InchieLED::init (void){
    GPIO_InitTypeDef GPIO_InitStructure;

  // Enable GPIO Peripheral clock
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);


  // RGB LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOB, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

	AUX_LED_BLUE_ON;AUX_LED_RED_OFF;AUX_LED_GREEN_ON;
}

void InchieLED::respond (OSCMessage &msg){

	int stat;

	// digitalWrite(ledPin, LOW);
	if (msg.isInt(0)) {
		stat = msg.getInt(0);

		stat %= 8;

		if (stat == 0) {
		AUX_LED_RED_OFF;
		AUX_LED_GREEN_OFF;
		AUX_LED_BLUE_OFF;
		}
		if (stat == 1) {
		AUX_LED_RED_OFF;
		AUX_LED_GREEN_OFF;
		AUX_LED_BLUE_ON;
		}
		if (stat == 2) {
		AUX_LED_RED_OFF;
		AUX_LED_GREEN_ON;
		AUX_LED_BLUE_OFF;
		}
		if (stat == 3) {
		AUX_LED_RED_OFF;
		AUX_LED_GREEN_ON;
		AUX_LED_BLUE_ON;
		}
		if (stat == 4) {
		AUX_LED_RED_ON;
		AUX_LED_GREEN_OFF;
		AUX_LED_BLUE_OFF;
		}
		if (stat == 5) {
		AUX_LED_RED_ON;
		AUX_LED_GREEN_OFF;
		AUX_LED_BLUE_ON;
		}
		if (stat == 6) {
		AUX_LED_RED_ON;
		AUX_LED_GREEN_ON;
		AUX_LED_BLUE_OFF;
		}
		if (stat == 7) {
		AUX_LED_RED_ON;
		AUX_LED_GREEN_ON;
		AUX_LED_BLUE_ON;
		}
	}
}

bool InchieLED::perform (OSCMessage &msg){

}



