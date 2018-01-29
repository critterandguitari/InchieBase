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
#include "SLIPEncodedSerial.h"


#include "stm32f0xx.h"

class InchiePot {

private:

public:
	InchiePot(SLIPEncodedSerial &serial);
	~InchiePot() {};

	// for communication
	SLIPEncodedSerial &slipSerial;

	// for address
	char const * type = "pot";
	uint8_t index;
	char address[16];

	// every inchie must have these three fucntions
	void init (void);
	void respond (const uint8_t *buf);
	void perform (void);

	// specific for this inchie
	int16_t potVal;
	uint32_t pollCount;
	bool changed;

};




#endif /* INCHIEPOT_H_ */
