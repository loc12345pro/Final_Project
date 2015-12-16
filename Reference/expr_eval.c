/*
 * 
 *
 *
 */

#include "expr_eval.h"
#include <stdio.h>

const char opchars[] = {'|', '&', '!', '^', '(', ')', '#', '*', '/', '+', '-', '?'};
struct level *p1;
struct level *p2;
struct level top[STACKSIZE];

int32_t stack = 0;

int32_t push(struct level* p1)
{
    if (stack < STACKSIZE) 
    {
        top[stack].var = p1->var;
        top[stack].sym = p1->sym;
        stack++;
        return 1;
    }
    
    return 0;
}


int32_t pop(struct level* p1)
{
    if (stack > 0) 
    {
        stack--;
        p1->var = top[stack].var;
        p1->sym = top[stack].sym;
        return 1;
    }
    
    return 0 ;
}

int32_t peek (struct level* p1)
{
    if (stack > 0) 
    {
        p1->var = top[stack-1].var;
        p1->sym = top[stack-1].sym;
        return 1;
    }
    
    return 0;
}

int32_t stack_depth(void)
{
    return stack;
}

void init_stack(void)
{
    int32_t i = 0;
    for (; i < STACKSIZE; i++)
    {
        top[i].var = 0;
        top[i].sym = INVALID;
    }
    stack = 0;
}

int32_t calc_binary_op(CALC_SYMBOLS sym)
{
    struct level temp;
    // The operator has to come after a number - it can't be preceeded by anything else
    // Makes sure there's something on the stack before peeking at it
    
    if(stack_depth() < 1)
    {
        return CALC_FAIL;
    }
    
    // Look at the top of the stack and verify that it's a number
    peek(&temp);
    if(temp.sym != NUMBER)
    {
        return CALC_FAIL;
    }
    
    // Ok, the stack isn't empty, and the last item is a number - place the operator on the stack
    temp.sym = sym;
    if(push(&temp) != 1)
    {
        // push failed (probably overfilled stack)
        return CALC_FAIL;
    }
    
    // Everything went well, hurray!
    return CALC_SUCCESS;
}

int32_t calc_unary_op(CALC_SYMBOLS sym)
{
    struct level temp;
    // The operator has no restrictions as to what should precede it - it modifies numbers
    // that come after it.
    //printf("Calling calc_unary_op(NOT)\n");
    
    temp.sym = sym;
    if(push(&temp) != 1)
    {
        // push failed (probably overfilled stack)
        return CALC_FAIL;
    }
    
    // Everything went well, hurray!
    return CALC_SUCCESS;
}


int32_t calc_paren(CALC_SYMBOLS sym)
{
    struct level temp;
    int32_t result;
    // An open parenthesis simply pushes onto the stack so future operators and numbers won't
    // interact with previous numbers and operators.
    // A closed parenthesis takes the result of the calculation inside the parenthesis,
    // removes the open parenthesis immediately before the number (there better be one!)
    // and then calls the calc_number routine as though this were a new number - 
    // Which it might as well be - it's the result of a prenthesis protected calculation.
    switch(sym)
    {
    case OPEN: 
        // Push it on the stack and move on
    
        temp.sym = sym;
        if(push(&temp) != 1)
        {
            // push failed (probably overfilled stack)
            return CALC_FAIL;
        }
        break;
    case CLOSE: 
        // Make sure the top item is a number, make sure the next item is an open paren, then calc
        // Take off the last stack item - should be a number
    
        if(pop(&temp) != 1)
        {
            // pop failed (probably empty stack, which technically can't happen as we've already checked above)
            return CALC_FAIL;
        }
        // Make sure it's a number
        if(temp.sym != NUMBER)
        {
            return CALC_FAIL;
        }
        result = temp.var;
    
        // Take off the next stack item - should be an open paren
        if(pop(&temp) != 1)
        {
            // pop failed (probably empty stack, which technically can't happen as we've already checked above)
            return CALC_FAIL;
        }
        // Make sure it's an OPEN parenthesis
        if(temp.sym != OPEN)
        {
            return CALC_FAIL;
        }
        // Now trea the number as though it's a new number
        if(calc_number(result) != CALC_SUCCESS)
        {
            return CALC_FAIL;
        }
        break;
    default: // Wait, what?  Someone called this function with an invalid input...  Grrrr!
        return CALC_FAIL;
    }
    
    // Everything went well, hurray!
    return CALC_SUCCESS;
}
int32_t calc_number(int num)
{
    struct level temp;
    CALC_SYMBOLS precede;
    int32_t result;
    
    // What happens to a number depends on what preceded it.
    // If the stack is empty, then put the number on the stack
    if(stack_depth() < 1)
    {
        temp.var = num;
        temp.sym = NUMBER;
        push(&temp);
        return CALC_SUCCESS;
    }
    
    // The stack isn't empty, let's see what's there and act on it.
    peek(&temp);
    precede = temp.sym;
    switch(precede)
    {
    case OR:        // Make sure the stack item below the binary operator is a number
    case AND:       // If it is a number, remove both the operator and number from the
    case XOR:       // stack, perform the operation, and store the result back to the stack
    case MULTIPLY:
    case DIVIDE:
    case ADD:
    case SUBTRACT:
    
        // Remove the XOR from the stack (we don't need it anymore)
        if(pop(&temp) != 1)
        {
            // pop failed (probably empty stack, which technically can't happen as we've already checked above)
            return CALC_FAIL;
        }
        // Get the next item on the stack
        if(pop(&temp) != 1)
        {
            // pop failed (probably empty stack, which technically can't happen as we've already checked above)
            return CALC_FAIL;
        }
        // If the item we just got wasn't a number, this operator can't work - FAIL!
        if(temp.sym != NUMBER)
        {
            return CALC_FAIL;
        }
        // OR, AND, or XOR the number we just pulled off the stack with the new number we got
        switch(precede)
        {
        case OR:
            temp.var = temp.var | num;
            break;
        case AND:
            temp.var = temp.var & num;
            break;
        case XOR:
            temp.var = temp.var ^ num;
            break;
        case MULTIPLY:
            temp.var = temp.var * num;
            break;
        case DIVIDE:
            if(num == 0) // No division by 0 allowed!
            {
                return CALC_FAIL;
            }
            temp.var = temp.var / num;
            break;
        case ADD:
            temp.var = temp.var + num;
            break;
        case SUBTRACT:
            temp.var = temp.var - num;
            break;
        default:// Just being thorough - have no clue how this could happen... until someone modifies the code...
            return CALC_FAIL;
        }
        // Push the number on the stack as the result of the binary operator
        temp.sym = NUMBER;
        if(push(&temp) != 1)
        {
            // push failed (probably overfilled stack)
            return CALC_FAIL;
        }
        break;
    case NOT:
        // If the number is false (==0) then make it true (1) otherwise, make it false
        // Remove the NOT from the stack (we don't need it anymore)
        if(pop(&temp) != 1)
        {
            // pop failed (probably empty stack, which technically can't happen as we've already checked above)
            return CALC_FAIL;
        }
        // If the number is 0 (false) then make it true - every other number counts as true and becomes false
        if(num == 0)
        {
            result = TRUE;
        }
        else
        {
            result = FALSE;
        }
        // Treat this result as though it's a new number and call calc number again (recursively)
        // Push the number on the stack as the result of the NOT operator
        if(calc_number(result) != CALC_SUCCESS)
        {
            return CALC_FAIL;
        }
        break;
    case OPEN:
        // OPEN paren - We just started a new subequation - let's put the number on the stack
        temp.var = num;
        temp.sym = NUMBER;
        if(push(&temp) != 1)
        {
            // push failed (probably overfilled stack)
            return CALC_FAIL;
        }
        break;
    case CLOSE:     // We should never see a CLOSE paren on the stack - that should have been taken care of.
    case NUMBER:    // Two numbers in a row in an equation?!?  BLASPHEMY!
        return CALC_FAIL;
    default:        // Hmm - we don't know what that was - can't process it!
        return CALC_FAIL;
    }
    
    // Everything went well, hurray!
    return CALC_SUCCESS;
}

