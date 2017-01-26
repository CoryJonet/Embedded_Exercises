#ifndef __BOARD_UTIL_H__
#define __BOARD_UTIL_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lm4f120h5qr.h"
#include "./inc/adc.h"
#include "./inc/pll.h"
#include "./inc/gpio.h"


#define PORTA                 0x40004000
#define PORTB                 0x40005000
#define PORTC                 0x40006000
#define PORTD                 0x40007000
#define PORTE                 0x40024000
#define PORTF                 0x40025000

uint8_t getActiveLEDs(uint8_t *dutyCycleArray, uint8_t dutyCycleCount);
void boardInit(void);

#endif
