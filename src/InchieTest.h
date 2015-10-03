/*
 * InchieTest.h
 *
 *  Created on: Oct 3, 2015
 *      Author: owen
 */

#ifndef INCHIETEST_H_
#define INCHIETEST_H_



#include <stdint.h>
#include <stdio.h>
#include "OSC/OSCMessage.h"
#include "SLIPEncodedSerial.h"
#include "OSC/SimpleWriter.h"
extern "C" {
#include "Timer.h"
}

#include "stm32f0xx.h"

class InchieTest {

private:

public:
	InchieTest(SimpleWriter &buf, SLIPEncodedSerial &up, SLIPEncodedSerial &down);
	~InchieTest() {};

	// for communication
	SimpleWriter &oscBuf;
	SLIPEncodedSerial &upstream;
	SLIPEncodedSerial &downstream;

	// for address
	char const * type = "tet";
	int index = 0;
	char address[16];

	// every inchie must have these three fucntions
	void init (void);
	void respond (OSCMessage &msg);
	void perform (void);

	// specific for this inchie
	uint32_t count = 0;

};


#endif /* INCHIETEST_H_ */
