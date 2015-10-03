/*
 * InchieKey.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: owen
 */

#include "InchieKey.h"

extern "C" {
#include "BlinkLed.h"
}

//InchieKey::~InchieKey(void) {};

void InchieKey::init (void){
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Periph clocks enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


	  /* Configure Buttons pin as input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void InchieKey::respond (OSCMessage &msg){

}

bool InchieKey::perform (OSCMessage &msg){


	state = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) ? 0 : 1;
	if (state) LEDON;
	else LEDOFF;
	return false;
	/*if (state != stateLast){
		stateLast = state;
		msg.add(state);
		if (state) LEDON;
		else LEDOFF;
		return true;
	} else {
		return false;
	}*/
}




