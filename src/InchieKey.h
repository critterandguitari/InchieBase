/*
 * InchieKey.h
 *
 *  Created on: Oct 2, 2015
 *      Author: owen
 */

#ifndef INCHIEKEY_H_
#define INCHIEKEY_H_



#include <stdint.h>
#include "Inchie.h"

#include "stm32f0xx.h"

class InchieKey : public Inchie {

private:

public:
	virtual ~InchieKey() {};

	//char const * type = "type";

	// every inchie must have these three fucntions
	virtual void init (void);
	virtual void respond (OSCMessage &msg);
	virtual bool perform (OSCMessage &msg);

	uint8_t state = 0;
	uint8_t stateLast = 0;

};


#endif /* INCHIEKEY_H_ */
