//-----------------------------------------------------------*
//			UTN FRBA - SSL
//-----------------------------------------------------------*
//			TP 2 - Ejercicio 1.24 K&R
//-----------------------------------------------------------*
//Curso: K2051 - Lunes noche
//Grupo 1
//-----------------------------------------------------------*
#include <stdlib.h>
#include "Stack.h"
#include <stdio.h>

//Stack
int push(stack *stk, char chr)
{
    if (stk->top == MAX_STACK) {
        printf("Stack overflow. No es posible poner mas valores en la pila.\n");
        return EXIT_FAILURE;
    }
    stk->top++;
    stk->character[stk->top] = chr;
    
    return 0;
}

//Pop
char pop(stack *stk)
{
    char retValue;
    
    if (stk->top == 0) {
        return 1;
    }
    retValue = stk->character[stk->top];
    stk->top--;
    
    return (retValue);
}
