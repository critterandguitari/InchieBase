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
