/*
 * Date: 17/10/2015
 * Writter: Loc Pham
 * Description: Declare function prototype concerned with UART
 */

#ifndef _UART_H
#define _UART_H

// Include eader files
#include "stm32f4xx.h"
#include <string.h>
#include "string_manipulator.h"
#include "gpio.h"

// Define MACROS
#define TC_BIT 0x0040
#define TC_SHIFT_LEFT 6

#define RXNE_BIT 0x0020
#define RXNE_SHIFT_LEFT 5

// Struct types
typedef struct
{
    USART_TypeDef* usart_type;
    gpio_pin_t rx_pin;
    gpio_pin_t tx_pin;
    USART_InitTypeDef config;
} usart_t;

#define MAX_DATA_STR 100u
// PUBLIC PROTOTYPE FUNCTIONS
/*
 * Name: USART_IsSentComplete
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 * Description: Check if sending is complete or not
 * Return: 0 or 1
 */
uint8_t USART_IsSentComplete(USART_TypeDef* UARTx);

/*
 * Name: USART_IsReceivedComplete
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 * Description: Check if sending is complete or not
 * Return: 0 or 1
 */
uint8_t USART_IsReceivedComplete(USART_TypeDef* UARTx);

/*
 * Name: USART_MySendData
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 *              data (uint16_t)
 * Description: Send data without using interupt
 * Return: void
 */
void USART_MySendData(USART_TypeDef* USARTx, uint16_t data);

/*
 * Name: USART_MyReceiveData
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 * Description: Receive data without using interupt
 * Return: void
 */
uint16_t USART_MyReceiveData(USART_TypeDef* USARTx);

/*
 * Name: USART_MySendDataStr
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 *              data_str (uint16_t*)
 *              str_length (uint16_t)
 * Description: Send data string without using interupt
 * Return: void
 */
void USART_MySendDataStr(USART_TypeDef* USARTx, uint16_t* data_str, uint16_t str_length);

/*
 * Name: USART_MySendDataStr
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 *              data_str (uint16_t*)
 *              str_length (uint16_t)
 * Description: Receive data string without using interupt
 * Return: void
 */
void USART_MyReceiveDataStr(USART_TypeDef* USARTx, uint16_t* data_str, uint16_t str_length);

/*
 * Name: USART_MySendStr
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 *              data_str (char*)
 *              data_size (uint16_t)
 * Description: Send data char string without using interupt
 * Return: void
 */
void USART_MySendStr(USART_TypeDef* USARTx, char* data_str, uint16_t data_size);

/*
 * Name: USART_MyInit
 * Module: UART
 * Parameters: None
 * Description: Init usart widthout using interrupt (usart's reference values won't be changed)
 * Return: void
 */
void USART_MyInit(usart_t* usart);

/*
 * Name: USART_EnableClock
 * Module: UART
 * Parameters: usart_type (USART_TypeDef*)
 * Description: Enable usart's clock (usart's reference values won't be changed)
 * Return: void
 */
void USART_EnableClock(USART_TypeDef* usart_type);

/*
 * Name: USART_EnableClock
 * Module: UART
 * Parameters: None
 * Description: Connect the pin to the desired peripherals' Alternate Function (AF) 
 *              (usart's reference values won't be changed)
 * Return: void
 */
void USART_ConnectPinsToAF(usart_t* usart);

/*
 * Name: USART_FindIRQChannel
 * Module: UART
 * Parameters: None
 * Description: Find IRQ channel based on usart_type
 * Return: void
 */
IRQn_Type USART_FindIRQChannel(USART_TypeDef* usart_type);

/*
 * Name: USART_Interrupt_MyInit
 * Module: UART
 * Parameters:  usart (usart*)
 *              interrupt_mode (uint16_t)
 *              priority (uint8_t)
 *              subpriority (uint8_t)
 * Description: Init usart using interrupt (usart's reference values won't be changed)
 * Return: void
 */
void USART_Interrupt_MyInit(usart_t* usart, uint16_t interrupt_mode, uint8_t priority, uint8_t subpriority);



#endif
/* End file */

