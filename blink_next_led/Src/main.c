/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "switch_intr.h"
#include "led.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



int main(void) {
	SystemInit();
	SwitchInit();
	LedInit(LED_ORANGE_PIN);
	LedInit(LED_RED_PIN);
	//int c=0;
	while(1) {
		// if switch is pressed blink orange led
		while(SwitchExtiFlag == 0)
			;
		/*// Optimization Level -- any
			LDR r7, =SwitchExtiFlag 	// r7 = &SwitchExtiFlag;
		loop:
			LDR r0, [r7]				// r0 = *r7;
			CMP r0, #0					// r0 == 0 (compare)
			BEQ loop					// if 0, repeat loop
		*/
		LedBlink(LED_ORANGE_PIN, 1000);

		SwitchExtiFlag = 0;
	}

	return 0;
}
























