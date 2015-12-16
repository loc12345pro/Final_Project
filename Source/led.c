/*
 * Date: 11/07/2015
 * Writer: Loc Pham
 * Description: Implement functions declared in file led.h
 */
 
// Include header files
#include "led.h"
#include "system.h"
#include <string.h>
#include "common.h"

void BoardLed_Init(void)
{
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
}

void Led_Blink(Led_TypeDef led, uint32_t delay_time)
{
    STM_EVAL_LEDOn(led);
    Delay(delay_time);
    STM_EVAL_LEDOff(led);
    Delay(delay_time);
}

void BoardLed_Blink_Clockwise(Led_TypeDef led_start, uint32_t delay_time)
{
    Led_TypeDef leds[LEDn] = { LED4, LED3, LED5, LED6 };
    uint8_t led_index = Led_Find_In_Array(led_start, leds);
    
    uint8_t led_iterator = led_index;
    for (; led_iterator < LEDn; led_iterator++)
    {
        Led_Blink(leds[led_iterator], delay_time);
    }
    
    for (led_iterator = 0u; led_iterator <= led_index; led_iterator++)
    {
        Led_Blink(leds[led_iterator], delay_time);
    }
}

void BoardLed_Blink_CounterClockwise(Led_TypeDef led_start, uint32_t delay_time)
{
    Led_TypeDef leds[LEDn] = { LED4, LED3, LED5, LED6 };
    uint8_t led_index = Led_Find_In_Array(led_start, leds);
    
    int8_t led_iterator = (int8_t) led_index;
    for (; led_iterator >= 0; led_iterator--)
    {
        Led_Blink(leds[led_iterator], delay_time);
    }
    
    for (led_iterator = LEDn - 1; led_iterator >= led_index; led_iterator--)
    {
        Led_Blink(leds[led_iterator], delay_time);
    }
}

uint8_t Led_Find_In_Array(Led_TypeDef led, Led_TypeDef leds[LEDn])
{
    uint8_t led_iterator = 0u;
    uint8_t isFound = 0;
    for (; led_iterator < LEDn && !isFound; led_iterator++)
    {
        if (leds[led_iterator] == led)
        {
            isFound = 1;
        }
    }
    
    return led_iterator;
}

void Leds_Blink(Led_TypeDef leds[LEDn], uint8_t led_num, uint32_t delay_time)
{
    Leds_On(leds, led_num);
    Delay(delay_time);
    Leds_Off(leds, led_num);
    Delay(delay_time);
}

void Leds_On(Led_TypeDef leds[LEDn], uint8_t led_num)
{
    uint8_t led_index = 0u;
    for (; led_index < led_num; led_index++)
    {
        STM_EVAL_LEDOn(leds[led_index]);
    }
}

void Leds_Off(Led_TypeDef leds[LEDn], uint8_t led_num)
{
    uint8_t led_index = 0u;
    for (; led_index < led_num; led_index++)
    {
        STM_EVAL_LEDOff(leds[led_index]);
    }
}

Led_TypeDef Led_GetByName(char* name_led)
{
    Led_TypeDef result = LED4;
    
    if (name_led != NULL)
    {
        if (strcasecmp(name_led, "orange") == EQUAL)
        {
            // LED 3
            result = LED3;
        }
        else if (strcasecmp(name_led, "green") == EQUAL)
        {
            // LED 4
            result = LED4;
        }
        else if (strcasecmp(name_led, "red") == EQUAL)
        {
            // LED 5
            result = LED5;
        }
        else if (strcasecmp(name_led, "blue") == EQUAL)
        {
            // LED 6
            result = LED6;
        }
    }
    
    return result;
}

/*End file*/
