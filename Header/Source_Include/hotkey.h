/*
 * Date: 12/12/2015
 * Writter: Loc Pham
 * Description: This file contains functions prototypes for hotkey identification
 */

#ifndef _HOTKEY_H
#define _HOTKEY_H

// Include header files
#include "stm32f4xx.h"

// Declare macros
#define ENTER 0x0D
#define ESC 0x1B

// Declare structs

// Declare function prototypes
/*
 * Name: HotKey_IsExisted
 * Module: hotkey
 * Parameters: str (char*)
 *             hot_key (char)
 * Description: Check if hot key is existed in string or not
 * Return: pointer to string
 */
char* HotKey_IsExisted(char* str, char hot_key);

#endif

/* End of file */
