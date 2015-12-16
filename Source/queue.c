/*
 * Date: 11/12/2015
 * Writter: Loc Pham
 * Description: This file contains function implementations for queue
 */

// Include header files
#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "string_manipulator.h"

// Function impelementations
void Queue_StructInit(queue_t* queue)
{
    if (queue != NULL)
    {
        memset(queue, 0, sizeof(queue_t));
    }
}

void Queue_Clear(queue_t* queue)
{
    if (Queue_IsInitialized(queue))
    {
        memset(queue->p_array, 0, queue->array_size);
        queue->queue_size = 0u;
    }
}

queue_t Queue_Create(uint16_t size)
{
    queue_t result;
    Queue_StructInit(&result);
    
    if (size > 0)
    {
        result.array_size = size;
        result.queue_size = 0u;
        result.p_array = (uint16_t*)calloc(size, sizeof(uint16_t));
    }
    
    return result;
}

uint16_t Queue_Peek(queue_t* queue)
{
    uint16_t result = 0;
    
    if (queue != NULL && queue->p_array != NULL)
    {
        result = queue->p_array[0];
    }
    
    return result;
}

void Queue_PeekUinit16s(queue_t* queue, uint16_t* array, uint16_t size)
{
    uint16_t counter = 0u;
    if (Queue_IsInitialized(queue) && array != NULL && size > 0)
    {
        uint16_t actual_size = (queue->queue_size >= size) ? size : queue->queue_size;
        memset(array, 0, size);
        
        for (; counter < actual_size; counter++)
        {
            array[counter] = queue->p_array[counter];
        }
    }
}

void Queue_PeekStr(queue_t* queue, char* str, uint16_t str_size)
{
    if (Queue_IsInitialized(queue) && str != NULL && str_size > 0u)
    {
        uint16_t* array_data = calloc(str_size, sizeof(uint16_t));
        
        Queue_PeekUinit16s(queue, array_data, str_size);
        uint16_array_to_string(array_data, str_size, str, &str_size);
        free(array_data);
    }
}

void Queue_Pop(queue_t* queue)
{
    if (queue != NULL && queue->queue_size > 0)
    {
        Array_Uint16_ShiftLeft(queue->p_array, queue->queue_size, 0u);
        queue->queue_size--;
    }
}

void Queue_Push(queue_t* queue, uint16_t data)
{
    if (queue != NULL)
    {
        uint16_t queue_size = queue->queue_size;
        if (!Queue_IsFull(queue))
        {
            queue->p_array[queue_size] = data;
            queue->queue_size++;
        }
    }
}

void Queue_PushUint16s(queue_t* queue, uint16_t* data, uint16_t size)
{
    if (Queue_IsInitialized(queue) && data != NULL && size > 0)
    {
        uint16_t counter = 0u;
        for (; counter < size && !Queue_IsFull(queue); counter++)
        {
            Queue_Push(queue, data[counter]);
        }
    }
}

void Queue_PushStr(queue_t* queue, char* data, uint16_t data_size)
{
    if (Queue_IsInitialized(queue) && data != NULL && data_size > 0u)
    {
        uint16_t* conv_data = calloc(data_size, sizeof(uint16_t));
    
        string_to_uint16_array(data, data_size, conv_data, &data_size);
        Queue_PushUint16s(queue, conv_data, data_size);
        
        free(conv_data);
    }
}

uint8_t Queue_IsEmpty(queue_t* queue)
{
    uint8_t result = 1;
    
    if (queue != NULL && queue->queue_size > 0)
    {
        result = 0;
    }
    
    return result;
}

void Queue_Destroy(queue_t* queue)
{
    if (queue != NULL && queue->p_array != NULL)
    {
        free(queue->p_array);
        Queue_StructInit(queue);
    }
}

uint8_t Queue_IsInitialized(queue_t* queue)
{
    uint8_t result = 0;
    
    if (queue != NULL && queue->p_array != NULL && 
        queue->array_size > 0 && queue->queue_size <= queue->array_size)
    {
        result = 1;
    }
    
    return result;
}

uint8_t Queue_IsFull(queue_t* queue)
{
    uint8_t result = 0;
    
    if (queue != NULL && queue->array_size == queue->queue_size)
    {
        result = 1;
    }
    
    return result;
}

/* End of file */
