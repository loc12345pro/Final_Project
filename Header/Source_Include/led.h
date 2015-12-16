/*
 * Date: 11/10/2015
 * Writer: Loc Pham
 * Description: This file contains led function prototypes
 */

#ifndef _LED_H
#define _LED_H

// Include header files
#include "stm32f4_discovery.h"

// PUBLIC FUNCTION DECLARATIONS

/*
 * Name: BoardLed_Init
 * Module: Led
 * Parameters:  None
 * Description: Initialize red, blue, green, orange Led
 * Return: void
 */
void BoardLed_Init(void);

/*
 * Name: Led_Blink
 * Module: Led
 * Parameters:  led (Led_TypeDef)
                delay_time (uint32_t)
 * Description: Blink specific led in miliseconds between led off and led on
 * Return: void
 */
void Led_Blink(Led_TypeDef led, uint32_t delay_time);

/*
 * Name: BoardLed_Blink_Clockwise
 * Module: Led
 * Parameters:  led_start (Led_TypeDef)
                delay_time (uint32_t)
 * Description: Blink all leds clock-wised, starting and stopping at specific LED, 
                in milisecond between blinking 
 * Return: void
 */
void BoardLed_Blink_Clockwise(Led_TypeDef led_start, uint32_t delay_time);

/*
 * Name: Led_Find_In_Array
 * Module: Led
 * Parameters:  led (Led_TypeDef)
                leds[LEDn] (Led_TypeDef)
 * Description: Find the index of a specific led in array of leds
 * Return: index of led in array
 */
uint8_t Led_Find_In_Array(Led_TypeDef led, Led_TypeDef leds[LEDn]);

/*
 * Name: BoardLed_Blink_CounterClockwise
 * Module: Led
 * Parameters:  led_start (Led_TypeDef)
                delay_time (uint32_t)
 * Description: Blink all leds counter clock-wised, starting and stopping at specific LED, 
                in milisecond between blinking 
 * Return: void
 */
void BoardLed_Blink_CounterClockwise(Led_TypeDef led_start, uint32_t delay_time);

/*
 * Name: Leds_Blink
 * Module: Led
 * Parameters:  leds[LEDn] (Led_TypeDef)
                led_num (uint32_t)
                delay_time (uint32_t)
 * Description: Turn on all Leds and then turn off all Leds between miliseconds
 * Return: void
 */
void Leds_Blink(Led_TypeDef leds[LEDn], uint8_t led_num, uint32_t delay_time);

/*
 * Name: Leds_On
 * Module: Led
 * Parameters:  leds[LEDn] (Led_TypeDef)
                led_num (uint32_t)
 * Description: Turn on all Leds
 * Return: void
 */
void Leds_On(Led_TypeDef leds[LEDn], uint8_t led_num);

/*
 * Name: Leds_On
 * Module: Led
 * Parameters:  leds[LEDn] (Led_TypeDef)
                led_num (uint32_t)
 * Description: Turn off all Leds
 * Return: void
 */
void Leds_Off(Led_TypeDef leds[LEDn], uint8_t led_num);

/*
 * Name: Led_GetByName
 * Module: Led
 * Parameters:  name_led (char*)
 * Description: Get led based one name of led
 * Return: void
 */
Led_TypeDef Led_GetByName(char* name_led);

#endif
/*End file*/
