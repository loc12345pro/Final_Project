/*
 * Date: 12/12/2015
 * Writter: Loc Pham
 * Description: This file contains function implementations for cmd identification
 */

// Include header files
#include "cmd.h"
#include "hotkey.h"
#include <string.h>

// Implement functions
uint8_t CMD_IsValid(char* cmd_str)
{
    uint8_t result = 0u;
    if (cmd_str != NULL)
    {
        char* pointer_str = HotKey_IsExisted(cmd_str, ENTER);
        // Check normal case
        if (HotKey_IsExisted(cmd_str, ESC) != NULL || (pointer_str != NULL && 
            (pointer_str - cmd_str + strlen(pointer_str)) == strlen(cmd_str)))
        {
            result = 1;
        }   
    }
    
    return result;
}

void CMD_RemoveEnter(char* cmd_str)
{
    if (cmd_str != NULL)
    {
        cmd_str[strlen(cmd_str) - 1] = '\0';
    }
}

/* End of file */
