/*
 * Inchie.h
 *
 *  Created on: Oct 2, 2015
 *      Author: owen
 */

#ifndef INCHIE_H_
#define INCHIE_H_

#include <stdint.h>
#include "OSC/OSCMessage.h"

class Inchie {

private:

public:
	virtual ~Inchie() {};

	// every inchie must have these three fucntions
	virtual void init (void) =0;
	virtual void respond (OSCMessage &msg) =0;
	virtual bool perform (OSCMessage &msg) =0;

};



#endif /* INCHIE_H_ */
