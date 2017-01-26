//*****************************************************************************
//
//*****************************************************************************
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lm4f120h5qr.h"
#include "board_config.h"
#include "team.h"
#include "sorting.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define PORTA   0x40004000
#define PORTB   0x40005000
#define PORTC   0x40006000
#define PORTD   0x40007000
#define PORTE   0x40024000
#define PORTF   0x40025000

#define ARRAY_SIZE   100
#define LOOPS        10

//*****************************************************************************
// Global Variables
//*****************************************************************************

int32_t A_Matrix = 0x03020100;
int32_t B_Matrix = 0x07060504;
int32_t C_Matrix = 0x00000000;


//*****************************************************************************
// External Functions
//*****************************************************************************
extern void PLL_Init(void);
extern bool InitializeUART(uint32_t base, UART_CONFIG *init);
extern char uartRxPoll(uint32_t base);
extern void uartTxPoll(uint32_t base, char *data);
extern bool  initializeGPIOPort( uint32_t base, GPIO_CONFIG *init);

extern uint32_t matrixMuliply(int32_t *A, int32_t *B, int32_t *C);

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  uint32_t ret = 0;
  // Initialize the PLLs so the the main CPU frequency is 80MHz
  PLL_Init();
  
  initializeGPIOPort(PORTA, &portA_config);
  initializeGPIOPort(PORTB, &portB_config);
  initializeGPIOPort(PORTC, &portC_config);
  initializeGPIOPort(PORTD, &portD_config);
  initializeGPIOPort(PORTE, &portE_config);
  initializeGPIOPort(PORTF, &portF_config);
  
  InitializeUART(UART0, &UART0_config);

  uartTxPoll(UART0, "\n\r\n\r");
  uartTxPoll(UART0, "=======================================\n\r");
  uartTxPoll(UART0, " Matrix Multiplicatiion Testbench START\n\r");
  uartTxPoll(UART0, "========================================\n\r");
  uartTxPoll(UART0, "\n\r");  
  
  ret = matrixMuliply(&A_Matrix, &B_Matrix, &C_Matrix);
  if ( C_Matrix != 0x1F1A0706)
      uartTxPoll(UART0, "FAILED\n\r");
  else
      uartTxPoll(UART0, "PASSED\n\r");
  
  uartTxPoll(UART0, "\n\r");   
  uartTxPoll(UART0, "=======================================\n\r");
  uartTxPoll(UART0, "Matrix Multiplicatiion Testbench START\n\r");
  uartTxPoll(UART0, "=======================================\n\r");

  while(1){};

  
}

