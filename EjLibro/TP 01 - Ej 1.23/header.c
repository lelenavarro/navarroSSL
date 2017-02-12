//-----------------------------------------------------------*
//			UTN FRBA - SSL
//-----------------------------------------------------------*
//		TP 1 - Ejercicio 1.23 K&R
//-----------------------------------------------------------*
//Curso: K2051 - Lunes noche
//Grupo 1
//-----------------------------------------------------------*

#include "header.h"
#include<stdbool.h>

//DEFINICION DE FUNCIONES INVOCADAS
//-------------------------------------------------------------------
int read_char_in_nc_state(char ch, enum states state){
    
    switch (ch) {
        case '/':
            state = POSSIBLE_COMMENT;
            break;
        case '"':
            state = STRING;
            putchar(ch);
            break;
        case '\'':
            state = FIRST_CHAR;
            putchar(ch);
            break;
        default:
            state = NO_COMMENT;
            putchar(ch);
            break;
    }
    return state;
    
}	//La funcion analiza si el caracter que se recibe puede indicar el inicio de un comentario
//-------------------------------------------------------------------
int read_char_in_first_char_state(char ch, enum states state){
    switch (ch) {
        case '\'':
			putchar(ch);
			puts("\nERROR: Un char no puede ser vacio. Se sigue analizando igualmente");
            break;
        default:
            putchar(ch);
            state = CHAR;
            break;
    }
    return state;
}	//Se analiza si el primer caracter que se recibe finaliza la constante caracter
    //vacia (error) o si se pasa un estado que espera otro caracter
//-------------------------------------------------------------------
int read_char_in_char_state(char ch, enum states state){
    switch (ch) {
        case '\'':
            putchar(ch);
            state = NO_COMMENT;
            break;
        default:
            putchar(ch);
            state = CHAR;
            break;
    }
    return state;
}	//Se analiza si el caracter que se recibe es un apostrofo (cierra constante caracter) o
    //o sigen llegando caracteres pertenecientes a la misma constante
//-------------------------------------------------------------------
int read_char_in_pc_state(char ch, enum states state){
    switch (ch) {
        case '/':
            return state = LINE_COMMENT;
            break;
        case '*':
            return state = COMMENT;
            break;
        default:
            return state = NO_COMMENT;
            break;
    }
    //Si no es un No Comentario, ni es un Comentario de Linea, entonces es un Comentario
    
}	//Se analiza si el caracter que se recibe hace que se pase a un comentario
    //de varias lineas, de una linea, o que no sea un comentario
//-------------------------------------------------------------------
int read_char_in_lc_state(char ch, enum states state){
    if(ch!='\n')
    {
        return state = LINE_COMMENT;
    }else{
        return state = NO_COMMENT;
    }
}	//Se analiza si el caracter que se lee es un salto de linea
    //(fin del comentario de linea) o no
//-------------------------------------------------------------------
int read_char_in_comment_state(char ch, enum states state){
    if(ch=='*')
    {
        return state = POSSIBLE_END_OF_COMMENT;
    }else{
        return state = COMMENT;
    }
}	//Se analiza si el caracter puede ocasionar un fin de comentario o no
//-------------------------------------------------------------------
int read_char_in_peoc_state(char ch, enum states state){
    if(ch=='/')
    {
        putchar(32);
        return state = NO_COMMENT;
    }else{
        return state = COMMENT;
    }
}	//Se analiza si finalizo el comentario o no
//-------------------------------------------------------------------
int read_char_in_string_state(char ch, enum states state){
    switch (ch) {
        case '"':
            state = NO_COMMENT;
            break;
        default:
            state = STRING;
            break;
    }
    return state;
}	//Se analiza si el string termino o no
//-------------------------------------------------------------------
void error_message(int state){
    
    if(state==STRING){
        puts("\nError por terminar el input con una cadena abierta\n");
    } else if(state==CHAR){
        puts("\nError por terminar el input con un caracter sin cerrar\n");
    } else if (state==COMMENT){
        puts("\nError por no cerrar el comentario\n");
    }
}	//La funcion imprime mensaje de error por ingresar un caracter invalido
//-------------------------------------------------------------------
