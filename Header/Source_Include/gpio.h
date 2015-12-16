/*
 * Date: 29/10/2015
 * Writter: Loc Pham
 * Description: This is expansion of file stm3f4xx_gpio.h, contains function prototypes
 */

#ifndef _GPIO_H
#define _GPIO_H

// Include header files
#include "stm32f4xx.h"

// Define MACROs

// Define structs
typedef struct
{
    GPIOMode_TypeDef gpio_mode;
    GPIOOType_TypeDef gpio_otype;
    GPIOPuPd_TypeDef gpio_pupd;
    GPIOSpeed_TypeDef gpio_speed;
} gpio_init_t;

typedef struct
{
    GPIO_TypeDef* gpio_port;
    uint16_t gpio_pin;
    gpio_init_t gpio_init;
} gpio_pin_t;

// PUBLIC FUNCTION PROTOTYPES
/*
 * Name: GPIO_EnableClock
 * Module: GPIO
 * Parameters:  GPIOx (GPIO_TypeDef*)
 * Description: Enable clock for particular GPIOx
 * Return: void
 */
void GPIO_EnableClock(GPIO_TypeDef* GPIOx);

/*
 * Name: GPIO_ToGPIOPinSource
 * Module: GPIO
 * Parameters:  gpio_pin (uint16_t)
 *  | GPIO_Pin_0 -> 0x0001  | GPIO_Pin_1 -> 0x0002  | GPIO_Pin_2 -> 0x0004  |
 *  | GPIO_Pin_3 -> 0x0008  | GPIO_Pin_4 -> 0x0010  | GPIO_Pin_5 -> 0x0020  |
 *  | GPIO_Pin_6 -> 0x0040  | GPIO_Pin_7 -> 0x0080  | GPIO_Pin_8 -> 0x0100  |
 *  | GPIO_Pin_9 -> 0x0200  | GPIO_Pin_10 -> 0x0400 | GPIO_Pin_11 -> 0x0800 |
 *  | GPIO_Pin_12 -> 0x1000 | GPIO_Pin_13 -> 0x2000 | GPIO_Pin_14 -> 0x4000 |
 *  | GPIO_Pin_15 -> 0x8000 | 
 * Description: Convert GPIO Pin to GPIO Pin Source
 * Return: uint8_t 
 *  | GPIO_PinSource0 -> 0x00  | GPIO_PinSource1 -> 0x01  | GPIO_PinSource2 -> 0x02  |
 *  | GPIO_PinSource3 -> 0x03  | GPIO_PinSource4 -> 0x04  | GPIO_PinSource5 -> 0x05  |
 *  | GPIO_PinSource6 -> 0x06  | GPIO_PinSource7 -> 0x07  | GPIO_PinSource8 -> 0x08  |
 *  | GPIO_PinSource9 -> 0x09  | GPIO_PinSource10 -> 0x0A | GPIO_PinSource11 -> 0x0B |
 *  | GPIO_PinSource12 -> 0x0C | GPIO_PinSource13 -> 0x0D | GPIO_PinSource14 -> 0x0E |
 *  | GPIO_PinSource15 -> 0x0F |
 */
uint8_t GPIO_ToGPIOPinSource(uint16_t gpio_pin);

/*
 * Name: GPIO_ToPinSource
 * Module: GPIO
 * Parameters:  gpio_pin_source (uint8_t)
 *  | GPIO_PinSource0 -> 0x00  | GPIO_PinSource1 -> 0x01  | GPIO_PinSource2 -> 0x02  |
 *  | GPIO_PinSource3 -> 0x03  | GPIO_PinSource4 -> 0x04  | GPIO_PinSource5 -> 0x05  |
 *  | GPIO_PinSource6 -> 0x06  | GPIO_PinSource7 -> 0x07  | GPIO_PinSource8 -> 0x08  |
 *  | GPIO_PinSource9 -> 0x09  | GPIO_PinSource10 -> 0x0A | GPIO_PinSource11 -> 0x0B |
 *  | GPIO_PinSource12 -> 0x0C | GPIO_PinSource13 -> 0x0D | GPIO_PinSource14 -> 0x0E |
 *  | GPIO_PinSource15 -> 0x0F |
 * Description: Convert GPIO Pin to GPIO Pin Source
 * Return: uint16_t 
 *  | GPIO_Pin_0 -> 0x0001  | GPIO_Pin_1 -> 0x0002  | GPIO_Pin_2 -> 0x0004  |
 *  | GPIO_Pin_3 -> 0x0008  | GPIO_Pin_4 -> 0x0010  | GPIO_Pin_5 -> 0x0020  |
 *  | GPIO_Pin_6 -> 0x0040  | GPIO_Pin_7 -> 0x0080  | GPIO_Pin_8 -> 0x0100  |
 *  | GPIO_Pin_9 -> 0x0200  | GPIO_Pin_10 -> 0x0400 | GPIO_Pin_11 -> 0x0800 |
 *  | GPIO_Pin_12 -> 0x1000 | GPIO_Pin_13 -> 0x2000 | GPIO_Pin_14 -> 0x4000 |
 *  | GPIO_Pin_15 -> 0x8000 | 
 */
uint16_t GPIO_ToGPIOPin(uint8_t gpio_pin_source);

/*
 * Name: GPIO_MyInit
 * Module: GPIO
 * Parameters:  gpio_pin (gpio_pin_t*)
 * Description: Initialize GPIO pin (variable references of gpio_pin won't be affected)
 * Return: void
 */
void GPIO_MyInit(gpio_pin_t* gpio_pin);

#endif
/* End file */
