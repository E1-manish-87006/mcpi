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
#include "adc.h"
#include "i2c_lcd.h"
#include "switch_intr.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
//On switch press, read ADC (LDR) input and display on I2C LCD.
int main(void) {
	uint16_t val;
	char str[32];
	SystemInit();
	ADC_Init();
	Lcd_Init();
	SwitchInit();
	//Lcd_Puts(LCD_LINE1,"hii");
	while(1){
		while(!SwitchExtiFlag);
		//Lcd_Puts(LCD_LINE1,"hello");
		if(SwitchExtiFlag){
		val = ADC_GetValue();
		Lcd_Puts(LCD_LINE1, str);
		sprintf(str, "ADC = %u", val);
		DelayMs(1000);
		SwitchExtiFlag=0;
		}

	}

	return 0;
}
