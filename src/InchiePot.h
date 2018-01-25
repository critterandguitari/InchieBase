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


#include "stm32f0xx.h"

class InchiePot {

private:

public:
	InchiePot(SimpleWriter &buf, SLIPEncodedSerial &serial);
	~InchiePot() {};

	// for communication
	SimpleWriter &oscBuf;
	SLIPEncodedSerial &slipSerial;

	// for address
	char const * type = "pot";
	int index;
	char address[16];

	// every inchie must have these three fucntions
	void init (void);
	void respond (OSCMessage &msg);
	void perform (void);

	// specific for this inchie
	int16_t potVal;
	uint32_t pollCount;
	bool changed;

};




#endif /* INCHIEPOT_H_ */
