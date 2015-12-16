/*
 * Date: 14/10/2015
 * Writter: References
 * Description: This file contains function declarations for expression evaluation
 */
 
// Include header files
#include <stdint.h>
#include "stm32f4xx.h"

// Macros declarations
#define STACKSIZE 20
#define CALC_FAIL -2
#define CALC_SUCCESS -1
#define TRUE 1
#define FALSE 0

typedef enum CALC_SYMBOLS_TAG
{
    OR=0,
    AND,
    NOT,
    XOR,
    OPEN,
    CLOSE,
    NUMBER,
    MULTIPLY,
    DIVIDE,
    ADD,
    SUBTRACT,
    INVALID
} CALC_SYMBOLS;

// Struct defininition
struct level 
{
    int32_t var;
    CALC_SYMBOLS sym;
};

// Public functions
int32_t push(struct level* p1);
int32_t pop(struct level* p1);
int32_t peek(struct level* p1);
int32_t stack_depth(void);
void init_stack(void);
int32_t calc_binary_op(CALC_SYMBOLS sym);
int32_t calc_unary_op(CALC_SYMBOLS sym);
int32_t calc_paren(CALC_SYMBOLS sym);
int32_t calc_number(int32_t num);;
int32_t calculate(char* exp, int32_t* result);
