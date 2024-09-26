#include "switch.h"

void SwitchInit(void) {
	RCC->AHB1ENR |= BV(GPIO_SWITCH_CLKEN);

	GPIOA->MODER &= ~(BV(SWITCH_PIN*2) | BV(SWITCH_PIN*2+1));
	GPIOA->PUPDR &= ~(BV(SWITCH_PIN*2) | BV(SWITCH_PIN*2+1));
}

int SwitchIsPressed(void) {
	uint32_t idr = GPIO_SWITCH->IDR;
	if(!(idr&SWITCH_PIN))
		return 0;
	return 1;
}











