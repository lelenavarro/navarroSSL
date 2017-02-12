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

#define MAX_STACK 1024

struct {
    int top;
    char character[MAX_STACK];
} stk;
//DEFINICION DE FUNCIONES INVOCADAS
//Stack
int push(char chr)
{
    if (stk.top == MAX_STACK) {
        printf("Stack overflow. No es posible poner mas valores en la pila.\n");
        return EXIT_FAILURE;
    }
    stk.top++;
    stk.character[stk.top] = chr;
    
    return 0;
}

//Pop
char pop()
{
    char retValue;
    
    if (stk.top == 0) {
        return 1;
    }
    retValue = stk.character[stk.top];
    stk.top--;
    
    return (retValue);
}

void fin_del_programa_por_mal_cierre(){
    system("cls");
    printf("El programa vuelve a iniciar. Se limpia la pila\n");
    stk.top = 0;
};

int isEmpty (void)
{
    if (stk.top == 0 ){
        return 1;}
    else{
        return 0;
        }
};

int get_top(void)
{
    return stk.top;
};
