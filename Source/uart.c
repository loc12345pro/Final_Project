/*
 * Date: 17/10/2015
 * Writer: Loc Pham
 * Decription: Implement function prototypes
 */
 
// Include header files
#include "uart.h"
#include "gpio.h"
#include <stdlib.h>

uint8_t USART_IsSentComplete(USART_TypeDef* UARTx)
{
    uint8_t result = 0u;
    if (UARTx != 0)
    {
        result = (UARTx->SR & TC_BIT) >> TC_SHIFT_LEFT;
    }
    
    return result;
}

uint8_t USART_IsReceivedComplete(USART_TypeDef* UARTx)
{
    uint8_t result = 0u;
    if (UARTx != 0)
    {
        result = (UARTx->SR & RXNE_BIT) >> RXNE_SHIFT_LEFT;
    }
    
    return result;
}

void USART_MySendData(USART_TypeDef* USARTx, uint16_t data)
{
    if (USARTx != 0)
    {
        USART_SendData(USARTx, data);
    
        while (!(USART_IsSentComplete(USARTx) == 1))
        {
            // Do nothing
        }
    }
}

uint16_t USART_MyReceiveData(USART_TypeDef* USARTx)
{
    uint16_t data = 0u;
    if (USARTx != 0)
    {
        while (!(USART_IsReceivedComplete(USARTx) == 1))
        {
            // Do nothing
        }
    
        data = USART_ReceiveData(USARTx);
    }
    return data;
}

void USART_MySendDataStr(USART_TypeDef* USARTx, uint16_t* data_str, uint16_t str_length)
{
    uint16_t counter = 0u;
    if (USARTx != 0 && data_str != 0)
    {
        for (; counter < str_length; counter++)
        {
            USART_MySendData(USARTx, data_str[counter]);
        }
    }
}

void USART_MyReceiveDataStr(USART_TypeDef* USARTx, uint16_t* data_str, uint16_t str_length)
{
    uint16_t counter = 0u;
    if (USARTx != 0 && data_str != 0 && str_length != 0)
    {
        memset(data_str, 0, str_length);
        for (; counter < str_length; counter++)
        {
            data_str[counter] = USART_MyReceiveData(USARTx);
        }
    }
}

void USART_MySendStr(USART_TypeDef* USARTx, char* data_str, uint16_t data_size)
{
    if (USARTx != NULL && data_str != NULL && data_size > 0u)
    {
        uint16_t* conv_data_str = calloc(data_size, sizeof(uint16_t));
        string_to_uint16_array(data_str, data_size, conv_data_str, &data_size);
        
        USART_MySendDataStr(USARTx, conv_data_str, data_size);
        free(conv_data_str);
    }
}

void USART_MyInit(usart_t* usart)
{
    if (usart != NULL)
    {
        // Enable peripheral clock for USART3
        USART_EnableClock(usart->usart_type);
        
        // Init GPIO Tx and Rx pin
        GPIO_MyInit(&(usart->tx_pin));
        GPIO_MyInit(&(usart->rx_pin));
        
        // Connect the pin to the desired peripherals' Alternate Function (AF)
        USART_ConnectPinsToAF(usart);
        
        // Program the Baud Rate, Word Length , Stop Bit, Parity, Hardware flow 
        // control and Mode(Receiver/Transmitter)
        USART_Init(usart->usart_type, &(usart->config));
        
        // Enable USART3
        USART_Cmd(usart->usart_type, ENABLE);
    }
}

void USART_EnableClock(USART_TypeDef* usart_type)
{
    if (usart_type != NULL)
    {
        if (usart_type == USART1)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        }
        else if (usart_type == USART2)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        }
        else if (usart_type == USART3)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        }
        else if (usart_type == UART4)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
        }
        else if (usart_type == UART5)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
        }
        else if (usart_type == USART6)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
        }
        else
        {
            // Do nothing
        }
    }
}

void USART_ConnectPinsToAF(usart_t* usart)
{
    if (usart != NULL)
    {
        GPIO_TypeDef* tx_port = usart->tx_pin.gpio_port;
        GPIO_TypeDef* rx_port = usart->rx_pin.gpio_port;
        uint8_t tx_pin_source = GPIO_ToGPIOPinSource(usart->tx_pin.gpio_pin);
        uint8_t rx_pin_source = GPIO_ToGPIOPinSource(usart->rx_pin.gpio_pin);
        
        if (usart->usart_type == USART1)
        {
            GPIO_PinAFConfig(tx_port, tx_pin_source, GPIO_AF_USART1);
            GPIO_PinAFConfig(rx_port, rx_pin_source, GPIO_AF_USART1);
        }
        else if (usart->usart_type == USART2)
        {
            GPIO_PinAFConfig(tx_port, tx_pin_source, GPIO_AF_USART2);
            GPIO_PinAFConfig(rx_port, rx_pin_source, GPIO_AF_USART2);
        }
        else if (usart->usart_type == USART3)
        {
            GPIO_PinAFConfig(tx_port, tx_pin_source, GPIO_AF_USART3);
            GPIO_PinAFConfig(rx_port, rx_pin_source, GPIO_AF_USART3);
        }
        else if (usart->usart_type == UART4)
        {
            GPIO_PinAFConfig(tx_port, tx_pin_source, GPIO_AF_UART4);
            GPIO_PinAFConfig(rx_port, rx_pin_source, GPIO_AF_UART4);
        }
        else if (usart->usart_type == UART5)
        {
            GPIO_PinAFConfig(tx_port, tx_pin_source, GPIO_AF_UART5);
            GPIO_PinAFConfig(rx_port, rx_pin_source, GPIO_AF_UART5);
        }
        else if (usart->usart_type == USART6)
        {
            GPIO_PinAFConfig(tx_port, tx_pin_source, GPIO_AF_USART6);
            GPIO_PinAFConfig(rx_port, rx_pin_source, GPIO_AF_USART6);
        }
        else
        {
            // Do nothing
        }
    }
}

IRQn_Type USART_FindIRQChannel(USART_TypeDef* usart_type)
{
    // Get default value result
    IRQn_Type result = USART1_IRQn;
    
    if (usart_type != NULL)
    {
        if (usart_type == USART1)
        {
            result = USART1_IRQn;
        }
        else if (usart_type == USART2)
        {
            result = USART2_IRQn;
        }
        else if (usart_type == USART3)
        {
            result = USART3_IRQn;
        }
        else if (usart_type == UART4)
        {
            result = UART4_IRQn;
        }
        else if (usart_type == UART5)
        {
            result = UART5_IRQn;
        }
        else if (usart_type == USART6)
        {
            result = USART6_IRQn;
        }
        else
        {
            // Do nothing
        }
    }
    
    return result;
}

void USART_Interrupt_MyInit(usart_t* usart, uint16_t interrupt_mode, uint8_t priority, uint8_t subpriority)
{    
    if (usart != NULL)
    {
        // Preprations
        NVIC_InitTypeDef nvic_init;
        memset(&nvic_init, 0, sizeof(NVIC_InitTypeDef));
    
        USART_MyInit(usart);
        
        // Enable Receive data register not empty
        USART_ITConfig(usart->usart_type, interrupt_mode, ENABLE);
        
        // Initialize NVIC
        nvic_init.NVIC_IRQChannel = USART_FindIRQChannel(usart->usart_type);
        nvic_init.NVIC_IRQChannelCmd = ENABLE;
        nvic_init.NVIC_IRQChannelPreemptionPriority = priority;
        nvic_init.NVIC_IRQChannelSubPriority = subpriority;
        NVIC_Init(&nvic_init);
    }
}

/* End file */