int32_t calculate(char * exp, int * result)
{
    /*************************************************************************************\
    |*>CRITICAL!! THERE IS NO OPERATOR PRECEDENCE - EVERYTHING IS EVALUATED LEFT TO RIGHT*|
    |*>--------------------> Use parenthesis to enforce precedence. <--------------------*|
    \*************************************************************************************/
    /* Goes through string character by character and calls the appropriate function
    * After all the characters have been processed it puts the last value on the stack 
    * into the result pointer - which should be the result of the calculation
    * If any function returns an error, or the stack hasn't been used up then this function
    * returns an error - the calculation was incomplete.
    * On success it returns -1
    * On failure it returns the location in exp where an error was detected
    */
    int32_t index; // index into the string we're processing
    struct level temp;
    int32_t number;
    
    // Start off with a fresh stack
    init_stack();
    
    if(exp[0] == 0) // Zero length string has no solution
    {
        return 0;
    }
    
    index = 0; // start at the beginning
    
    while(exp[index] != 0)
    {
        switch(exp[index])
        {
        case '|':
            if(calc_binary_op(OR) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '&':
            if(calc_binary_op(AND) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '^':
            if(calc_binary_op(XOR) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '!':
            if(calc_unary_op(NOT) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '(':
            if(calc_paren(OPEN) == CALC_FAIL)
            {
                return index;
            }
            break;
        case ')':
            if(calc_paren(CLOSE) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '*':
            if(calc_binary_op(MULTIPLY) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '/':
            if(calc_binary_op(DIVIDE) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '+':
            if(calc_binary_op(ADD) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '-':
            if(calc_binary_op(SUBTRACT) == CALC_FAIL)
            {
                return index;
            }
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            number = (exp[index] - 0x30);
            // See if the number is longer than a single digit
            while( (exp[index+1] >= 0x30) && (exp[index+1] <= 0x39) )
            {
                // While the next character is a digit
                // Increment the index pointer to the next digit
                index++;
                // Multiply the existing number by 10 and add the new digit
                number = (number * 10) + (exp[index] - 0x30);
            }
            if(calc_number(number) == CALC_FAIL)
            {
                return index;
            }
            break;
        case ' ': // space - do nothing
            break;
        default:
            // error - invalid character
            return index;
        }
        index++;
    }
    // String processing complete - there should be exactly one item left on the stack
    if(stack_depth() != 1)
    {
        return index;
    }
    
    // Get the remaining item on the stack
    if(pop(&temp) != 1)
    {
        // pop failed (probably empty stack, which technically can't happen as we've already checked above)
        return index;
    }
    // If the item we just got wasn't a number, then there is a problem - FAIL!
    if(temp.sym != NUMBER)
    {
        return index;
    }
    
    // Otherwise (ie, only one item that was a number) we can write the result and exit successfully
    *result = temp.var;
    return CALC_SUCCESS;
}

/* End of file */
