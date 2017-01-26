#ifndef __ADC_H__
#define __ADC_H__

#define POT_LEFT  1
#define POT_RIGHT 0

void initializeADC(void);
uint32_t GetADCval(uint32_t Channel);
#endif
