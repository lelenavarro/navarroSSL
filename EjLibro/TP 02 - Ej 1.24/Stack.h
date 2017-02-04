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

char pop(void);
int push( char);
void fin_del_programa_por_mal_cierre();
int isEmpty(void);
int get_top(void);

#endif /* Stack_h */
