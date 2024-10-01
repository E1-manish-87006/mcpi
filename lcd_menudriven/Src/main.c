#include <stdint.h>
#include <stdio.h>
#include<string.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "i2c_lcd.h"
#include "rtc.h"
#include "dac.h"
#include "switch.h"
#include "timer.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	char str2[32];
	char str1[24];
	int count=0;
	int seq = 0;
	int scrl = 0;
	RTC_Date d, dt = { .Date = 29, .Month = 2, .Year = 24, .WeekDay = 4 };
	RTC_Time t, tm = { .Hours = 11, .Minutes = 59, .Seconds = 50 };

	uint8_t val=255, step1 = 2, step2 = 1;

	SystemInit();
	LcdInit();
	LcdPuts(LCD_LINE1, " MCPI LAB EXAM :)");
	DelayMs(2000);
	LcdWrite(LCD_CMD, LCD_CLEAR);
	RTC_Init(&dt, &tm);
	DAC_Init();
	SwitchInit(SWITCH);
	TimerInit(1000);

	while(1) {

		while(exti0_flag == 0)
		{
		RTC_GetTime(&t);
		RTC_GetDate(&d);
		sprintf(str1, "%02d-%02d-%02d%02d:%02d:%02d", d.Date, d.Month, d.Year,t.Hours, t.Minutes, t.Seconds);
		LcdPuts(LCD_LINE1, str1);
		DelayMs(500);
		}

		count++;
		DelayMs(100);

		if(count == 1)
		{

			for(seq = 0; seq < 128 ; seq++)
			 {
			    val = val - step1;
				DAC_SetValue(val);
				DelayMs(40);
				sprintf(str1,"%d",val);
				LcdWrite(LCD_CMD, LCD_CLEAR);
				LcdPuts(LCD_LINE1, str1);
				LcdPuts(LCD_LINE2,"JITENDRA DAC=");
				LcdPuts(LCD_LINE2_14, str2);
			}

			for(seq = 0; seq < 256 ; seq++)
			{
				val = val + step2;
				DAC_SetValue(val);
				DelayMs(40);
				sprintf(str2,"%d",val);
				LcdWrite(LCD_CMD, LCD_CLEAR);
				LcdPuts(LCD_LINE1, str1);
				LcdPuts(LCD_LINE2,"JITENDRA DAC=");
				LcdPuts(LCD_LINE2_14, str2);
			}
			exti0_flag = 0;
		}

		else if(count == 2)
		{
			for(scrl =0; scrl < 10 ; scrl++)
			{
			LcdWrite(LCD_CMD, LCD_CUR_SHF);
			LcdPuts(LCD_LINE1, str1);
			LcdPuts(LCD_LINE2, str2);
			DelayMs(1000);
			}
			exti0_flag = 0;
		}

		else if(count == 3)
		{
			LcdWrite(LCD_CMD, LCD_CLEAR);
			DelayMs(40);
			count = 0;
			exti0_flag = 0;
		}

	}
	return 0;
}
