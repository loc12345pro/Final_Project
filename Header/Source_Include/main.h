/*
 * Date: 11/10/2015
 * Writer: Loc Pham
 * Description: Contains program prototypes
 */
 
#ifndef _MAIN_H
#define _MAIN_H

// Include header files
#include "stm32f4xx.h"
#include "uart.h"
#include "led.h"
#include "system.h"
#include "spi.h"
#include "stm32f4_discovery.h"
#include "queue.h"
#include "cmd.h"
#include "common.h"
#include "hotkey.h"
#include "expr_eval.h"
#include <stdio.h>

// Macros
// USART Macros
#define USART_TYPE USART3
#define USART_Tx GPIO_Pin_10
#define USART_Rx GPIO_Pin_11
#define USART_PIN_PORT GPIOB

#define USART_BAUDRATE 9600u
#define USART_HARDWARE_FLOW_CONTROL USART_HardwareFlowControl_None
#define USART_MODE (USART_Mode_Rx | USART_Mode_Tx)
#define USART_PARITY USART_Parity_No
#define USART_STOP_BITS USART_StopBits_1
#define USART_WORD_LENGTH USART_WordLength_8b

// QUEUE Macros
#define QUEUE_SIZE 150u

// Program macros
#define MENU_SIZE 150u

// CMD size
#define CMD_SIZE 50u

// Error size
#define ERROR_SIZE 50u

// Option 3 CMD check count
#define OPTION3_CMD_CHECK_COUNT 2u

// CMD result
#define CMD_RESULT_SIZE 150u

// Define enum
typedef enum
{
    Menu,
    Option1,
    Option2,
    Option2_1,
    Option3,
    Option3_1,
    Option4,
    Option4_1,
    Option4_2,
    Option4_3,
    Option5,
    Unknown
} program_status_e;

typedef enum
{
    Error,
    Done
} cmd_status_e;

// Function declarations
/*
 * Name: USART_Configure
 * Module: Program
 * Parameters:  usart (usart_t*)
 * Description: USART configuration
 * Return: void
 */
void USART_Configure(usart_t* usart);

/*
 * Name: USART3_IRQHandler
 * Module: Program
 * Parameters:  None
 * Description: Tx and Rx handler
 * Return: void
 */
void USART3_IRQHandler(void);

/*
 * Name: Menu_CreateStr
 * Module: Program
 * Parameters:  menu_str (char*)
 * Description: Create menu string
 * Return: void
 */
void Menu_CreateStr(char* menu_str);

/*
 * Name: StudentInfo_CreateStr
 * Module: Program
 * Parameters:  info_str (char*)
 * Description: Create student info string
 * Return: void
 */
void StudentInfo_CreateStr(char* info_str);

/*
 * Name: MathExprInform_CreateStr
 * Module: Program
 * Parameters:  inform_str (char*)
 * Description: Create math expression inform string
 * Return: void
 */
void MathExprInform_CreateStr(char* inform_str);

/*
 * Name: MathExpr_CreateStr
 * Module: Program
 * Parameters:  info_str (char*)
 * Description: Create math expression result string
 * Return: void
 */
void Unknown_CreateStr(char* unknown_cmd);

/*
 * Name: Status_CmdCheck
 * Module: Program
 * Parameters:  cmd_str (char*)
 *              cur_stat (program_status_t)
 * Description: Check for status of program depending on cmd_str
 * Return: program_status_t
 */
program_status_e Status_CmdCheck(char* cmd_str, program_status_e cur_stat);

/*
 * Name: Status_CmdCheckMenu
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for menu
 * Return: program_status_t
 */
program_status_e Status_CmdCheckMenu(char* cmd_str);

/*
 * Name: Status_CmdCheckOption1
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 1
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption1(char* cmd_str);

/*
 * Name: Status_CmdCheckOption2
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 2
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption2(char* cmd_str);

/*
 * Name: Status_CmdCheckOption3
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 3
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption3(char* cmd_str);

/*
 * Name: Status_CmdCheckOption4
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 4
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption4(char* cmd_str);

/*
 * Name: Status_CmdCheckOption5
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 5
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption5(char* cmd_str);

/*
 * Name: Status_CmdCheckOption41
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 4 - suboption 1
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption41(char* cmd_str);

/*
 * Name: Status_CmdCheckOption42
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 4 - suboption 2
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption42(char* cmd_str);

/*
 * Name: Status_CmdCheckOption43
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 4 - suboption 3
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption43(char* cmd_str);

/*
 * Name: Status_ExecuteCmd
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Execute command
 * Return: void
 */
void Status_ExecuteCmd(char* cmd_str, program_status_e stat, char* result_cmd);

/*
 * Name: CMD_IsOption3Valid
 * Module: Program
 * Parameters: cmd_str (char*)
 * Description: Check if cmd is valid or not
 *              An valid cmd is:
 *                  + First word must be 'on' or 'off'
 *                  + Second word must be 'green', 'blue', 'red', 'orange'
 * Return: uint8_t
 *          1 means cmd is valid
 *          0 means cmd is invalid
 */
uint8_t CMD_IsOption3Valid(char* cmd_str);

/*
 * Name: MathExpr_CreateStr
 * Module: Program
 * Parameters:  info_str (char*)
 * Description: Create math expression result string
 * Return: void
 */
void MathExpr_CreateStr(char* cmd_str, char* expr_result);

/*
 * Name: Status_CmdCheckOption21
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 2 - suboption 1
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption21(char* cmd_str);

/*
 * Name: Status_CmdCheckOption31
 * Module: Program
 * Parameters:  cmd_str (char*)
 * Description: Check for status of program depending on cmd_str for option 3 - suboption 1
 * Return: program_status_t
 */
program_status_e Status_CmdCheckOption31(char* cmd_str);

/*
 * Name: BasicLed_CreateStr
 * Module: Program
 * Parameters:  info_str (char*)
 * Description: Create basic led result string
 * Return: void
 */
void BasicLed_CreateStr(char* cmd_str, char* expr_result);

/*
 * Name: BasicLedInform_CreateStr
 * Module: Program
 * Parameters:  result_cmd (char*)
 * Description: Create basic led inform string
 * Return: void
 */
void BasicLedInform_CreateStr(char* result_cmd);

#endif
/*End file*/
