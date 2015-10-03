//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef BLINKLED_H_
#define BLINKLED_H_

#include "stm32f0xx.h"

// ----- LED definitions ------------------------------------------------------

#define LEDON GPIO_ResetBits(GPIOB, GPIO_Pin_3)
#define LEDOFF GPIO_SetBits(GPIOB, GPIO_Pin_3)

// ----------------------------------------------------------------------------

void blink_led_init(void);


// ----------------------------------------------------------------------------

#endif // BLINKLED_H_
