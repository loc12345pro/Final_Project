/*
 * Date: 12/12/2015
 * Writter: Loc Pham
 * Description: This file contains function declarations for CMD
 */

#ifndef _CMD_H
#define _CMD_H

// Include header files
#include "stm32f4xx.h"

// Declare macros

// Declare structs

// Declare function prototypes
/*
 * Name: CMD_IsValid
 * Module: cmd
 * Parameters: cmd_str (char*)
 * Description: Check if cmd is valid or not
 *              An valid cmd is:
 *                  + not an empty cmd
 *                  + must have 'enter' at the end of cmd
 *              Note: If cmd is ESC then it is valid without having 'enter' at the end
 * Return: uint8_t
 *          1 means cmd is valid
 *          0 means cmd is invalid
 */
uint8_t CMD_IsValid(char* cmd_str);

/*
 * Name: CMD_IsValid
 * Module: cmd
 * Parameters: cmd_str (char*)
 * Description: Remove enter at the end string
 * Return: void
 */
void CMD_RemoveEnter(char* cmd_str);

#endif

/* End of file */
