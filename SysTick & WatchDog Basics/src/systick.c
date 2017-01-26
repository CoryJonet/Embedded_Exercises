#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lm4f120h5qr.h"

extern  volatile bool AlertSeconds; 
extern  volatile uint32_t SecondCount;
 
 /****************************************************************************
 * The SysTick Handler 
 ****************************************************************************/
void SYSTICKIntHandler(void)
{
  
    // Determine if one second has passed
    // If so, upate SecondCound and set AlertSeconds to true
    
    // !!!!!!!!!
    // Note:  If you don't know what a static variable is, search the web
    // to find out.
    // !!!!!!!!!

    // clear the SysTick Timer Interrupt
  
    // reset the watchdog timer
}


/****************************************************************************
 * Initialize the SysTick timer to a given count.
 * Turns on Interrupts
 ****************************************************************************/
void initializeSysTick(uint32_t count, bool enableInterrupts)
{
  // disable SysTick timer

  // Set reload to count-1

  // clear the current count
  
  // If enableInterrupts is true, enable the timer with interrupts
  // else enable the timer without interrupts
  
}
