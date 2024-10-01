
#ifndef SWITCH_INTR_H_
#define SWITCH_INTR_H_

#include "stm32f4xx.h"

#define GPIO_SWITCH				GPIOA
#define SWITCH_PIN				0
#define SWITCH_GPIO_CLKEN		0

#define SWITCH_EXTI				0

void SwitchInit(void);
void EXTI0_IRQHandler(void);

extern volatile uint32_t SwitchExtiFlag;
extern volatile int c;

#endif /* SWITCH_INTR_H_ */
