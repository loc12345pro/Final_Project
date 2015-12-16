/*
 * Date: 29/10/2015
 * Writer: Loc Pham
 * Description: This file contains function prototypes concerned with system function,
 * such as: Delay, Initialize clock,...
 */

#ifndef _SYSTEM_H
#define _SYSTEM_H

// Include headers
#include "stm32f4xx.h"

// PUBLIC FUNCTIONS PROTOTYPES
/*
 * Name: SysTick_Handler
 * Module: System
 * Parameters:  None
 * Description: Increase sytem tick variables by one
 * Return: void
 */
void SysTick_Handler(void);

/*
 * Name: Delay
 * Module: System
 * Parameters:  ms_tick (uint32_t)
 * Description: Delay system within ms_tick (miliseconds)
 * Return: void
 */
void Delay(uint32_t ms_tick);

/*
 * Name: Delay
 * Module: System
 * Parameters:  ms_tick (uint32_t)
 * Description: Initialize system clock
 * Return: void
 */
void SysClock_Init(void);

#endif
// End file
