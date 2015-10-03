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
#include "InchiePot.h"
#include "InchieTest.h"

// uart buffers
extern hardware_uart uart_upstream;
extern hardware_uart uart_downstream;

// OSC stuff
SLIPEncodedSerial upstream(&uart_upstream);
SLIPEncodedSerial downstream(&uart_downstream);
SimpleWriter oscBuf;

// create inchie object and initialize
//InchiePot inchie(oscBuf, upstream, downstream);
InchieTest inchie(oscBuf, upstream, downstream);

/// main callbacks
void reset(OSCMessage &msg) {
	inchie.index = 0;
	inchie.init();
}

void renumber(OSCMessage &msg) {

	// send out my type
	sprintf(inchie.address, "/%s", inchie.type);
	OSCMessage msgOut(inchie.address);
	msgOut.send(oscBuf);
	downstream.sendPacket(oscBuf.buffer, oscBuf.length);
}

void incIndex(OSCMessage &msg) {
	inchie.index++;
}

void respond(OSCMessage &msg) {
	inchie.respond(msg);
}

void reportStat(OSCMessage &msg){
	LEDON;
    OSCMessage msgOut("/stat");
	//msgOut.add((int)(downstream.uart->rx_buf_head - downstream.uart->rx_buf_tail));
	msgOut.add((int)downstream.uart->rx_buf_head);
	msgOut.add((int)downstream.uart->rx_buf_tail);
    msgOut.send(oscBuf);
	upstream.sendPacket(oscBuf.buffer, oscBuf.length);
	msgOut.empty();
	LEDOFF;
}

int main(int argc, char* argv[]) {

	// init system stuff
	uart_init();
	blink_led_init();
	timer_start();

	// init the inchie
	inchie.init();

	OSCMessage msgIn;

	LEDOFF;
	timer_sleep(100);
	LEDON;
	timer_sleep(100);
	LEDOFF;
	timer_sleep(100);
	LEDON;

	stopwatchReStart();

	while (1) {
		if (upstream.recvPacket()) {
			// fill the message and dispatch it

			msgIn.fill(upstream.decodedBuf, upstream.decodedLength);

			// dispatch it
			if (!msgIn.hasError()) {
				// wait for start message so we aren't sending stuff during boot
				if (msgIn.fullMatch("/ready", 0)) {
					msgIn.send(oscBuf);
					downstream.sendPacket(oscBuf.buffer, oscBuf.length);
					msgIn.empty(); // free space occupied by message
					break;
				}
				msgIn.empty();
			} else {   // just empty it if there was an error
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
			if (!msgIn.hasError()) {

				// send it downstream
				msgIn.send(oscBuf);
				downstream.sendPacket(oscBuf.buffer, oscBuf.length);

				sprintf(inchie.address, "/%s/%d", inchie.type, inchie.index);
				msgIn.dispatch(inchie.address, respond, 0);

				sprintf(inchie.address, "/%s", inchie.type);
				msgIn.dispatch(inchie.address, incIndex, 0);

				msgIn.dispatch("/renumber", renumber, 0);

				msgIn.dispatch("/resetindex", reset, 0);

				msgIn.dispatch("/stat", reportStat, 0);

				msgIn.empty(); // free space occupied by message

			} else {   // just empty it if there was an error
				msgIn.empty(); // free space occupied by message
			}
		}

		if (downstream.recvPacket()) {
			msgIn.fill(downstream.decodedBuf, downstream.decodedLength);
			if (!msgIn.hasError()) {

				// send it upstream
				msgIn.send(oscBuf);
				upstream.sendPacket(oscBuf.buffer, oscBuf.length);

				msgIn.empty(); // free space occupied by message

			} else {   // just empty it if there was an error
				msgIn.empty(); // free space occupied by message
			}
		}
		// do stuff, possibly send message out
		inchie.perform();

	} // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
