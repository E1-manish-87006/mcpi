/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 21, 2024
*/

#include "switch_intr.h"
#include "led.h"

void SwitchInit(void) {
	// Enable GPIO clock
    RCC->AHB1ENR |= BV(SWITCH_GPIO_CLKEN);
	// Set gpio mode as input
    GPIOA->MODER &= ~(BV(SWITCH_PIN*2+1) | BV(SWITCH_PIN*2));
	// set no pull-up pull-down registers
    GPIOA->PUPDR &= ~(BV(SWITCH_PIN*2+1) | BV(SWITCH_PIN*2));
	EXTI->FTSR |= BV(SWITCH_EXTI);
	EXTI->IMR |= BV(SWITCH_EXTI);
	SYSCFG->EXTICR[0] &= ~(BV(3) | BV(2) | BV(1) | BV(0));
	NVIC_EnableIRQ(EXTI0_IRQn);

}

// intr handler(ISR) written with exactly same name as of handler fn name in vector table.
// it overrides the WEAK function written in startup.S
void EXTI0_IRQHandler(void) {
	EXTI->PR |= BV(SWITCH_EXTI);
	LedToggle(LED_RED_PIN);
}









