//-----------------------------------------------------------*
//			UTN FRBA - SSL
//-----------------------------------------------------------*
//			TP 2 - Ejercicio 1.24 K&R
//-----------------------------------------------------------*
//Curso: K2051 - Lunes noche
//Grupo 1
//-----------------------------------------------------------*

#ifndef Stack_h
#define Stack_h

#include <stdio.h>

#define MAX_STACK 1024

typedef struct {
    int top;
    char character[MAX_STACK];
} stack;

char pop( stack*);
int push( stack*, char);

#endif /* Stack_h */
