/*
 * InchiePot.h
 *
 *  Created on: Oct 3, 2015
 *      Author: owen
 */

#ifndef INCHIEPOT_H_
#define INCHIEPOT_H_


#include <stdint.h>
#include <stdio.h>
#include "OSC/OSCMessage.h"
#include "SLIPEncodedSerial.h"
#include "OSC/SimpleWriter.h"
extern "C" {
#include "Timer.h"
}

#include "stm32f0xx.h"

class InchiePot {

private:

public:
	InchiePot(SimpleWriter &buf, SLIPEncodedSerial &up, SLIPEncodedSerial &down);
	~InchiePot() {};

	// for communication
	SimpleWriter &oscBuf;
	SLIPEncodedSerial &upstream;
	SLIPEncodedSerial &downstream;

	// for address
	char const * type = "pot";
	int index = 0;
	char address[16];

	// every inchie must have these three fucntions
	void init (void);
	void respond (OSCMessage &msg);
	void perform (void);

	// specific for this inchie
	int potVal = 0;
	int potValLast = 0;
	uint32_t count = 0;

};




#endif /* INCHIEPOT_H_ */
