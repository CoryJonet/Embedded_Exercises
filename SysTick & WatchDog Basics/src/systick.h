#ifndef __SYSTICK_H__
#define __SYSTICK_H__

void SYSTICKIntHandler(void);
void initializeSysTick(uint32_t count, bool enableInterrupts);

#endif
