/*
 * Date: 17/10/2015
 * Writter: Loc Pham
 * Description: Implement function prototypes
 */

#include "string_manipulator.h"
#include "stdio.h"

void string_to_uint16_array(char* str, uint16_t str_size, uint16_t* data, uint16_t* data_length)
{
    uint16_t counter = 0u;
    if (str != NULL && data != NULL && data_length != NULL && *data_length > 0)
    {
        memset(data, 0, *data_length);
        *data_length = (str_size > *data_length) ? *data_length : str_size;
        
        for (; counter < *data_length; counter++)
        {
            data[counter] = (uint16_t) str[counter];
        }
    }
}

void uint16_array_to_string(uint16_t* data, uint16_t data_length, char* str, uint16_t* str_size)
{
    uint16_t counter = 0u;
    if (data != NULL && data_length > 0 && str != NULL)
    {
        memset(str, 0, *str_size);
        
        *str_size = (data_length > *str_size) ? *str_size : data_length;
        for (; counter < *str_size; counter++)
        {
            str[counter] = (char)data[counter];
        }
    }
}

/* End file */
