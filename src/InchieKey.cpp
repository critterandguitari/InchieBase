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

InchieKey::InchieKey(SimpleWriter &buf, SLIPEncodedSerial &up, SLIPEncodedSerial &down)
: oscBuf(buf), upstream(up), downstream(down)
{
	index = 0;
	keyState = 0;
	keyStateLast = 0;
}

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

void InchieKey::perform (void){

	keyState = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) ? 0 : 1;


	if (keyState != keyStateLast){
		keyStateLast = keyState;

	    sprintf(address, "/%s/%d", type, index);
	    OSCMessage msgOut(address);
		msgOut.add(keyState);
	    msgOut.send(oscBuf);
		upstream.sendPacket(oscBuf.buffer, oscBuf.length);

		if (keyState) LEDON;
		else LEDOFF;
	}
}




