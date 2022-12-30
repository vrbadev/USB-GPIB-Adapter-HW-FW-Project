#ifndef DELAY_H_
#define DELAY_H_

#include "stm32f103x6.h"

void stk_init(void);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#endif
