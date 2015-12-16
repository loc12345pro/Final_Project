/*
 * Date: 29/10/2015
 * Writter: Loc Pham
 * Description: This file contains function implementations concerned with GPIO
 */

#include "gpio.h"
#include <string.h>

void GPIO_EnableClock(GPIO_TypeDef* GPIOx)
{
    if (GPIOx == GPIOA)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    }
    else if (GPIOx == GPIOF)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    }
    else if (GPIOx == GPIOG)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    }
    else if (GPIOx == GPIOH)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    }
    else if (GPIOx == GPIOI)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
    }
    else 
    {
        // End searching for GPIO port
    }
}

uint8_t GPIO_ToGPIOPinSource(uint16_t gpio_pin)
{
    uint8_t result = GPIO_PinSource0;
    switch (gpio_pin)
    {
        case GPIO_Pin_0:
            result = GPIO_PinSource0;
            break;
        case GPIO_Pin_1:
            result = GPIO_PinSource1;
            break;
        case GPIO_Pin_2:
            result = GPIO_PinSource2;
            break;
        case GPIO_Pin_3:
            result = GPIO_PinSource3;
            break;
        case GPIO_Pin_4:
            result = GPIO_PinSource4;
            break;
        case GPIO_Pin_5:
            result = GPIO_PinSource5;
            break;
        case GPIO_Pin_6:
            result = GPIO_PinSource6;
            break;
        case GPIO_Pin_7:
            result = GPIO_PinSource7;
            break;
        case GPIO_Pin_8:
            result = GPIO_PinSource8;
            break;
        case GPIO_Pin_9:
            result = GPIO_PinSource9;
            break;
        case GPIO_Pin_10:
            result = GPIO_PinSource10;
            break;
        case GPIO_Pin_11:
            result = GPIO_PinSource11;
            break;
        case GPIO_Pin_12:
            result = GPIO_PinSource12;
            break;
        case GPIO_Pin_13:
            result = GPIO_PinSource13;
            break;
        case GPIO_Pin_14:
            result = GPIO_PinSource14;
            break;
        case GPIO_Pin_15:
            result = GPIO_PinSource15;
            break;
        default:
            // Do nothing
            break;
    }
    
    return result;
}

uint16_t GPIO_ToGPIOPin(uint8_t gpio_pin_source)
{
    uint16_t result = GPIO_Pin_0;
    switch (gpio_pin_source)
    {
        case GPIO_PinSource0:
            result = GPIO_Pin_0;
            break;
        case GPIO_PinSource1:
            result = GPIO_Pin_1;
            break;
        case GPIO_PinSource2:
            result = GPIO_Pin_2;
            break;
        case GPIO_PinSource3:
            result = GPIO_Pin_3;
            break;
        case GPIO_PinSource4:
            result = GPIO_Pin_4;
            break;
        case GPIO_PinSource5:
            result = GPIO_Pin_5;
            break;
        case GPIO_PinSource6:
            result = GPIO_Pin_6;
            break;
        case GPIO_PinSource7:
            result = GPIO_Pin_7;
            break;
        case GPIO_PinSource8:
            result = GPIO_Pin_8;
            break;
        case GPIO_PinSource9:
            result = GPIO_Pin_9;
            break;
        case GPIO_PinSource10:
            result = GPIO_Pin_10;
            break;
        case GPIO_PinSource11:
            result = GPIO_Pin_11;
            break;
        case GPIO_PinSource12:
            result = GPIO_Pin_12;
            break;
        case GPIO_PinSource13:
            result = GPIO_Pin_13;
            break;
        case GPIO_PinSource14:
            result = GPIO_Pin_14;
            break;
        case GPIO_PinSource15:
            result = GPIO_Pin_15;
            break;
        default: 
            // Do nothing
            break;
    }
    
    return result;
}

void GPIO_MyInit(gpio_pin_t* gpio_pin)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if (gpio_pin != NULL)
    {
        // Preparations
        memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitTypeDef));
        GPIO_StructInit(&GPIO_InitStruct);
        
        GPIO_EnableClock(gpio_pin->gpio_port);
        
        GPIO_InitStruct.GPIO_Mode = (gpio_pin->gpio_init).gpio_mode;
        GPIO_InitStruct.GPIO_OType = (gpio_pin->gpio_init).gpio_otype;
        GPIO_InitStruct.GPIO_Pin = gpio_pin->gpio_pin;
        GPIO_InitStruct.GPIO_PuPd = (gpio_pin->gpio_init).gpio_pupd;
        GPIO_InitStruct.GPIO_Speed = (gpio_pin->gpio_init).gpio_speed;
        GPIO_Init(gpio_pin->gpio_port, &GPIO_InitStruct);
    }
}

/* End file */
