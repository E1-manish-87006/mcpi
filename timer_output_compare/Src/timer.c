
#include "timer.h"

void Timer_Init(void) {
	// GPIOD.12,13,14,15 -- as AF2 i.e. Tim4 Output Compare Channels
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= BV(12*2+1) | BV(13*2+1) | BV(14*2+1) | BV(15*2+1);
	GPIOD->MODER &= ~(BV(12*2) | BV(13*2) | BV(14*2) | BV(15*2));
	GPIOD->AFR[1] |= BV(17) | BV(21) | BV(25) | BV(29);

	// Tim4 Output Compare
	// enable tim clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	// set prescalar
	TIM4->PSC = PR-1;
	// clear timer counter
	TIM4->CNT = 0;
	// set arr value
	TIM4->ARR = 500;
	// set ccr1, ccr2, ccr3, ccr4 values
	TIM4->CCR1 = 100;
	TIM4->CCR2 = 200;
	TIM4->CCR3 = 300;
	TIM4->CCR4 = 400;
	// set output mode -- toggle on match (011)
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_1;
	TIM4->CCMR2 |= TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC4M_0 | TIM_CCMR2_OC4M_1;
	// enable output compare
	TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
	// start the timer
	TIM4->CR1 |= TIM_CR1_CEN;
}






