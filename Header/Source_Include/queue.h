/*
 * Date: 11/12/2015
 * Writter Loc Pham
 * Description: This file contains function declarations for queue
 */

#ifndef _QUEUE_H
#define _QUEUE_H

// Include header files
#include <stm32f4xx.h>

// Define macros

// Define struct
typedef struct
{
    uint16_t* p_array;
    uint16_t array_size;
    uint16_t queue_size;
} queue_t;

// Declare function prototypes
/*
 * Name: Queue_StructInit
 * Module: Queue
 * Parameters: queue (queue_t*)
 * Description: Struct initialization. Struct will receive default values
 * Return: void
 */
void Queue_StructInit(queue_t* queue);

// Declare function prototypes
/*
 * Name: Queue_Clear
 * Module: Queue
 * Parameters: queue (queue_t*)
 * Description: Clear queue
 * Return: void
 */
void Queue_Clear(queue_t* queue);

/*
 * Name: Queue_Create
 * Module: Queue
 * Parameters: size (uint16_t)
 * Description: Create a queue
 * Return: void
 */
queue_t Queue_Create(uint16_t size);

/*
 * Name: Queue_Peek
 * Module: Queue
 * Parameters: queue (queue_t*)
 * Description: Show front value. This value won't be deleted
 * Return: void
 */
uint16_t Queue_Peek(queue_t* queue);

/*
 * Name: Queue_PeekUint16s
 * Module: Queue
 * Parameters: queue (queue_t*)
 *             array (uint16_t*)
 *             size (uint16_t)
 * Description: Peek all uint16 items
 * Return: void
 */
void Queue_PeekUint16s(queue_t* queue, uint16_t* array, uint16_t size);

/*
 * Name: Queue_PeekStr
 * Module: Queue
 * Parameters: queue (queue_t*)
 *             str (uint16_t*)
 *             str_size (uint16_t)
 * Description: Peek all char items
 * Return: void
 */
void Queue_PeekStr(queue_t* queue, char* str, uint16_t str_size);

/*
 * Name: Queue_Pop
 * Module: Queue
 * Parameters: queue (queue_t*)
 * Description: Delete front value out of queue
 * Return: void
 */
void Queue_Pop(queue_t* queue);

/*
 * Name: Queue_Push
 * Module: Queue
 * Parameters: queue (queue_t*)
 *             data (uint16_t)
 * Description: Push data to the botton of queue
 * Return: void
 */
void Queue_Push(queue_t* queue, uint16_t data);

/*
 * Name: Queue_PushUint16s
 * Module: Queue
 * Parameters: queue (queue_t*)
 *             data (uint16_t*)
 *             size (uint16_t)
 * Description: Push array of uint16_t
 * Return: void
 */
void Queue_PushUint16s(queue_t* queue, uint16_t* data, uint16_t size);

/*
 * Name: Queue_PushStr
 * Module: Queue
 * Parameters: queue (queue_t*)
 *             data (char*)
 *             data_size (uint16_t)
 * Description: Push array of char
 * Return: void
 */
void Queue_PushStr(queue_t* queue, char* data, uint16_t data_size);

/*
 * Name: Queue_IsEmpty
 * Module: Queue
 * Parameters: queue (queue_t*)
 * Description: Check if queue is empty or not
 *              1 = queue is empty
 *              0 = queue is not empty
 * Return: void
 */
uint8_t Queue_IsEmpty(queue_t* queue);

/*
 * Name: Queue_Destroy
 * Module: Queue
 * Parameters: queue (queue_t*)
 * Description: Destroy queue. This function MUST be called after not using queue
 * Return: void
 */
void Queue_Destroy(queue_t* queue);

/*
 * Name: Queue_IsInitialized
 * Module: Queue
 * Parameters: queue (queue_t*)
 * Description: Check if queue is iniitialized or not
 *              Note: An initialized queue must be:
 *                  1. queue != NULL
 *                  2. queue->p_array != NULL
 *                  3. queue->array_size > 0
 *                  4. queue->queue_size <= queue->array_size
 * Return: uint8_t
 */
uint8_t Queue_IsInitialized(queue_t* queue);

/*
 * Name: Queue_IsInitialized
 * Module: Queue
 * Parameters: queue (queue_t*)
 * Description: Check if queue is full or not
 * Return: uint8_t
 */
uint8_t Queue_IsFull(queue_t* queue);

#endif

/* End of file */
