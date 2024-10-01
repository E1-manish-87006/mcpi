/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: jitendra
 */

#include "timer.h"


void TimerInit(uint32_t ms) {

	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	TIM4->PSC = TIM_PR-1;

	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
	TIM4->ARR = cnt - 1;

	TIM4->CNT = 0;

	TIM4->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM4_IRQn);

	TIM4->CR1 |= TIM_CR1_CEN;
}

volatile int flag = 0;

void TIM4_IRQHandler(void)
{
	if(TIM4->SR & TIM_SR_UIF) {

		TIM4->SR &= ~TIM_SR_UIF;
		flag = 1;

	}
}




