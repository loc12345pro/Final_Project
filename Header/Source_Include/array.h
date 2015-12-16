/*
 * Date: 11/12/2015
 * Writter: Loc Pham
 * Description: This file contains function declarations for array
 */

#ifndef _ARRAY_H
#define _ARRAY_H 
 
// Include header files
#include "stm32f4xx.h"

// Define macros

// Define structs

// Public functions declarations
/*
 * Name: Array_Uint16_ShiftLeft
 * Module: Queue
 * Parameters: array (uint16_t[])
 *             index (uint16_t)
 * Description: Shift left array at index position
 * Return: void
 */
void Array_Uint16_ShiftLeft(uint16_t array[], uint16_t size, uint16_t index);

#endif

/* End of file */
