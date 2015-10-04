/*
 * InchieLED.h
 *
 *  Created on: Oct 2, 2015
 *      Author: owen
 */

#ifndef INCHIELED_H_
#define INCHIELED_H_


#include <stdint.h>
#include "Inchie.h"
//#include "OSC/OSCMessage.h"

#include "stm32f0xx.h"

#define AUX_LED_BLUE_ON GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED_RED_ON GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED_GREEN_ON GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define AUX_LED_BLUE_OFF GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED_RED_OFF GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED_GREEN_OFF GPIO_SetBits(GPIOA, GPIO_Pin_7)

class InchieLED  {

private:

public:
	InchieLED(SimpleWriter &buf, SLIPEncodedSerial &up, SLIPEncodedSerial &down);
	~InchieLED() {};

	// for communication
	SimpleWriter &oscBuf;
	SLIPEncodedSerial &upstream;
	SLIPEncodedSerial &downstream;

	// for address
	char const * type = "led";
	int index = 0;
	char address[16];

	// every inchie must have these three fucntions
	void init (void);
	void respond (OSCMessage &msg);
	void perform (void);

	// specific for this inchie

};


#endif /* INCHIELED_H_ */
