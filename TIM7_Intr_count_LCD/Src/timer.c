#include "timer.h"

void Timer_Init(uint32_t ms) {
	//* Enable Timer APB clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	//* Set Timer clock -- PCLK = TCLK = 16 MHz : * Set PR = 16000
	TIM6->PSC = (PR-1);
	//* Calculate number of clocks to count (CNT).
	uint32_t cnt = (TCLK / 1000) * ms / PR;
	//* Set CNT in ARR.
	TIM6->ARR = (cnt-1);
	//* Reset Timer Counter to 0.
	TIM6->CNT = 0;
	//* Enable Timer Interrupt in DIER.
	TIM6->DIER |= TIM_DIER_UIE;
	//* Enable Timer Interrupt in NVIC.
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	//* Start Timer in CR1.
	TIM6->CR1 |= TIM_CR1_CEN;
}

void Timer_Delay(uint32_t ms) {
	//* Calculate number of clocks to count (CNT).
	uint32_t cnt = (TCLK / 1000) * ms / PR;
	//* Set CNT in ARR.
	TIM6->ARR = cnt - 1;
	//* Reset Timer Counter to 0.
	TIM6->CNT = 0;
	//* Start Timer in CR1.
	TIM6->CR1 |= TIM_CR1_CEN;
	//* Wait for UIF flag (in SR).
	while(!(TIM6->SR & TIM_SR_UIF));
	//* Clear UIF in SR
	TIM6->SR &= ~TIM_SR_UIF;
	//* Stop Timer in CR1.
	TIM6->CR1 &= ~TIM_CR1_CEN;
}

void TIM6_DAC_IRQHandler(void) {
	//* Check if UIF flag is set (in SR).
	if(TIM6->SR & TIM_SR_UIF) {
		//* Clear UIF in SR (Ack)
		TIM6->SR &= ~TIM_SR_UIF;
		//DelayMs(1000);
		Timer_Delay(1000);
	}
}
