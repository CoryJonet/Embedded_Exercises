#ifndef __INIT_BOARD_H__
#define __INIT_BOARD_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UART.h"
#include "gpio.h"


extern void PLL_Init(void);
extern bool InitializeUART(uint32_t base, UART_CONFIG *init);
extern char uartRxPoll(uint32_t base);
extern void uartTxPoll(uint32_t base, char *data);
extern bool  initializeGPIOPort( uint32_t base, GPIO_CONFIG *init);

void initBoard(void);

#endif
