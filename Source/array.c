/*
 * Date: 11/12/2015
 * Writter: Loc Pham
 * Description: This file contains function implementations for array
 */
 
// Include header files
#include "array.h"
#include <stdio.h>

// Function implementations
void Array_Uint16_ShiftLeft(uint16_t array[], uint16_t size, uint16_t index)
{
    if (array != NULL && size > 0 && index < size)
    {
        uint16_t counter = index;
        for (; counter < size - 1; counter++)
        {
            array[counter] = array[counter + 1];
        }
        array[size - 1] = 0u;
    }
}

/* End of file */
