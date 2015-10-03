/*
 * InchieTest.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: owen
 */


#include "InchieTest.h"

extern "C" {
#include "BlinkLed.h"
}

InchieTest::InchieTest(SimpleWriter &buf, SLIPEncodedSerial &up, SLIPEncodedSerial &down)
: oscBuf(buf), upstream(up), downstream(down)
{
	index = 0;
}

void InchieTest::init (void){

}

void InchieTest::respond (OSCMessage &msg){

}

void InchieTest::perform (void){

	if (stopwatchReport() >= 51){
		LEDON;
		stopwatchReStart();

		    sprintf(address, "/%s/%d", type, index);
		    OSCMessage msgOut(address);


			msgOut.add(1);
		    msgOut.send(oscBuf);
			upstream.sendPacket(oscBuf.buffer, oscBuf.length);

			/*msgOut.add(2);
		    msgOut.send(oscBuf);
			upstream.sendPacket(oscBuf.buffer, oscBuf.length);

			msgOut.add(3);
		    msgOut.send(oscBuf);
			upstream.sendPacket(oscBuf.buffer, oscBuf.length);

			msgOut.add(4);
		    msgOut.send(oscBuf);
			upstream.sendPacket(oscBuf.buffer, oscBuf.length);*/

		LEDOFF;
	}
}

