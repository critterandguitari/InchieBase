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

#define SYS_RENUMBER 1
#define SYS_REZERO 2

#include "SLIPEncodedSerial.h"
//#include "InchieLED.h"
#include "InchieKeyLED.h"
//#include "Inchie4KeyLED.h"
//#include "InchiePot.h"
//#include "InchieTest.h"

// uart buffers
extern hardware_uart uart_upstream;
//extern hardware_uart uart_downstream;

// OSC stuff
//SLIPEncodedSerial upstream(&uart_upstream);
SLIPEncodedSerial slipSerial(&uart_upstream);

// create inchie object and initialize
//InchiePot inchie(slipSerial);
InchieKeyLED inchie(slipSerial);
//Inchie4KeyLED inchie(slipSerial);

int main(int argc, char* argv[]) {

    int hi = 0;

    uint8_t buf[64];

    for (int i = 0; i <64; i++) buf[i] = 0;

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

    LEDON;//AUX_LED1_RED_ON;
    timer_sleep(10);
    LEDOFF;//AUX_LED1_RED_OFF;
    timer_sleep(10);
    LEDON;//AUX_LED1_RED_ON;
    timer_sleep(10);
    LEDOFF;//AUX_LED1_RED_OFF;
    timer_sleep(10);

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

	LEDOFF;

	while (1) {
		if (slipSerial.recvPacket()) {
			// if we have an address match
			if (slipSerial.decodedBuf[0] == inchie.index){
				inchie.respond(slipSerial.decodedBuf);
			}
			// or broadcast match
			else if (slipSerial.decodedBuf[0] == 255 && slipSerial.decodedBuf[1] == SYS_RENUMBER){
				//AUX_LED1_RED_ON;
				buf[0] = 255;
				buf[1] = SYS_RENUMBER;
				buf[2] = slipSerial.decodedBuf[2] + 1;
				inchie.index = buf[2];
				slipSerial.sendPacket(buf, 3);
			}
			// otherwise pass it along
			else {
				// echo
				slipSerial.sendPacket(slipSerial.decodedBuf, slipSerial.decodedLength);
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
