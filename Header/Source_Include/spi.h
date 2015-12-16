/*
 * Date: 27/11/2015
 * Writter: Loc Pham
 * Description: This file includes header declarations for SPI
 */

// Include header files
#include "stm32f4xx.h"
#include "gpio.h"

// MACROs Declarations
#define SS_PORT_UNKNOWN NULL
#define SS_PIN_UNKNOWN GPIO_Pin_All

// Structs declarations
typedef struct
{
    SPI_TypeDef* spi_type;
    gpio_pin_t sck_pin;
    gpio_pin_t miso_pin;
    gpio_pin_t mosi_pin;
    gpio_pin_t ss_pin;
    SPI_InitTypeDef SPI_init;
} spi_t;

// Public functions
/*
 * Name: SPI_Interrupt_MyInit
 * Module: UART
 * Parameters:  SPIx (spi_t*)
 *              priority (uint8_t)
 *              subpriority (uint8_t)
 * Description: init SPI (store information for initializations)
 * Return: None
 */
void SPI_Interrupt_MyInit(spi_t* spi_format, uint8_t interrupt_mode, uint8_t priority, uint8_t subpriority);

/*
 * Name: SPI_MyInit
 * Module: UART
 * Parameters:  SPIx (spi_t*)
 * Description: init SPI (store information for initializations)
 * Return: None
 */
void SPI_MyInit(spi_t* spi_format);

/*
 * Name: SPI_MySendData
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 *              data (uint16_t)
 * Description: Send data without using interupt
 * Return: void
 */
void SPI_MySendDataOnly(SPI_TypeDef* SPIx, uint16_t data);

/*
 * Name: SPI_MyReceiveData
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 * Description: Receive data without using interupt
 * Return: void
 */
uint16_t SPI_MyReceiveDataOnly(SPI_TypeDef* SPIx);

/*
 * Name: SPI_MySendReceiveData
 * Module: UART
 * Parameters:  UARTx (USART_TypeDef*)
 *              data_send (uint16_t)
 *              data_recv (uint16_t*)
 * Description: Receive data without using interupt
 * Return: void
 */
void SPI_MySendReceiveData(SPI_TypeDef* SPIx, uint16_t data_send, uint16_t* data_recv);


/*
 * Name: SPI_EnableClock
 * Module: SPI
 * Parameters: SPIx (SPI_TypeDef*)
 * Description: Enable spi's clock
 * Return: void
 */
void SPI_EnableClock(SPI_TypeDef* SPIx);

/*
 * Name: SPI_ConnectPinsToAF
 * Module: SPI
 * Parameters: spi_format (spi_t*)
 * Description: Connect the pin to the desired peripherals' Alternate Function (AF) 
 * Return: void
 */
void SPI_ConnectPinsToAF(spi_t* spi_format);

/*
 * Name: SPI_EnableSendReceive
 * Module: SPI
 * Parameters: SPIx (SPI_TypeDef*)
 *             gpio_pin (uint16_t)
 * Description: Start sending and receiving on SPIs 
 * Return: void
 */
void SPI_EnableSendReceive(GPIO_TypeDef* gpio_port, uint16_t gpio_pin);

/*
 * Name: SPI_DisableSendReceive
 * Module: SPI
 * Parameters: SPIx (SPI_TypeDef*)
 *             gpio_pin (uint16_t)
 * Description: Stop sending and receiving on SPIs 
 * Return: void
 */
void SPI_DisableSendReceive(GPIO_TypeDef* gpio_port, uint16_t gpio_pin);

/*
 * Name: SPI_FindIRQChannel
 * Module: SPI
 * Parameters: SPIx (SPI_TypeDef*)
 *             gpio_pin (uint16_t)
 * Description: Stop sending and receiving on SPIs 
 * Return: IRQn_Type
 */
IRQn_Type SPI_FindIRQChannel(SPI_TypeDef* SPIx);

/*
 * Name: SPI_StructInit
 * Module: SPI
 * Parameters: spi_format (spi_t*)
 * Description: Start Init
 * Return: IRQn_Type
 */
void SPI_FormatInit(spi_t* spi_format);

/* End file */

