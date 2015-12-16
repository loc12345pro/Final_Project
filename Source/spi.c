/*
 * Date: 27/11/2015
 * Writter: Loc Pham
 * Description: This file contains function implementations for SPI
 */

#include "spi.h"
#include <string.h>
#include "gpio.h"

void SPI_MyInit(spi_t* spi_format)
{
    if (spi_format != NULL)
    {
        // Enable clock
        SPI_EnableClock(spi_format->spi_type);
        
        // Configure pins used by SPIx
        GPIO_MyInit(&(spi_format->sck_pin));
        GPIO_MyInit(&(spi_format->miso_pin));
        GPIO_MyInit(&(spi_format->mosi_pin));
        
        // Connect SPIx pins to SPI alternative function
        SPI_ConnectPinsToAF(spi_format);
    
        // Initialize for slave select
        if ((spi_format->ss_pin).gpio_port != SS_PORT_UNKNOWN && 
            (spi_format->ss_pin).gpio_pin != SS_PIN_UNKNOWN)
        {
            GPIO_MyInit(&(spi_format->ss_pin));
        }
        
        // Enable SPIx
        SPI_Init(spi_format->spi_type, &(spi_format->SPI_init));
        SPI_Cmd(spi_format->spi_type, ENABLE);
    }
}

void SPI_Interrupt_MyInit(spi_t* spi_format, uint8_t interrupt_mode, uint8_t priority, uint8_t subpriority)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    
    if (spi_format != NULL)
    {
        // Preparations
        memset(&NVIC_InitStruct, 0, sizeof(NVIC_InitTypeDef));
        
        // SPI Initializations
        SPI_MyInit(spi_format);
    
        // Enable interrupt
        SPI_ITConfig(spi_format->spi_type, interrupt_mode, ENABLE);
        
        // Initialize NVIC
        NVIC_InitStruct.NVIC_IRQChannel = SPI_FindIRQChannel(spi_format->spi_type);
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = priority;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = subpriority;
        NVIC_Init(&NVIC_InitStruct);
        
        SPI_Cmd(spi_format->spi_type, ENABLE);
    }
}

void SPI_EnableClock(SPI_TypeDef* SPIx)
{
    if (SPIx != NULL)
    {
        if (SPIx == SPI1)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
        }
        else if (SPIx == SPI2)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
        }
        else if (SPIx == SPI3)
        {
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
        }
        else 
        {
            // Do nothing
        }
    }
}

void SPI_ConnectPinsToAF(spi_t* spi_format)
{
    if (spi_format)
    {
        GPIO_TypeDef* sck_port = (spi_format->sck_pin).gpio_port;
        GPIO_TypeDef* mosi_port = (spi_format->mosi_pin).gpio_port;
        GPIO_TypeDef* miso_port = (spi_format->miso_pin).gpio_port;
        
        uint8_t sck_pin_source = GPIO_ToGPIOPinSource((spi_format->sck_pin).gpio_pin);
        uint8_t mosi_pin_source = GPIO_ToGPIOPinSource((spi_format->mosi_pin).gpio_pin);
        uint8_t miso_pin_source = GPIO_ToGPIOPinSource((spi_format->miso_pin).gpio_pin);
        
        if (spi_format->spi_type == SPI1)
        {
            GPIO_PinAFConfig(sck_port, sck_pin_source, GPIO_AF_SPI1);
            GPIO_PinAFConfig(mosi_port, mosi_pin_source, GPIO_AF_SPI1);
            GPIO_PinAFConfig(miso_port, miso_pin_source, GPIO_AF_SPI1);
        }
        else if (spi_format->spi_type == SPI2)
        {
            GPIO_PinAFConfig(sck_port, sck_pin_source, GPIO_AF_SPI2);
            GPIO_PinAFConfig(mosi_port, mosi_pin_source, GPIO_AF_SPI2);
            GPIO_PinAFConfig(miso_port, miso_pin_source, GPIO_AF_SPI2);
        }
        else if (spi_format->spi_type == SPI3)
        {
            GPIO_PinAFConfig(sck_port, sck_pin_source, GPIO_AF_SPI3);
            GPIO_PinAFConfig(mosi_port, mosi_pin_source, GPIO_AF_SPI3);
            GPIO_PinAFConfig(miso_port, miso_pin_source, GPIO_AF_SPI3);
        }
        else 
        {
            // Do nothing
        }
    }
}

void SPI_EnableSendReceive(GPIO_TypeDef* gpio_port, uint16_t gpio_pin)
{
    if (gpio_port != NULL)
    {
        GPIO_ResetBits(gpio_port, gpio_pin);
    }
}

void SPI_DisableSendReceive(GPIO_TypeDef* gpio_port, uint16_t gpio_pin)
{
    if (gpio_port != NULL)
    {
        GPIO_SetBits(gpio_port, gpio_pin);
    }
}

IRQn_Type SPI_FindIRQChannel(SPI_TypeDef* SPIx)
{
    IRQn_Type result = SPI1_IRQn;
    if (SPIx != NULL)
    {
        if (SPIx == SPI1)
        {
            result = SPI1_IRQn;
        }
        else if (SPIx == SPI2)
        {
            result = SPI2_IRQn;
        }
        else if (SPIx == SPI3)
        {
            result = SPI3_IRQn;
        }
        else 
        {
            // Do nothing
        }
    }
    
    return result;
}

void SPI_FormatInit(spi_t* spi_format)
{
    if (spi_format != NULL)
    {
        memset(spi_format, 0, sizeof(spi_t));
        (spi_format->SPI_init).SPI_NSS = SPI_NSS_Hard;
        (spi_format->ss_pin).gpio_port = SS_PORT_UNKNOWN;
        (spi_format->ss_pin).gpio_pin = SS_PIN_UNKNOWN;
    }
}

void SPI_MySendDataOnly(SPI_TypeDef* SPIx, uint16_t data)
{
    SPI_SendData(SPIx, data);
    
    while (SPI_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
    {
        // Do nothing
    }
}

uint16_t SPI_MyReceiveDataOnly(SPI_TypeDef* SPIx)
{
    uint16_t result = 0;
    
    while (SPI_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {
        // Do nothing
    }
    
    result = SPI_ReceiveData(SPIx);
    return result;
}

void SPI_MySendReceiveData(SPI_TypeDef* SPIx, uint16_t data_send, uint16_t* data_recv)
{
    SPI_MySendDataOnly(SPIx, data_send);
    *data_recv = SPI_MyReceiveDataOnly(SPIx);
}

/* End file */
