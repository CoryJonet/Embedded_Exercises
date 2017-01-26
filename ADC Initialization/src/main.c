//*****************************************************************************
//
//*****************************************************************************
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lm4f120h5qr.h"
#include "board_config.h"
#include "team.h"


/******************************************************************************
 * Defines
 *****************************************************************************/
#define PORTA                 0x40004000
#define PORTB                 0x40005000
#define PORTC                 0x40006000
#define PORTD                 0x40007000
#define PORTE                 0x40024000
#define PORTF                 0x40025000

#define POT_LEFT  1
#define POT_RIGHT 0

/******************************************************************************
 * Global Variables
 *****************************************************************************/
 GPIO_PORT *GpioPortA = (GPIO_PORT *)PORTA;
 GPIO_PORT *GpioPortB = (GPIO_PORT *)PORTB;
 GPIO_PORT *GpioPortC = (GPIO_PORT *)PORTC;
 GPIO_PORT *GpioPortD = (GPIO_PORT *)PORTD;
 GPIO_PORT *GpioPortE = (GPIO_PORT *)PORTE;
 GPIO_PORT *GpioPortF = (GPIO_PORT *)PORTF;
 
//*****************************************************************************
// External Functions
//*****************************************************************************
extern void PLL_Init(void);
extern bool InitializeUART(uint32_t base, UART_CONFIG *init);
extern char uartRxPoll(uint32_t base);
extern void uartTxPoll(uint32_t base, char *data);
extern bool  initializeGPIOPort( uint32_t base, GPIO_CONFIG *init);
extern void sysTickInit(void);
extern void sysTickWait1mS(int32_t num);


/****************************************************************************
 ****************************************************************************/
void initializeADC(void)
{
  uint32_t delay;
  
   
    // Enable Port E
    // See the schematics, page 3, on the class website to determine
    // which pins to configure
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
    sysTickWait1mS(10);

    // Set the direction as an input


    // Set the alternate function


    // Disable the Digital Enable


    // Enable Analog 




    // Enable ADC 
    SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;
    sysTickWait1mS(10);

    // Make sure to look at the #defines found in lm4f120h5qr.h.  
    // Line 3367 starts the bit mask definitions for the ADC.
    
    // (Step 1 from Data Sheet)
    // Disable Sample Sequencer #3 
    

    // ((Step 2 from Data Sheet)
    // Configure the sample sequencer so Sample Sequencer #3 (EM3) 
    // is triggered by the processor
    
    
    // (Step 3 from Data Sheet)
    // Clear the Sample Input Select for Sample Sequencer #3
    

    // (Step 4 from Data Sheet)
    // Configure the Sample Sequencer #3 control register.  Make sure to set 
    // the 1st Sample Interrupt Enable and the End of Sequence bits
    
    
    // Not shown in the data sheet.  See SAC register
    // Clear Averaging Bits
    

    // Not shown in the data sheet.  See SAC register
    // Average 64 samples
    
    
    // Do NOT enable the Sequencer after this.  This is done in GetADCval

}

//*****************************************************************************
// Get the ADC value of a given ADC Channel
//*****************************************************************************
uint32_t GetADCval(uint32_t Channel)
{
  uint32_t result;

  ADC0_SSMUX3_R = Channel;      // Set the channel
  ADC0_ACTSS_R  |= ADC_ACTSS_ASEN3; // Enable SS3
  ADC0_PSSI_R = ADC_PSSI_SS3;     // Initiate SS3

  while(0 == (ADC0_RIS_R & ADC_RIS_INR3)); // Wait for END of conversion
  result = ADC0_SSFIFO3_R & 0x0FFF;     // Read the 12-bit ADC result
  ADC0_ISC_R = ADC_ISC_IN3;         // Acknowledge completion

  return result;
}

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  uint32_t ADCval1 = 0;
  uint32_t ADCval2 = 0;
  uint32_t i = 0;
  char msg[40];

  
  // Initialize the PLLs so the the main CPU frequency is 80MHz
  PLL_Init();
  
  initializeGPIOPort(PORTA, &portA_config);
  initializeGPIOPort(PORTB, &portB_config);
  initializeGPIOPort(PORTC, &portC_config);
  initializeGPIOPort(PORTD, &portD_config);
  //initializeGPIOPort(PORTE, &portE_config);
  initializeGPIOPort(PORTF, &portF_config);
  
  InitializeUART(UART0, &UART0_config);
  sysTickInit();
  
  
  uartTxPoll(UART0, "\n\r\n\r");
  uartTxPoll(UART0, "================================\n\r");
  uartTxPoll(UART0, "ADC Test Bench START\n\r");
  uartTxPoll(UART0, "================================\n\r");
  uartTxPoll(UART0, "\n\r");  
  
  initializeADC();
   
  while(1)
  {
        sysTickWait1mS(300);
        //columnEnable( gpioPortF, gpioPortB, activeRow);
         // updateCol = false;
        ADCval1 = GetADCval(POT_RIGHT);
        sprintf(msg, "Right: 0x%03x\t\t",ADCval1);
        uartTxPoll(UART0, msg);
        
        sysTickWait1mS(10);
        ADCval2 = GetADCval(POT_LEFT);
        sprintf(msg, "Left: 0x%03x\r",ADCval2);
        uartTxPoll(UART0, msg);
  };

  
}

