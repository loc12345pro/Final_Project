/*
 * Date: 10/12/2015
 * Writer: Loc Pham
 * Description: Main entry
 * Program Description:
 *      This program satisfies following requireents:
 *          1. Program will output to Hyper Terminal (HT) list of functionalities:
 *              + Student info
 *              + Basic operation
 *              + Simple led
 *              + Advanced led
 *              + Audio
 *          2. User chooses one of functionalities
 *          3. User start or input to selected functionality
 *          4. Program process and output result to board or HT
 */

// Include header files
#include "main.h"

// Global variables
// Inform strings
volatile char* g_option_inform_str = "Choose your option(1, 2,...):";
volatile char* g_line_str = "\r\n";
volatile char* g_option_1_str = "1. Student info";
volatile char* g_option_2_str = "2. Basic operation (+, -, *, /)";
volatile char* g_option_3_str = "3. Simple LED";
volatile char* g_option_4_str = "4. Advanced LED";
volatile char* g_option_5_str = "5. Audio";

// Escape string
volatile char* g_escape_str = "ESC: return previous menu";

// Cmd string
volatile char* g_cmd_str = "> ";

// Student info details
volatile char* g_student_id_str = "ID: ";
volatile char* g_student_name_str = "Full name: ";

// Main menu string
volatile char g_menu_str[MENU_SIZE];

// Queue send and receive
volatile queue_t g_queue_send;
volatile queue_t g_queue_receive;

// Usart
volatile usart_t g_usart;

// Words
volatile char* g_word_on = "On";
volatile char* g_word_off = "Off";
volatile char* g_word_green = "Green";
volatile char* g_word_blue = "Blue";
volatile char* g_word_red = "Red";
volatile char* g_word_orange = "Orange";

// Menu and option cmds
volatile char* g_cmd_one = "1\r";
volatile char* g_cmd_two = "2\r";
volatile char* g_cmd_three = "3\r";
volatile char* g_cmd_four = "4\r";
volatile char* g_cmd_five = "5\r";
volatile char* g_cmd_a = "a\r";
volatile char* g_cmd_b = "b\r";
volatile char* g_cmd_c = "c\r";
volatile char* g_cmd_r = "r\r";
volatile char* g_cmd_g = "g\r";
volatile char* g_cmd_o = "o\r";

// Data
volatile char* g_student_1_name = "Pham Phuoc Loc";
volatile char* g_student_2_name = "Le Vu Dai Yen";
volatile char* g_student_1_id = "1212216";
volatile char* g_student_2_id = "1212537";
volatile char* g_cmd_invalid = "Invalid command";
volatile char* g_expr_result = "Result: ";
volatile char* g_led_on_inform = "Turned on LED";
volatile char* g_led_off_inform = "Turned off LED";

// Main entry
int main()
{
    // Variable declarations
    char cmd_result[CMD_RESULT_SIZE];
    char cmd_buffer[CMD_SIZE];
    uint8_t cmd_buffer_index = 0u;
    uint16_t temp_data = 0;
    program_status_e prev_prog_status;
    program_status_e cur_prog_status;

    // Common initializations
    memset(cmd_result, 0, CMD_RESULT_SIZE);
    memset(cmd_buffer, 0, CMD_SIZE);
    memset((char*)g_menu_str, 0, MENU_SIZE);
    memset((usart_t*)&g_usart, 0, sizeof(usart_t));
    g_queue_send = Queue_Create(QUEUE_SIZE);
    g_queue_receive = Queue_Create(QUEUE_SIZE);
    
    // First go into menu mode
    prev_prog_status = Menu;
    cur_prog_status = Menu;
    
    // System's clock initialization
    SysClock_Init();
    
    // Led initializations
    BoardLed_Init();
    
    // Menu initialization
    Menu_CreateStr((char*)g_menu_str);
    
    // USART configuration and initialization
    USART_Configure((usart_t*)&g_usart);
    USART_Interrupt_MyInit((usart_t*)&g_usart, USART_IT_RXNE, 1u, 0u);
    
    // Push menu string to sending queue
    Queue_PushStr((queue_t*)&g_queue_send, (char*)g_menu_str, strlen((char*)g_menu_str));
    
    // Add and enable TXE interrupt
    USART_ITConfig(g_usart.usart_type, USART_IT_TXE, ENABLE);
    
    // Led_Blink
    BoardLed_Init();
    
    // Infinite loop
    for (; ; )
    {
        if (Queue_IsEmpty((queue_t*)&g_queue_send) && !Queue_IsEmpty((queue_t*)&g_queue_receive))
        {
            cmd_buffer[cmd_buffer_index++] = Queue_Peek((queue_t*)&g_queue_receive);
            if (CMD_IsValid(cmd_buffer))
            {
                // Line break
                Queue_PushStr((queue_t*)&g_queue_send, (char*)g_line_str, strlen((char*)g_line_str));
                
                // Process
                cur_prog_status = Status_CmdCheck(cmd_buffer, prev_prog_status);
                Status_ExecuteCmd(cmd_buffer, cur_prog_status, cmd_result);
                
                // Push result to send queue
                Queue_PushStr((queue_t*)&g_queue_send, cmd_result, strlen(cmd_result));
                prev_prog_status = (cur_prog_status != Unknown) ? cur_prog_status : prev_prog_status;
                
                // Initialize
                memset(cmd_buffer, 0, CMD_SIZE);
                memset(cmd_result, 0, CMD_RESULT_SIZE);
                cmd_buffer_index = 0;
                
                Queue_Clear((queue_t*)&g_queue_receive);
                
                // Enable Tx interrupt
                USART_ITConfig(g_usart.usart_type, USART_IT_TXE, ENABLE);
            }
            else 
            {
                temp_data = Queue_Peek((queue_t*)&g_queue_receive);
                Queue_Pop((queue_t*)&g_queue_receive);
                Queue_Push((queue_t*)&g_queue_send, temp_data);
                USART_ITConfig(g_usart.usart_type, USART_IT_TXE, ENABLE);
            }
        }
    }
}

