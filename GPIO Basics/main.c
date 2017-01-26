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

/******************************************************************************
 * Defines
 *****************************************************************************/
#define PORTA   0x40004000
#define PORTB   0x40005000
#define PORTC   0x40006000
#define PORTD   0x40007000
#define PORTE   0x40024000
#define PORTF   0x40025000

/******************************* ADD GPIO DEFINES ****************************/
#define PORTD_DIGITAL_EN_M    0
#define PORTD_OUTPUT_M        0
#define PORTD_PULL_UP_M       0
#define PORTD_OPEN_DRAIN_M    0

#define PORTF_DIGITAL_EN_M    0
#define PORTF_OUTPUT_M        0
#define PORTF_PULL_UP_M       0
#define PORTF_OPEN_DRAIN_M    0


//*****************************************************************************
// Make sure tha the base address is one of the 6 valid addresses listed 
// above.
//
// Return 'true' if it is valid and 'false' if it is not.
//*****************************************************************************
bool verifyPort(uint32_t base)
{  
    return false;
}

//*****************************************************************************
// Initialize a GPIO port.  You will need to modify the switch statement to 
// add support for PORTD.
//*****************************************************************************
bool initGpioPort(  uint32_t portAddr,  
                    uint8_t digitalEnableMask,
                    uint8_t outputMask, 
                    uint8_t pullUpMask, 
                    uint8_t openDrianMask)
{
  uint32_t delay;
  GPIO_PORT *myPort = (GPIO_PORT *)portAddr;
    
  if( verifyPort(portAddr) == false )
      return false;
  
  // Check to see which Port we are configuring
  switch (portAddr)
  {
    case PORTB:
    {
      SYSCTL_RCGCGPIO_R   |= SYSCTL_RCGCGPIO_R1;
      delay = SYSCTL_RCGCGPIO_R;
      break;
    }
    case PORTF:
    {
      SYSCTL_RCGCGPIO_R   |= SYSCTL_RCGCGPIO_R5;
      delay = SYSCTL_RCGCGPIO_R;
      
      // Port F has a lock register, so we need to unlock it before making modifications
      GPIO_PORTF_LOCK_R = 0x4C4F434B;
      GPIO_PORTF_CR_R = 0xFF;
      break;
    }
    default:
    {
      return false;
    }
  }
  
  myPort->DigitalEnable = digitalEnableMask;
  myPort->Direction = outputMask;
  myPort->PullUpSelect = pullUpMask;
  myPort->OpenDrainSelect = openDrianMask;
 
  return true;
  
}

/******************************************************************************
 * Indicates if a button is being pressed
 *
 * Paramter(s)
 *      base - Base address of the GPIO Port
 *      pin -  Which Pin on the provided port we are examining.
 *
 * IMPORTANT: These signals are ACTIVE-LOW!  Use the GPIO_PORT struct
 * to access the data register.  
 *
 * Returns
 *  -1 if base is not a valid GPIO port
 *   0 if the button is not pressed
 *   1 if the button is pressed
 *****************************************************************************/
int32_t  buttonPressed( uint32_t base, uint8_t pin)
{
    return -1;

}

//*****************************************************************************
// DO NOT MODIFY BELOW!!!
//*****************************************************************************

//*****************************************************************************
//*****************************************************************************
void detectButtonChange(uint8_t button)
{

  char msg[20] ;
  uint32_t gpioBase = 0;
 uint8_t buttonNumber;
  
  switch (button) 
  {
    case PA6_SW2 :
    {
      gpioBase = PORTA;
      buttonNumber = 2;
      break;
    }
    case PA7_SW3 :
    {
      gpioBase = PORTA;
      buttonNumber = 3;
      break;
    }
    case PD2_SW4 :
    {
      gpioBase = PORTD;
      buttonNumber = 4;
      break;
    }
    case PD3_SW5 :
    {
      gpioBase = PORTD;
      buttonNumber = 5;
      break;
    }
    case PF1_SW6 :
    {
      gpioBase = PORTF;
      buttonNumber = 6;
      break;
    }
    default:
    {
      return;
    }
  }
  
  if ( buttonPressed( gpioBase, button) == 1)
  {
    sprintf(msg, "Button %d Pressed\n\r",buttonNumber);
    uartTxPoll(UART0, msg);
  }
  
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  initBoard();
    
  // Initialize PORT D
  initGpioPort( 
                PORTD,
                PORTD_DIGITAL_EN_M,
                PORTD_OUTPUT_M, 
                PORTD_PULL_UP_M, 
                PORTD_OPEN_DRAIN_M
              );
    
  // Initialize PORT F
  initGpioPort( 
                PORTF,
                PORTF_DIGITAL_EN_M,
                PORTF_OUTPUT_M, 
                PORTF_PULL_UP_M, 
                PORTF_OPEN_DRAIN_M
              );
    
  
      
  uartTxPoll(UART0, "\n\r\n\r");
  uartTxPoll(UART0, "================================\n\r");
  uartTxPoll(UART0, "GPIO Test Bench\n\r");
  uartTxPoll(UART0, "================================\n\r");
  uartTxPoll(UART0, "\n\r");  

  while(1)
  {
    detectButtonChange(PA6_SW2);
    detectButtonChange(PA7_SW3);
    detectButtonChange(PD2_SW4);
    detectButtonChange(PD3_SW5);
    detectButtonChange(PF1_SW6);
  };

  
}




