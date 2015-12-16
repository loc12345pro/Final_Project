/*
 * Date: 17/10/2015
 * Writter: Loc Pham
 * Description: Declare function prototypes for text processing
 */

#ifndef _STRING_MANIPULATOR_
#define _STRING_MANIPULATOR_

// Include header files
#include "stm32f4xx.h"
#include <string.h>

// PUBLIC FUNCTION PROTOTYPES

/*
 * Name: string_to_uint16_array
 * Module: Led
 * Parameters:  str (char*)
                data (uint16_t*)
                data_length (uint16_t*)
 * Description: Convert from string to uint16 array
 * Return: void
 */
void string_to_uint16_array(char* str, uint16_t str_size, uint16_t* data, uint16_t* data_length);

/*
 * Name: uint16_array_to_string
 * Module: Led
 * Parameters:  str (char*)
                data (uint16_t*)
                data_length (uint16_t*)
 * Description: Convert from uint16 array to string
 * Return: void
 */
void uint16_array_to_string(uint16_t* data, uint16_t data_length, char* str, uint16_t* str_size);

#endif
/* End file */
