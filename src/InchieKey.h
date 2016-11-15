/*
 * InchieKey.h
 *
 *  Created on: Oct 2, 2015
 *      Author: owen
 */

#ifndef INCHIEKEY_H_
#define INCHIEKEY_H_



#include <stdint.h>
#include <stdio.h>
#include "OSC/OSCMessage.h"
#include "SLIPEncodedSerial.h"
#include "OSC/SimpleWriter.h"

#include "stm32f0xx.h"

class InchieKey {

private:

public:
	InchieKey(SimpleWriter &buf, SLIPEncodedSerial &serial);
	~InchieKey() {};

	// for communication
	SimpleWriter &oscBuf;
	SLIPEncodedSerial &slipSerial;

	// for address
	char const * type = "key";
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


#endif /* INCHIEKEY_H_ */
