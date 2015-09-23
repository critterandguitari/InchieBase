//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>

extern "C" {
#include "uart.h"
#include "stm32f0xx.h"
#include "Timer.h"
#include "BlinkLed.h"
}

#include "OSC/OSCMessage.h"
#include "SLIPEncodedSerial.h"
#include "OSC/SimpleWriter.h"
#include "Serial.h"

// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 2 / 3)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


extern hardware_uart uart_upstream;
extern hardware_uart uart_downstream;

// OSC stuff
SLIPEncodedSerial upstream(&uart_upstream);
SLIPEncodedSerial downstream(&uart_downstream);
SimpleWriter oscBuf;

// reset to default turn on state
void reset(OSCMessage &msg){
}

void renumber(OSCMessage &msg){
  // send out a
}

void ledControl(OSCMessage &msg) {

	  int stat;

	  // digitalWrite(ledPin, LOW);
	  if (msg.isInt(0)) {
	    stat = msg.getInt(0);

	    stat %= 8;

	    if (stat == 0) {
	      AUX_LED_RED_OFF;
	      AUX_LED_GREEN_OFF;
	      AUX_LED_BLUE_OFF;
	    }
	    if (stat == 1) {
	      AUX_LED_RED_OFF;
	      AUX_LED_GREEN_OFF;
	      AUX_LED_BLUE_ON;
	    }
	    if (stat == 2) {
	      AUX_LED_RED_OFF;
	      AUX_LED_GREEN_ON;
	      AUX_LED_BLUE_OFF;
	    }
	    if (stat == 3) {
	      AUX_LED_RED_OFF;
	      AUX_LED_GREEN_ON;
	      AUX_LED_BLUE_ON;
	    }
	    if (stat == 4) {
	      AUX_LED_RED_ON;
	      AUX_LED_GREEN_OFF;
	      AUX_LED_BLUE_OFF;
	    }
	    if (stat == 5) {
	      AUX_LED_RED_ON;
	      AUX_LED_GREEN_OFF;
	      AUX_LED_BLUE_ON;
	    }
	    if (stat == 6) {
	      AUX_LED_RED_ON;
	      AUX_LED_GREEN_ON;
	      AUX_LED_BLUE_OFF;
	    }
	    if (stat == 7) {
	      AUX_LED_RED_ON;
	      AUX_LED_GREEN_ON;
	      AUX_LED_BLUE_ON;
	    }
	  }

      msg.send(oscBuf);
      upstream.sendPacket(oscBuf.buffer, oscBuf.length);
}

uint32_t owen = 0;

int main(int argc, char* argv[]) {

	OSCMessage msgIn;

	uart2_init();

	blink_led_init();

	timer_start();

    AUX_LED_RED_OFF;
    AUX_LED_GREEN_OFF;
    AUX_LED_BLUE_OFF;
    timer_sleep(1000);
	AUX_LED_RED_ON;
    timer_sleep(1000);
	AUX_LED_GREEN_ON;
    timer_sleep(1000);
	AUX_LED_BLUE_ON;

	while (1) {
		if (upstream.recvPacket()) {
			// fill the message and dispatch it

			msgIn.fill(upstream.decodedBuf, upstream.decodedLength);

			// dispatch it
			if(!msgIn.hasError()) {
				// wait for start message so we aren't sending stuff during boot
				if (msgIn.fullMatch("/ready", 0)){
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

    AUX_LED_RED_OFF;
    AUX_LED_GREEN_OFF;
    AUX_LED_BLUE_OFF;

	while (1) {
		if (upstream.recvPacket()) {
			// fill the message and dispatch it

			msgIn.fill(upstream.decodedBuf, upstream.decodedLength);

			// dispatch it
			if(!msgIn.hasError()) {

				// led
				msgIn.dispatch("/led", ledControl, 0);


				msgIn.empty(); // free space occupied by message

			}
			else {   // just empty it if there was an error
				msgIn.empty(); // free space occupied by message
			}
		}

		// do stuff

	} // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
