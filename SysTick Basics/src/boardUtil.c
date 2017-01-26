#include "boardUtil.h"
#include "board_config.h"

extern GPIO_PORT *GpioPortA ;
extern GPIO_PORT *GpioPortB;
extern GPIO_PORT *GpioPortC;
extern GPIO_PORT *GpioPortD;
extern GPIO_PORT *GpioPortE;
extern GPIO_PORT *GpioPortF;
 
 
uint8_t RedDutyCycle[8] = 
  {
    60,
    50,
    40,
    30,
    0,
    0,
    0,
    0
  };
 
  
uint8_t GreenDutyCycle[8] = 
  {
    0,
    0,
    30,
    40,
    50,
    60,
    0,
    0
  };
  

//*****************************************************************************
// DO NOT MODIFY
//*****************************************************************************
void boardInit(void)
{
  int i;
  
  // Initialize the PLLs so the the main CPU frequency is 80MHz
  PLL_Init();
  
  initializeGPIOPort(PORTA, &portA_config);
  initializeGPIOPort(PORTB, &portB_config);
  initializeGPIOPort(PORTC, &portC_config);
  initializeGPIOPort(PORTD, &portD_config);
  initializeGPIOPort(PORTE, &portE_config);
  initializeGPIOPort(PORTF, &portF_config);
  
  InitializeUART(UART0, &UART0_config);
  initializeADC();
  // Need to wait a while before the UART is functional
  while(i < 10000)
  {
    i++;
  }
  
}  

//*****************************************************************************
// DO NOT MODIFY
//*****************************************************************************
uint8_t getActiveLEDs(uint8_t *dutyCycleArray, uint8_t dutyCycleCount)
{
  uint8_t returnVal = 0xFF;
  uint8_t i;
  
  // For each LED, determine if the LED should be turned on based
  // on the current value of the duty cycle.
  for(i=0; i < 8; i++)
  {
    if(dutyCycleCount < dutyCycleArray[i] )
    {
      returnVal &= ~(1 << i);
    }
  }
  
  return returnVal;
}
