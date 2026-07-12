#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

void timerInit(void);
void delay(uint32_t time);
void delay_us(uint32_t time);
void timerStart(uint32_t time);
void timerWait(void);
void timerCounter(void);


#endif /* TIMER_H_ */
