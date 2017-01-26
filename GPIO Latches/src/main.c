//*****************************************************************************
//
//*****************************************************************************
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lm4f120h5qr.h"
#include "team.h"
#include "initBoard.h"
#include "board_config.h"
#include "gpio.h"
#include "boardUtil.h"

/******************************************************************************
 * Defines
 *****************************************************************************/

/******************************************************************************
 * Global Variables
 *****************************************************************************/


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  initBoard();
    
  uartTxPoll(UART0, "\n\r\n\r");
  uartTxPoll(UART0, "================================\n\r");
  uartTxPoll(UART0, "GPIO Latch Test Bench\n\r");
  uartTxPoll(UART0, "================================\n\r");
  uartTxPoll(UART0, "\n\r");  

  while(1)
  {
    getUserInput();
  };

  
}




