#include "initBoard.h"

#define PORTA   0x40004000
extern GPIO_CONFIG portA_config;
extern UART_CONFIG UART0_config;

void initBoard(void)
{
   int i = 0;
    
  // Initialize the PLLs so the the main CPU frequency is 80MHz
  PLL_Init();
  
  initializeGPIOPort(PORTA, &portA_config);
  
  InitializeUART(UART0, &UART0_config);
  
  // Need to wait a while before the UART is functional
  while(i < 10000)
  {
    i++;
  }
  
}
