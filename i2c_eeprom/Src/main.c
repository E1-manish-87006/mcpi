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
#include <string.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "eeprom.h"
#include "uart.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	char str1[32] = "God Bless You!\r\n";
	char str2[32] = "";
	SystemInit();
	UartInit(BAUD_9600);
	UartPuts("I2C EEPROM Demo!\r\n");
	EEPROM_Init();
	UartPuts("Enter a String: \r\n");
	UartGets(str1);
	EEPROM_Write(0x0020, (uint8_t*)str1, strlen(str1)+1);
	UartPuts("I2C EEPROM Write Done!\r\n");
	EEPROM_Read(0x0020, (uint8_t*)str2, 32);
	UartPuts("I2C EEPROM Read Done!\r\n");
	UartPuts(str2);
	while(1);
	return 0;
}









