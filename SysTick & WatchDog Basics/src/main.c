//*****************************************************************************
//
//*****************************************************************************
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lm4f120h5qr.h"
#include "board_config.h"
#include "team.h"
#include "systick.h"
#include "UART.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define PORTA                 0x40004000
#define PORTB                 0x40005000
#define PORTC                 0x40006000
#define PORTD                 0x40007000
#define PORTE                 0x40024000
#define PORTF                 0x40025000

#define DISABLE_SYSTICK_IRQ   false
#define ENABLE_SYSTICK_IRQ    true

/******************************************************************************
 * Global Variables
 *****************************************************************************/
 GPIO_PORT *GpioPortA = (GPIO_PORT *)PORTA;
 GPIO_PORT *GpioPortB = (GPIO_PORT *)PORTB;
 GPIO_PORT *GpioPortC = (GPIO_PORT *)PORTC;
 GPIO_PORT *GpioPortD = (GPIO_PORT *)PORTD;
 GPIO_PORT *GpioPortE = (GPIO_PORT *)PORTE;
 GPIO_PORT *GpioPortF = (GPIO_PORT *)PORTF;
 
volatile bool AlertSeconds = false;
volatile uint32_t SecondCount = 0;
char Msg[40];
 
 
//*****************************************************************************
// External Functions
//*****************************************************************************
extern void PLL_Init(void);
extern bool initializeGPIOPort( uint32_t base, GPIO_CONFIG *init);
extern void EnableInterrupts(void);
extern void DisableInterrupts(void);
extern bool InitializeUART(uint32_t base, UART_CONFIG *init);
extern char uartRxPoll(uint32_t base);
extern void uartTxPoll(uint32_t base, char *data);
extern void watchdogInit(uint32_t mSec, uint8_t priority);


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
  
  watchdogInit(5000,1);
  initializeSysTick(800000, ENABLE_SYSTICK_IRQ);

  
  EnableInterrupts(); 
  
  while(1)
  {
    
    DisableInterrupts();    // Avoid Race Conditions
    if(AlertSeconds)
    {
        // Print out the new second count
        sprintf(Msg,"Seconds: %d\n\r",SecondCount);
        uartTxPoll(UART0, Msg);
      
        // Reset the flag
        AlertSeconds = false;
    }
    EnableInterrupts(); // Turn interrupts back on.
  };

  
}

