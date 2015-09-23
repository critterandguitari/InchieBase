//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef BLINKLED_H_
#define BLINKLED_H_

#include "stm32f0xx.h"

// ----- LED definitions ------------------------------------------------------

#define AUX_LED_BLUE_ON GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED_RED_ON GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED_GREEN_ON GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define AUX_LED_BLUE_OFF GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define AUX_LED_RED_OFF GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define AUX_LED_GREEN_OFF GPIO_SetBits(GPIOA, GPIO_Pin_7)

#define LEDON GPIO_ResetBits(GPIOB, GPIO_Pin_3)
#define LEDOFF GPIO_SetBits(GPIOB, GPIO_Pin_3)

// ----------------------------------------------------------------------------

void blink_led_init(void);


// ----------------------------------------------------------------------------

#endif // BLINKLED_H_