void USART_Configure(usart_t* usart)
{
    // Preparations
    gpio_init_t gpio_init;
    USART_InitTypeDef usart_init;
    
    memset(&gpio_init, 0, sizeof(gpio_init_t));
    memset(&usart_init, 0, sizeof(USART_InitTypeDef));
    USART_StructInit(&usart_init);
    
    // Configure USART type
    usart->usart_type = USART_TYPE;
    
    // Configure GPIO init struct template
    gpio_init.gpio_mode = GPIO_Mode_AF;
    gpio_init.gpio_otype = GPIO_OType_PP;
    gpio_init.gpio_pupd = GPIO_PuPd_UP;
    gpio_init.gpio_speed = GPIO_Speed_50MHz;
    
    // Configure Tx pin
    (usart->tx_pin).gpio_pin = USART_Tx;
    (usart->tx_pin).gpio_port = USART_PIN_PORT;
    memcpy(&((usart->tx_pin).gpio_init), &gpio_init, sizeof(gpio_init_t));
    
    // Configure Rx pin
    (usart->rx_pin).gpio_pin = USART_Rx;
    (usart->rx_pin).gpio_port = USART_PIN_PORT;
    memcpy(&((usart->rx_pin).gpio_init), &gpio_init, sizeof(gpio_init_t));
    
    // Configure usart settings
    usart_init.USART_BaudRate = USART_BAUDRATE;
    usart_init.USART_HardwareFlowControl = USART_HARDWARE_FLOW_CONTROL;
    usart_init.USART_Mode = USART_MODE;
    usart_init.USART_Parity = USART_PARITY;
    usart_init.USART_StopBits = USART_STOP_BITS;
    usart_init.USART_WordLength = USART_WORD_LENGTH;
    
    memcpy(&(usart->config), &usart_init, sizeof(USART_InitTypeDef));
}

void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(g_usart.usart_type, USART_IT_TXE) == SET)
    {
        if (!Queue_IsEmpty((queue_t*)&g_queue_send))
        {
            uint16_t data = Queue_Peek((queue_t*)&g_queue_send);
            Queue_Pop((queue_t*)&g_queue_send);
            USART_SendData(g_usart.usart_type, data);
        }
        else 
        {
            // Disable Tx interrupt
            USART_ITConfig(g_usart.usart_type, USART_IT_TXE, DISABLE);
        }
    }
    
    if (USART_GetITStatus(g_usart.usart_type, USART_IT_RXNE) == SET)
    {
        uint16_t data = USART_ReceiveData(g_usart.usart_type);
        Queue_Push((queue_t*)&g_queue_receive, data);
    }
}

