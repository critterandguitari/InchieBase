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
//#include "InchieLED.h"
//#include "InchieKeyLED.h"
#include "Inchie4KeyLED.h"
//#include "InchiePot.h"
//#include "InchieTest.h"

// uart buffers
extern hardware_uart uart_upstream;
//extern hardware_uart uart_downstream;

// OSC stuff
//SLIPEncodedSerial upstream(&uart_upstream);
SLIPEncodedSerial slipSerial(&uart_upstream);
SimpleWriter oscBuf;

// create inchie object and initialize
//InchiePot inchie(oscBuf, slipSerial);
//InchieKeyLED inchie(oscBuf, slipSerial);
Inchie4KeyLED inchie(oscBuf, slipSerial);

/// main callbacks
void reset(OSCMessage &msg) {
	inchie.index = 1;
	inchie.init();
}

void renumber(OSCMessage &msg) {

	// send out my type
	sprintf(inchie.address, "/%s", inchie.type);
	OSCMessage msgOut(inchie.address);
	msgOut.send(oscBuf);
	slipSerial.sendPacket(oscBuf.buffer, oscBuf.length);
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
	msgOut.add((int)123);
	msgOut.add((int)456);
    msgOut.send(oscBuf);
    slipSerial.sendPacket(oscBuf.buffer, oscBuf.length);
	msgOut.empty();
	LEDOFF;
}

int main(int argc, char* argv[]) {

    int hi = 0;

    /* Check if the system has resumed from IWDG reset */
    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
    {
      /* IWDGRST flag set */
      /* Clear reset flags */
        hi = 1;
      RCC_ClearFlag();
    }
    else
    {
        hi = 0;
      /* IWDGRST flag is not set */
    }

	// init system stuff
	uart_init();
	blink_led_init();
	timer_start();

	// init the inchie
	inchie.init();

	OSCMessage msgIn;
	OSCMessage msgOut("/hi");


    LEDON;
    timer_sleep(10);
    LEDOFF;
    timer_sleep(10);
    LEDON;
    timer_sleep(10);
    LEDOFF;
    timer_sleep(10);

    // say hi
    msgOut.add((int)hi);
    msgOut.send(oscBuf);
    slipSerial.sendPacket(oscBuf.buffer, oscBuf.length);
    stopwatchReStart();
    while(stopwatchReport() < 500){
        uart_service_tx();
    }
    stopwatchReStart();

/*    while (1) {
        LEDON;
        timer_sleep(100);
        LEDOFF;
        timer_sleep(100);


        slipSerial.sendPacket(oscBuf.buffer, oscBuf.length);

        while(stopwatchReport() < 500){
            uart_service_tx();
        }
        stopwatchReStart();
    }*/

    /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
       dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescaler(IWDG_Prescaler_32);

    /* Set counter reload value to obtain 250ms IWDG TimeOut.
       Counter Reload Value = 250ms/IWDG counter clock period
                            = 250ms / (LSI/32)
                            = 0.25s / (LsiFreq/32)
                            = LsiFreq/(32 * 4)
                            = LsiFreq/128
     */
    __IO uint32_t LsiFreq = 40000;
    IWDG_SetReload(LsiFreq/128);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();

	while (1) {
		if (slipSerial.recvPacket()) {
			// fill the message and dispatch it

			msgIn.fill(slipSerial.decodedBuf, slipSerial.decodedLength);

			// dispatch it
			if (!msgIn.hasError()) {
				// wait for start message so we aren't sending stuff during boot
				if (msgIn.fullMatch("/ready", 0)) {
					msgIn.send(oscBuf);
					slipSerial.sendPacket(oscBuf.buffer, oscBuf.length);
					msgIn.empty(); // free space occupied by message
					break;
				}
				msgIn.empty();
			} else {   // just empty it if there was an error
				msgIn.empty(); // free space occupied by message
			}
		}
	    /* Reload IWDG counter */
	    IWDG_ReloadCounter();
	} // waiting for /ready command

	LEDOFF;

	while (1) {
		if (slipSerial.recvPacket()) {
			// fill the message and dispatch it

			msgIn.fill(slipSerial.decodedBuf, slipSerial.decodedLength);

			// dispatch it
			if (!msgIn.hasError()) {

				// send it downstream
				msgIn.send(oscBuf);
				slipSerial.sendPacket(oscBuf.buffer, oscBuf.length);

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

		// do stuff, possibly send message out
		// limit 1 per ms
		if (stopwatchReport() > 2){
		    stopwatchReStart();
	        inchie.perform();
		}

		//	service the tx buffer
		uart_service_tx();
        /* Reload IWDG counter */
        IWDG_ReloadCounter();
	} // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
