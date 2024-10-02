
#ifndef WDT_H_
#define WDT_H_

#include "stm32f4xx.h"

#define LSI_CLK	32000
#define WDT_PR	64

void IWDG_Init(uint32_t ms);
void IWDG_Refresh(void);
int IWDG_IsReset(void);

#endif /* WDT_H_ */