void Menu_CreateStr(char* menu_str)
{
    strcat(menu_str, (char*)g_option_inform_str);
    strcat(menu_str, (char*)g_line_str);
    
    strcat(menu_str, (char*)g_option_1_str);
    strcat(menu_str, (char*)g_line_str);
    
    strcat(menu_str, (char*)g_option_2_str);
    strcat(menu_str, (char*)g_line_str);
    
    strcat(menu_str, (char*)g_option_3_str);
    strcat(menu_str, (char*)g_line_str);
    
    strcat(menu_str, (char*)g_option_4_str);
    strcat(menu_str, (char*)g_line_str);
    
    strcat(menu_str, (char*)g_option_5_str);
    strcat(menu_str, (char*)g_line_str);
    
    strcat(menu_str, (char*)g_cmd_str);
}

program_status_e Status_CmdCheck(char* cmd_str, program_status_e cur_stat)
{
    program_status_e result = Unknown;
    
    if (cur_stat == Menu)
    {
        result = Status_CmdCheckMenu(cmd_str);
    }
    else if (cur_stat == Option1)
    {
        result = Status_CmdCheckOption1(cmd_str);
    }
    else if (cur_stat == Option2)
    {
        result = Status_CmdCheckOption2(cmd_str);
    }
    else if (cur_stat == Option3)
    {
        result = Status_CmdCheckOption3(cmd_str);
    }
    else if (cur_stat == Option4)
    {
        result = Status_CmdCheckOption4(cmd_str);
    }
    else if (cur_stat == Option5)
    {
        result = Status_CmdCheckOption5(cmd_str);
    }
    else if (cur_stat == Option4_1)
    {
        result = Status_CmdCheckOption41(cmd_str);
    }
    else if (cur_stat == Option4_2)
    {
        result = Status_CmdCheckOption42(cmd_str);
    }
    else if (cur_stat == Option4_3)
    {
        result = Status_CmdCheckOption43(cmd_str);
    }
    else if (cur_stat == Option2_1)
    {
        result = Status_CmdCheckOption21(cmd_str);
    }
    else if (cur_stat == Option3_1)
    {
        result = Status_CmdCheckOption31(cmd_str);
    }
    else 
    {
        // Do nothing
    }
    
    return result;
}

program_status_e Status_CmdCheckMenu(char* cmd_str)
{
    program_status_e result = Unknown;
    
    if (cmd_str != NULL)
    {
        if (strcasecmp(cmd_str, (char*)g_cmd_one) == EQUAL)
        {
            result = Option1;
        }
        else if (strcasecmp(cmd_str, (char*)g_cmd_two) == EQUAL)
        {
            result = Option2;
        }
        else if (strcasecmp(cmd_str, (char*)g_cmd_three) == EQUAL)
        {
            result = Option3;
        }
        else if (strcasecmp(cmd_str, (char*)g_cmd_four) == EQUAL)
        {
            result = Option4;
        }
        else if (strcasecmp(cmd_str, (char*)g_cmd_five) == EQUAL)
        {
            result = Option5;
        }
        else 
        {
            // Do nothing
        }
    }
    
    return result;
}

program_status_e Status_CmdCheckOption1(char* cmd_str)
{
    program_status_e result = Unknown;
    
    if (cmd_str != NULL)
    {
        if (HotKey_IsExisted(cmd_str, ESC))
        {
            result = Menu;
        }
    }
    
    return result;
}

program_status_e Status_CmdCheckOption21(char* cmd_str)
{
    return Status_CmdCheckOption2(cmd_str);
}

program_status_e Status_CmdCheckOption3(char* cmd_str)
{
    program_status_e result = Unknown;
    uint8_t check_result = 0u;
    
    char temp_buffer[CMD_SIZE];
    
    if (cmd_str != NULL)
    {
        memcpy(temp_buffer, cmd_str, CMD_SIZE);
        
        if (HotKey_IsExisted(temp_buffer, ESC))
        {
            result = Menu;
        }
        else
        {
            // Remove enter
            CMD_RemoveEnter(temp_buffer);
            
            check_result = CMD_IsOption3Valid(temp_buffer);
            switch (check_result)
            {
                case 1u:
                    result = Option3_1;
                    break;
            }
        }
    }
    
    return result;
}

program_status_e Status_CmdCheckOption4(char* cmd_str)
{
    program_status_e result = Unknown;
    
    if (cmd_str != NULL)
    {
        if (HotKey_IsExisted(cmd_str, ESC))
        {
            result = Menu;
        }
        else if (strcasecmp(cmd_str, (char*)g_cmd_a) == EQUAL)
        {
            result = Option4_1;
        }
        else if (strcasecmp(cmd_str, (char*)g_cmd_b) == EQUAL)
        {
            result = Option4_2;
        }
        else if (strcasecmp(cmd_str, (char*)g_cmd_c) == EQUAL)
        {
            result = Option4_3;
        }
        else 
        {
            // Do nothing
        }
    }
    
    return result;
}

