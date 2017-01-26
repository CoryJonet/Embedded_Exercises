//*****************************************************************************
//
//*****************************************************************************
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lm4f120h5qr.h"
#include "team.h"
#include "./inc/adc.h"
#include "./inc/UART.h"
#include "./inc/gpio.h"
#include "boardUtil.h"




/******************************************************************************
 * Defines
 *****************************************************************************/
#define SYSTICK_100HZ          0

#define OUTPUT_ENABLE_B       0xEF
#define ENABLES_B             0x0F
#define nROW_0                ~(1 << 0)
#define RED_EN                (1 << 4)
#define GREEN_EN              (1 << 5)
#define BLUE_EN               (1 << 6)
#define ROW_EN                (1 << 7)
#define ENABLES_OFF           0x00
#define OUT_EN_B              (1 << 4)



/******************************************************************************
 * Global Variables
 *****************************************************************************/
GPIO_PORT *GpioPortA = (GPIO_PORT *)PORTA;
GPIO_PORT *GpioPortB = (GPIO_PORT *)PORTB;
GPIO_PORT *GpioPortC = (GPIO_PORT *)PORTC;
GPIO_PORT *GpioPortD = (GPIO_PORT *)PORTD;
GPIO_PORT *GpioPortE = (GPIO_PORT *)PORTE;
GPIO_PORT *GpioPortF = (GPIO_PORT *)PORTF;
 
extern uint8_t RedDutyCycle[];
extern uint8_t GreenDutyCycle[];
 

//*****************************************************************************
// Part A
//*****************************************************************************
void sysTickSleep(uint32_t loadVal)
{

}


//*****************************************************************************
// Part B
//*****************************************************************************
uint8_t getBlueLEDs(uint8_t *dutyCycleCount)
{
  uint16_t adcVal = 0;
  
  return 0xFF;
}


//*****************************************************************************
// DO NOT MODIFY
//*****************************************************************************
int 
main(void)
{
  uint8_t redData;
  uint8_t greenData;
  uint8_t blueData;
  uint8_t dutyCycleCount=0;
  
  boardInit();
  
  uartTxPoll(UART0, "\n\r\n\r");
  uartTxPoll(UART0, "================================\n\r");
  uartTxPoll(UART0, "SysTick START\n\r");
  uartTxPoll(UART0, "================================\n\r");
  uartTxPoll(UART0, "\n\r");  
  
  // Activate Column 0
  GpioPortC->Data = ROW_EN;
  GpioPortB->Data = nROW_0;
  GpioPortC->Data = ENABLES_OFF;
  
  while(1)
  {
    sysTickSleep(SYSTICK_100HZ);
    
    blueData = getBlueLEDs(&dutyCycleCount);
    redData = getActiveLEDs(RedDutyCycle, dutyCycleCount);
    greenData = getActiveLEDs(GreenDutyCycle, dutyCycleCount);
    
    // Disable all Outputs
    GpioPortF->Data |= ~OUTPUT_ENABLE_B;

    // Set Red LEDs
    GpioPortC->Data = RED_EN;
    GpioPortB->Data = redData;
    GpioPortC->Data = ENABLES_OFF;
    
    // Set Blue LEDs
    GpioPortC->Data = BLUE_EN;
    GpioPortB->Data = blueData;
    GpioPortC->Data = ENABLES_OFF;
    
    // Set Green LEDs
    GpioPortC->Data = GREEN_EN;
    GpioPortB->Data = greenData;
    GpioPortC->Data = ENABLES_OFF;
    
    // Enable All Output
    GpioPortF->Data &= OUTPUT_ENABLE_B;
    
    dutyCycleCount = (dutyCycleCount+1)%100;

  }

  
}

