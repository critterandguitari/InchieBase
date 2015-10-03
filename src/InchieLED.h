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

class InchieLED : public Inchie {

private:

public:
	virtual ~InchieLED() {};

	//char const * type = "type";

	// every inchie must have these three fucntions
	virtual void init (void);
	virtual void respond (OSCMessage &msg);
	virtual bool perform (OSCMessage &msg);

};


#endif /* INCHIELED_H_ */