program_status_e Status_CmdCheckOption5(char* cmd_str)
{
    program_status_e result = Unknown;
    
    if (cmd_str != NULL)
    {
        if (HotKey_IsExisted(cmd_str, ESC))
        {
            result = Menu;
        }
    }
    
    return result;
}

program_status_e Status_CmdCheckOption41(char* cmd_str)
{
    program_status_e result = Unknown;
    
    // TODO
    
    return result;
}

program_status_e Status_CmdCheckOption42(char* cmd_str)
{
    program_status_e result = Unknown;
    
    // TODO
    
    return result;
}

program_status_e Status_CmdCheckOption43(char* cmd_str)
{
    program_status_e result = Unknown;
    
    // TODO
    
    return result;
}

void Status_ExecuteCmd(char* cmd_str, program_status_e stat, char* result_cmd)
{
    if (cmd_str != NULL && result_cmd != NULL)
    {
        if (stat == Menu)
        {
            // Return list of options
            // Return commandline indicator
            Menu_CreateStr(result_cmd);
        }
        else if (stat == Option1)
        {
            // Return student informations
            // Then, return esc commandline reminder
            // Then, return commandlinr indicator
            StudentInfo_CreateStr(result_cmd);
        }
        else if (stat == Option2)
        {
            // Return the name of option 2 functionalities
            // Then, return esc commandline reminder
            // Then, return the result of math expression
            // Then, return commandline indicator
            MathExprInform_CreateStr(result_cmd);
        }
        else if (stat == Option2_1)
        {
            // Return the result of math expression
            MathExpr_CreateStr(cmd_str, result_cmd);
        }
        else if (stat == Option3)
        {
            // Return the name of option 3 functionalities
            // Then, return esc commandline reminder
            // Then, return commandline indicator
            BasicLedInform_CreateStr(result_cmd);
        }
        else if (stat == Option3_1)
        {
            // Return of string indicating status of led
            BasicLed_CreateStr(cmd_str, result_cmd);
        }
        else if (stat == Option4)
        {
            // TODO
        }
        else if (stat == Option5)
        {
            // Return the string "Playing"
            // Then, return esc commandline reminder
            // Then, return commandline indicator
        }
        else if (stat == Unknown)
        {
            // Return the string "Invalid command"
            // Then, return commandline indicator
            Unknown_CreateStr(result_cmd);
        }
    }
}

uint8_t CMD_IsOption3Valid(char* cmd_str)
{
    uint8_t result = 0u;
    
    if (cmd_str != NULL)
    {
        // Get first word
        char* word = strtok(cmd_str, " ");
        if (word != NULL && ((strcasecmp(word, (char*)g_word_on) == EQUAL) || 
            (strcasecmp(word, (char*)g_word_off) == EQUAL)))
        {
            result = 1u;
        }
        
        // Get seconds word
        word = strtok(NULL, " ");
        if ((word != NULL) && (result == 1u) && ((strcasecmp(word, (char*)g_word_red) == EQUAL) || 
            (strcasecmp(word, (char*)g_word_green) == EQUAL) || 
            (strcasecmp(word, (char*)g_word_blue) == EQUAL) || 
            (strcasecmp(word, (char*)g_word_orange) == EQUAL)))
        {
            result = 1u;
        }
        else 
        {
            result = 0u;
        }
    }
    
    return result;
}

void StudentInfo_CreateStr(char* info_str)
{
    if (info_str != NULL)
    {
        // Show option 1
        strcat(info_str, (char*)g_option_1_str);
        strcat(info_str, (char*)g_line_str);
        
        // Show student 1
        strcat(info_str, (char*)g_student_name_str);
        strcat(info_str, (char*)g_student_1_name);
        strcat(info_str, (char*)g_line_str);
        
        strcat(info_str, (char*)g_student_id_str);
        strcat(info_str, (char*)g_student_1_id);
        strcat(info_str, (char*)g_line_str);
        
        // Show student 2
        strcat(info_str, (char*)g_student_name_str);
        strcat(info_str, (char*)g_student_2_name);
        strcat(info_str, (char*)g_line_str);
        
        strcat(info_str, (char*)g_student_id_str);
        strcat(info_str, (char*)g_student_2_id);
        strcat(info_str, (char*)g_line_str);
        
        // Show esc command
        strcat(info_str, (char*)g_escape_str);
        strcat(info_str, (char*)g_line_str);
        
        // Show commandline indicator
        strcat(info_str, (char*)g_cmd_str);
    }
}

