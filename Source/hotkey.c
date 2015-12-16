/*
 * Date: 12/12/2015
 * Writter: Loc Pham
 * Description: This file contains function implementations for hotkey identification
 */

#include "hotkey.h"
#include <string.h>

char* HotKey_IsExisted(char* str, char hot_key)
{
    char key_str[2];
    key_str[0] = hot_key;
    key_str[1] = '\0';
    
    return (char*)strstr(str, key_str);
}

/* End of file */
