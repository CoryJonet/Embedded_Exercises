#include "boardUtil.h"
#include "gpio.h"

extern GPIO_PORT *PortA ;
extern GPIO_PORT *PortB ;
extern GPIO_PORT *PortC ;
extern GPIO_PORT *PortD ;
extern GPIO_PORT *PortE ;
extern GPIO_PORT *PortF ;
extern void uartTxPoll(uint32_t base, char *data);
extern char uartRxPoll(uint32_t base);


// For the following #defines, use the (1 << x) to define which bit position 
// is used to enable the given signal.  
#define LATCH_ALL_ON_M     0xF0
#define LATCH_ALL_OFF_M    0x00
#define LATCH_OE_B_M    ~(1 << 4)  // What pin enabled the latch OE?  (Active Low)

/**********************************************************
 * Enables all of the latch enables (PortC)
 **********************************************************/
__inline void enableAllLatchEnables(void)
{
    PortC->Data = LATCH_ALL_ON_M;
}

/**********************************************************
 * Disables all of the latch enables (PortC)
 **********************************************************/
__inline void disableAllLatchEnables(void)
{
    PortC->Data = LATCH_ALL_OFF_M;
}

/**********************************************************
 * Enable all of the Output Enables for the latches 
 * (PortF)
 **********************************************************/
__inline void outputEnable(void)
{
    PortF->Data &= LATCH_OE_B_M;
}

/* Add Code Below */

/**********************************************************
 * Add a single line of code for each of the functions 
 * below until you reach displayLed();
 *
 * Each function will write a value out the the Data 
 * Register of the specified port.  Make sure to examine the 
 * schematic to determine what values to write out
 *
 * Note that the row/color enables are Active High
 *
 * Note that these one line functions DO NOT change the 
 * data stored in the latches, rather they enable/disable
 * the ability to write to the latch.  Writing data to 
 * the latch is done after the latch is enabled using a 
 * different GPIO port.
 *
 * There are three functions above that can be used as 
 * examples on how to access the data registers of a 
 * given port.  You will also use the functions in 
 * displayLed()
 **********************************************************/


/**********************************************************
 * Enable only the green latch.  Leave the lower 4-bits of 
 * PortC undisturbed (PortC)
 **********************************************************/
__inline void greenEnable(void)
{
    
}

/**********************************************************
 * Enable only the red latch.  Leave the lower 4-bits of 
 * PortC undisturbed (PortC)
 **********************************************************/
__inline void redEnable(void)
{
    
}

/**********************************************************
 * Enable only the bluelatch.  Leave the lower 4-bits of 
 * PortC undisturbed (PortC)
 **********************************************************/
__inline void blueEnable(void)
{
   
}

/**********************************************************
 * Enable only the row latch.  Leave the lower 4-bits of 
 * PortC undisturbed (PortC)
 **********************************************************/
__inline void rowEnable(void)
{
    
}


/**********************************************************
 * Given 3 parameters, it calls the functions above to
 * turn on specificed LEDs.  You will need to add code 
 * that corresponds to the comments below.
 *
 * When you are writing a value a latch, which port
 * will you write the data to?  
 *
 * Parameters:
 *
 *    row : The row number to turn on. 
 *    color: a single character that will be'R' or 'G' or 'B'
 *    lednumber:  Which LED to turn on.  0 is left most
 *                                       7 is right most
 *
 * 
 *  NOTE: All of the LEDs and ROW data are active low, 
 *  so be sure to invert the value you write out to the 
 *  latches!
 *
 * Example row = 3
 * This means that the 4th row from the bottom will be 
 * turned on, so we need to write ~(1<<3) to the row latch.
 **********************************************************/
void displayLed( int8_t row, int8_t color, int8_t ledNumber)
{
    // Enable all the latches
    
    
    // Write out 0xFF to set all latches to 0xFF
    // All of the Rows and LEDs are active low!
    
    
    // Disable all the latches
    
    
    // Enable Row latch
    
    
    // Write the data to the row latch.  
    // See the example above.
    
    
    // Decide which color latch to enable

    
    // Write the active LED into the selected color latch
     
    
    // Disable all the latches
    
    
    // Enable Output
    
    
}

/*********************** Do NOT Modify below****************/

/**********************************************************
 * Prints out the prompts and returns user input from
 * UART0
 **********************************************************/
void getUserInput(void)
{
    char row;
    char leds;
    char color;
    
     uartTxPoll(UART0, "\n\r");
    
    do {
    uartTxPoll(UART0, "Enter Row Number (7-0): ");
    row  = uartRxPoll(UART0);
    uartTxPoll(UART0, &row);
    uartTxPoll(UART0, "\n\r");
    uartTxPoll(UART0, "\n\r");
    } while( row < 0x30 || row > 0x37);
    row = row - 0x30;
    
    
    do {
    uartTxPoll(UART0, "Enter the color (R,G,B): ");
    color  = uartRxPoll(UART0);
    uartTxPoll(UART0, &color);
    uartTxPoll(UART0, "\n\r");
    uartTxPoll(UART0, "\n\r");
    } while( color != 'R' && color != 'G' && color != 'B');
    

    
    do {
    uartTxPoll(UART0, "Enter leds number to turn on (7-0): ");
    leds  = uartRxPoll(UART0);
     uartTxPoll(UART0, &leds);
     uartTxPoll(UART0, "\n\r");
     uartTxPoll(UART0, "\n\r");
    } while( leds < 0x30 || leds > 0x37);
    
    leds = leds - 0x30;
    displayLed( row, color, leds);
    
   
}



