
#include "wdt.h"

void IWDG_Init(uint32_t ms) {
	//* step 0. Enable LSI clock.
	RCC->CSR |= RCC_CSR_LSION;				//enable LSI (stm32 manual 7.3.21)
	while(!(RCC->CSR & RCC_CSR_LSIRDY));	//wait for LSI ready flag
	//* step 1. Enable IWDG by writing 0xCCCC into IWDG_KR.
	IWDG->KR = 0xCCCC;
	//* step 2. Enable register access by writing 0x5555 into IWDG_KR.
	IWDG->KR = 0x5555;
	//* step 3. Set Prescalar value in IWDG_PR.
	IWDG->PR = IWDG_PR_PR_2;
	//* step 4. Set Reload value in IWDG_RLR.
	int cnt = (LSI_CLK / 1000) * ms / WDT_PR;
	IWDG->RLR = cnt - 1;
	//* step 5. Wait for registers to be updated i.e. IWDG_SR == 0x00000000;
	while(IWDG->SR);
	// Refresh WDT
	IWDG_Refresh();
}

void IWDG_Refresh(void) {
	// Refresh counter by writing 0xAAAA into IWDG_KR.
	IWDG->KR = 0xAAAA;
}

int IWDG_IsReset(void) {
	// If reset due to IWDG, Bit 29 in RCC_CSR is set.
	if(RCC->CSR & RCC_CSR_IWDGRSTF)
		return 1;
	return 0;
}

