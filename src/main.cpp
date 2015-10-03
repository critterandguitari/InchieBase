//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <string>

extern "C" {
#include "uart.h"
#include "stm32f0xx.h"
#include "Timer.h"
#include "BlinkLed.h"
}

#include "OSC/OSCMessage.h"
#include "SLIPEncodedSerial.h"
#include "OSC/SimpleWriter.h"
#include "InchieLED.h"
#include "InchieKey.h"

// uart buffers
extern hardware_uart uart_upstream;
extern hardware_uart uart_downstream;

// OSC stuff
SLIPEncodedSerial upstream(&uart_upstream);
SLIPEncodedSerial downstream(&uart_downstream);
SimpleWriter oscBuf;

// declaration of independence
int inchieIndex = 0;   // or would be controlElement.index
char const * inchieType = "key";   // or would be controlElement.type
char inchieAddress[16];

// create inchie object and initialize
InchieLED inchieKey;
Inchie& inchie = inchieKey;

//InchieLED inchieLED;
//Inchie& inchie = inchieLED;

/// main callbacks
void reset(OSCMessage &msg){
	inchieIndex = 0;
	inchie.init();
}

void renumber(OSCMessage &msg){

	// send out my type
    sprintf(inchieAddress, "/%s", inchieType);
    OSCMessage msgOut(inchieAddress);
    msgOut.send(oscBuf);
	downstream.sendPacket(oscBuf.buffer, oscBuf.length);
}

void incIndex(OSCMessage &msg){
	inchieIndex++;
}

void respond(OSCMessage &msg){
	inchie.respond(msg);
}

int main(int argc, char* argv[]) {

	inchie.init();

	OSCMessage msgIn;

	uart_init();
	blink_led_init();
	timer_start();

	LEDOFF;
    timer_sleep(1000);
    LEDON;
    timer_sleep(1000);
    LEDOFF;
    timer_sleep(1000);
    LEDON;

	while (1) {
		if (upstream.recvPacket()) {
			// fill the message and dispatch it

			msgIn.fill(upstream.decodedBuf, upstream.decodedLength);

			// dispatch it
			if(!msgIn.hasError()) {
				// wait for start message so we aren't sending stuff during boot
				if (msgIn.fullMatch("/ready", 0)){
				    msgIn.send(oscBuf);
				    downstream.sendPacket(oscBuf.buffer, oscBuf.length);
	                msgIn.empty(); // free space occupied by message
					break;
				}
				msgIn.empty();
			}
			else {   // just empty it if there was an error
				msgIn.empty(); // free space occupied by message
			}
		}
	} // waiting for /ready command

    LEDOFF;

	while (1) {
		if (upstream.recvPacket()) {
			// fill the message and dispatch it

			msgIn.fill(upstream.decodedBuf, upstream.decodedLength);

			// dispatch it
			if(!msgIn.hasError()) {

			    // send it downstream
                msgIn.send(oscBuf);
                downstream.sendPacket(oscBuf.buffer, oscBuf.length);

                sprintf(inchieAddress, "/%s/%d", inchieType, inchieIndex);
                msgIn.dispatch(inchieAddress, respond, 0);

                sprintf(inchieAddress, "/%s", inchieType);
                msgIn.dispatch(inchieAddress, incIndex, 0);

                msgIn.dispatch("/renumber", renumber, 0);

                msgIn.dispatch("/resetindex", reset, 0);

				msgIn.empty(); // free space occupied by message

			}
			else {   // just empty it if there was an error
				msgIn.empty(); // free space occupied by message
			}
		}

        if (downstream.recvPacket()) {
            msgIn.fill(downstream.decodedBuf, downstream.decodedLength);
            if(!msgIn.hasError()) {

                // send it upstream
                msgIn.send(oscBuf);
                upstream.sendPacket(oscBuf.buffer, oscBuf.length);

                msgIn.empty(); // free space occupied by message

            }
            else {   // just empty it if there was an error
                msgIn.empty(); // free space occupied by message
            }
        }

    	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) LEDON;
    	else LEDOFF;

      /*  sprintf(inchieAddress, "/%s/%d", inchieType, inchieIndex);
	    OSCMessage msgOut(inchieAddress);
		// do stuff, possibly send message out
        if (inchie.perform(msgOut)) {
    	    //msgOut.send(oscBuf);
    		//upstream.sendPacket(oscBuf.buffer, oscBuf.length);
        }*/

	} // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
