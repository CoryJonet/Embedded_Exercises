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

#define ARRAY_SIZE   10
#define LOOPS        10

//*****************************************************************************
// Global Variables
//*****************************************************************************

uint8_t bubbleSortASM_array[ARRAY_SIZE];
uint8_t bubbleSortC_array[ARRAY_SIZE];

//*****************************************************************************
// External Functions
//*****************************************************************************
extern void PLL_Init(void);
extern bool InitializeUART(uint32_t base, UART_CONFIG *init);
extern char uartRxPoll(uint32_t base);
extern void uartTxPoll(uint32_t base, char *data);
extern bool  initializeGPIOPort( uint32_t base, GPIO_CONFIG *init);
void sysTickInit(void);
uint32_t sysTickStop(void);
void bubbleSort(uint8_t * address, uint16_t size);


//*****************************************************************************
// Used to initialize array
//*****************************************************************************
void initArrays(uint8_t * array1, uint8_t * array2)
{
  int i;
  uint8_t value;
  
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    value = rand();
    array1[i] = value;
    array2[i] = value;
  }

}

//*****************************************************************************
// Used to verify our sorting algorithm
//*****************************************************************************
bool verifySort(uint8_t * array1, uint8_t * array2)
{
  int i;
  char msg[40];
  
  for( i=0; i < LOOPS; i++)
  {

    if ( array1[i] != array2[i])
    {
      uartTxPoll(UART0, msg);
      return false;
    }
  }
  
  return true;
}

//*****************************************************************************
// C Implementation of bubble sort
//*****************************************************************************
void bubbleSortC(uint8_t * address, int16_t size)
{
  uint16_t i,j;
  uint8_t temp;
  uint8_t swappedVal = 0;
  
  for( i = 0; i < (size-1); i++)
  {
    for ( j = 0; j < (size-i-1); j++)
    {
      if(address[j] > address[j+1])
      {
        temp = address[j];
        address[j] = address[j+1];
        address[j+1] = temp;
        swappedVal = 1;
      }
    }
  }
}


//*****************************************************************************
// Test Functions
//*****************************************************************************

void bubbleSortTestBenchASM(void)
{
  bool pass = false;
  int i;
  int avg = 0;
  int asmTotal = 0;
  int asmTicks;
  int cTotal = 0;
  int cTicks;
  char UserMsg[80];
  
  for (i=0; i < LOOPS; i++)
  {

   
    initArrays(bubbleSortASM_array, bubbleSortC_array);
    
    // Start the timer to count clock cycles
    sysTickInit();
    // Run the bubble sort
    bubbleSort( bubbleSortASM_array,  sizeof(bubbleSortASM_array));
    // Get the Clock Count
    asmTicks = sysTickStop();
    
    asmTotal = asmTotal + asmTicks;
    
    
    // Start the timer to count clock cycles
    sysTickInit();
    // Run the bubble sort
    bubbleSortC( bubbleSortC_array,  sizeof(bubbleSortC_array));
    // Get the Clock Count
    cTicks = sysTickStop();
    
    cTotal = cTotal + cTicks;
    
    
    //  Verify the sort
    pass = verifySort(bubbleSortASM_array,bubbleSortC_array);
    
    if( pass == false)
      break;
  }
  
  if ( pass == true)
  {
    // Print the success message
    avg = asmTotal/LOOPS;
    
    // Create a string with the user clock count
    // so we can print it out.
    sprintf(UserMsg, "SUCCESS\n\r");
    uartTxPoll(UART0, UserMsg);
    
    sprintf(UserMsg, "Average ASM code CLK cycles to perform sort: %15d\n\r", avg);
    uartTxPoll(UART0, UserMsg);
    
    // Print the success message
    avg = cTotal/LOOPS;
    sprintf(UserMsg, "Average C   code CLK cycles to perform sort: %15d\n\r", avg);
    uartTxPoll(UART0, UserMsg);
  }
  else
  {
    // Print the error message
    sprintf(UserMsg, "ASM Code Results: ERROR\n\r");
    uartTxPoll(UART0, UserMsg);
  }
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
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
  uartTxPoll(UART0, "=============================\n\r");
  uartTxPoll(UART0, "Bubble Sort Testbench START\n\r");
  uartTxPoll(UART0, "=============================\n\r");
  uartTxPoll(UART0, "\n\r");  
  
  bubbleSortTestBenchASM();
  
  uartTxPoll(UART0, "\n\r");   
  uartTxPoll(UART0, "=============================\n\r");
  uartTxPoll(UART0, "Bubble Sort Testbench END  \n\r");
  uartTxPoll(UART0, "=============================\n\r");

  while(1){};

  
}

