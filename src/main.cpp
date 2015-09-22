//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"



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

// ----------------------------------------------------------------------------
//
// STM32F0 led blink sample (trace via $(trace)).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// To demonstrate POSIX retargetting, reroute the STDOUT and STDERR to the
// trace device and display messages on both of them.
//
// Then demonstrates how to blink a led with 1Hz, using a
// continuous loop and SysTick delays.
//
// On DEBUG, the uptime in seconds is also displayed on the trace device.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the $(trace) output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//
// The external clock frequency is specified as a preprocessor definition
// passed to the compiler via a command line option (see the 'C/C++ General' ->
// 'Paths and Symbols' -> the 'Symbols' tab, if you want to change it).
// The value selected during project creation was HSE_VALUE=8000000.
//
// Note: The default clock settings take the user defined HSE_VALUE and try
// to reach the maximum possible system clock. For the default 8MHz input
// the result is guaranteed, but for other values it might not be possible,
// so please adjust the PLL settings in system/src/cmsis/system_stm32f0xx.c
//

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


// OSC stuff
SLIPEncodedSerial slip;
Serial serialUart2;
SimpleWriter oscBuf;

extern hardware_uart uart_upstream;
extern hardware_uart uart_downstream;

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
      slip.sendPacket(oscBuf.buffer, oscBuf.length, &uart_upstream);
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
		if (slip.recvPacket(&uart_upstream)) {
			// fill the message and dispatch it


			msgIn.fill(slip.decodedBuf, slip.decodedLength);

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
		if (slip.recvPacket(&uart_upstream)) {
			// fill the message and dispatch it

			msgIn.fill(slip.decodedBuf, slip.decodedLength);

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
