/*
 * Date: 29/10/2015
 * Writer: Loc Pham
 * Description: This file contains function implementations concerned with system function,
 * such as: Delay, Initialize clock,...
 */

#include "system.h"

__IO uint32_t g_sys_tick;

void SysTick_Handler(void)
{
    g_sys_tick++;
}

void Delay(uint32_t ms_tick)
{
    uint32_t current_sys_tick = g_sys_tick;
    while ((g_sys_tick - current_sys_tick) <= ms_tick)
    {
        // Wait
    }
}

void SysClock_Init(void)
{
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
}

// End file
