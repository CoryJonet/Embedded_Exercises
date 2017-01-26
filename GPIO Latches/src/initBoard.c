#include "initBoard.h"

extern GPIO_CONFIG portA_config;
extern GPIO_CONFIG portB_config;
extern GPIO_CONFIG portC_config;
extern GPIO_CONFIG portD_config;
extern GPIO_CONFIG portE_config;
extern GPIO_CONFIG portF_config;
extern UART_CONFIG UART0_config;

extern void sysTickInitInt(uint32_t count, uint8_t priority);
extern void EnableInterrupts(void);


/******************************************************************************
 * Global Variables
 *****************************************************************************/
 GPIO_PORT *PortA = (GPIO_PORT *)PORTA;
 GPIO_PORT *PortB = (GPIO_PORT *)PORTB;
 GPIO_PORT *PortC = (GPIO_PORT *)PORTC;
 GPIO_PORT *PortD = (GPIO_PORT *)PORTD;
 GPIO_PORT *PortE = (GPIO_PORT *)PORTE;
 GPIO_PORT *PortF = (GPIO_PORT *)PORTF;
 



void initBoard(void)
{
   int i = 0;
    
  // Initialize the PLLs so the the main CPU frequency is 80MHz
  PLL_Init();
  
  initializeGPIOPort(PORTA, &portA_config);
  initializeGPIOPort(PORTB, &portB_config);
  initializeGPIOPort(PORTC, &portC_config);
  initializeGPIOPort(PORTD, &portD_config);
  initializeGPIOPort(PORTE, &portE_config);
  initializeGPIOPort(PORTF, &portF_config);
  
  InitializeUART(UART0, &UART0_config);
  
  // Need to wait a while before the UART is functional
  while(i < 10000)
  {
    i++;
  }

}