void MathExprInform_CreateStr(char* inform_str)
{
    if (inform_str != NULL)
    {
        // Show option 2 string
        strcat(inform_str, (char*)g_option_2_str);
        strcat(inform_str, (char*)g_line_str);
        
        // Show esc exit command
        strcat(inform_str, (char*)g_escape_str);
        strcat(inform_str, (char*)g_line_str);
        
        // Show command indicator
        strcat(inform_str, (char*)g_cmd_str);
    }
}

void Unknown_CreateStr(char* unknown_cmd)
{
    if (unknown_cmd != NULL)
    {
        // Show unknown string
        strcat(unknown_cmd, (char*)g_cmd_invalid);
        strcat(unknown_cmd, (char*)g_line_str);
        
        // Show commandline indicator
        strcat(unknown_cmd, (char*)g_cmd_str);
    }
}

void MathExpr_CreateStr(char* cmd_str, char* expr_result)
{
    char temp_buffer[CMD_SIZE];
    int32_t temp_result = 0u;
    int32_t temp_status = CALC_SUCCESS;
    
    memcpy(temp_buffer, cmd_str, CMD_SIZE);
    
    if (cmd_str != NULL && expr_result != NULL)
    {
        CMD_RemoveEnter(temp_buffer);
        temp_status = calculate(temp_buffer, &temp_result);
        if (temp_status == CALC_SUCCESS)
        {
            sprintf(temp_buffer, "%d", temp_result);
            
            // Show "Result: " string
            strcat(expr_result, (char*)g_expr_result);
            strcat(expr_result, temp_buffer);
            strcat(expr_result, (char*)g_line_str);
            
            // Show cmd indicator
            strcat(expr_result, (char*)g_cmd_str);
        }
    }
}

program_status_e Status_CmdCheckOption2(char* cmd_str)
{
    program_status_e result = Unknown;
    
    char temp_buffer[CMD_SIZE];
    int32_t expr_result = 0u;
    int32_t expr_local = CALC_SUCCESS;
    
    memcpy(temp_buffer, cmd_str, CMD_SIZE);
    
    if (cmd_str != NULL)
    {
        if (HotKey_IsExisted(cmd_str, ESC))
        {
            result = Menu;
        }
        else 
        {
            CMD_RemoveEnter(temp_buffer);
            expr_local = calculate(temp_buffer, &expr_result);
            switch (expr_local)
            {
                case CALC_SUCCESS:
                    result = Option2_1;
                    break;
            }
        }
    }
    
    return result;
}

program_status_e Status_CmdCheckOption31(char* cmd_str)
{
    return Status_CmdCheckOption3(cmd_str);
}

void BasicLed_CreateStr(char* cmd_str, char* expr_result)
{
    char temp_buffer[CMD_SIZE];
    uint8_t is_on = 0;
    Led_TypeDef led;
    char* word = NULL;
    
    if (cmd_str != NULL && expr_result != NULL)
    {
        memset(temp_buffer, 0, CMD_SIZE);
        memcpy(temp_buffer, cmd_str, strlen(cmd_str));
        
        // Remove enter from commandline
        CMD_RemoveEnter(temp_buffer);
        
        // Get first word
        word = strtok(temp_buffer, " ");
        if (strcasecmp(word, (char*)g_word_on) == EQUAL)
        {
            is_on = 1;
        }
        else if (strcasecmp(word, (char*)g_word_off) == EQUAL)
        {
            is_on = 0;
        }
        
        // Get second word
        word = strtok(NULL, " ");
        led = Led_GetByName(word);
        
        if (is_on)
        {
            STM_EVAL_LEDOn(led);
            strcat(expr_result, (char*)g_led_on_inform);
        }
        else 
        {
            STM_EVAL_LEDOff(led);
            strcat(expr_result, (char*)g_led_off_inform);
        }
        
        // Show line break and cmd indicator
        strcat(expr_result, (char*)g_line_str);
        strcat(expr_result, (char*)g_cmd_str);
    }
}

void BasicLedInform_CreateStr(char* result_cmd)
{
    if (result_cmd != NULL)
    {
        // Return the name of option 3 functionalities

        strcat(result_cmd, (char*)g_option_3_str);
        strcat(result_cmd, (char*)g_line_str);
        
        // Then, return esc commandline reminder
        strcat(result_cmd, (char*)g_escape_str);
        strcat(result_cmd, (char*)g_line_str);
        
        // Then, return commandline indicator
        strcat(result_cmd, (char*)g_cmd_str);
    }
}

/* End file */
