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
int get_line(char s[], int max){
    
    int i,j,k;
    
    for(j=0,k=0;(i=getchar())!=EOF;++j)
        if(j<max-1)
            s[k++]=i;
    s[k]='\0';
    
    return k;
}	//La funcion lee el array ingresado por el usuario
//-------------------------------------------------------------------

int read_char_in_nc_state(char char_from_input_array, enum states state){
    
    switch (char_from_input_array) {
        case '/':
            state = POSSIBLE_COMMENT;
            break;
        case '"':
            state = STRING;
            putchar(char_from_input_array);
            break;
        case '\'':
            state = CHAR;
            putchar(char_from_input_array);
            break;
        case '\\':
            state = ESCAPE_NO_COMMENT;
            putchar(char_from_input_array);
            break;
        default:
            state = NO_COMMENT;
            putchar(char_from_input_array);
            break;
    }
    return state;
    
}	//La funcion analiza si el caracter que se recibe puede indicar el inicio de un comentario
//-------------------------------------------------------------------
int read_char_in_char_state(char char_from_input_array, enum states state){
    switch (char_from_input_array) {
        case '\'':
            state = EMPTY_CHAR_ERROR;
            break;
        case '\\':
            state = ESCAPE_CHAR;
            break;
        default:
            putchar(char_from_input_array);
            state = END_OF_CHAR;
            break;
    }
    return state;
}	//La funcion analiza si el caracter que se recibe finaliza un caracter vacio (error) o si se pasa a un estado que espera el cierre del caracter
//-------------------------------------------------------------------
int read_char_in_end_of_char_state(char char_from_input_array, enum states state){
    switch (char_from_input_array) {
        case '\'':
            state = NO_COMMENT;
            break;
        default:
            state = MORE_THAN_ONE_CHAR_ERROR;
            break;
    }
    putchar(char_from_input_array);
    return state;
}
//-------------------------------------------------------------------
int read_char_in_pc_state(char char_from_input_array, enum states state){
    
    switch (char_from_input_array) {
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
}	//La funcion analiza si el caracter que se recibe hace que se pase a un comentario de varias lineas, de una linea, o que no sea un comentario
//-------------------------------------------------------------------
int read_char_in_lc_state(char char_from_input_array, enum states state){
    if(char_from_input_array!='\n')
    {
        return state = LINE_COMMENT;
    }else{
        return state = NO_COMMENT;
    }
}	//La funcion analiza si el caracter que se lee es un salto de linea (fin del comentario de linea) o no
//-------------------------------------------------------------------
int read_char_in_comment_state(char char_from_input_array, enum states state){
    if(char_from_input_array=='*')
    {
        return state = POSSIBLE_END_OF_COMMENT;
    }else{
        return state = COMMENT;
    }
}	//La funcion analiza si el caracter puede ocasionar un fin de comentario o no
//-------------------------------------------------------------------
int read_char_in_peoc_state(char char_from_input_array, enum states state){
    if(char_from_input_array=='/')
    {
        putchar(32);
        return state = NO_COMMENT;
    }else{
        return state = COMMENT;
    }
}	//La funcion analiza si finalizo el comentario o no
//-------------------------------------------------------------------
int read_char_in_string_state(char char_from_input_array, enum states state){
    switch (char_from_input_array) {
        case '"':
            state = NO_COMMENT;
            break;
        case '\\':
            state = ESCAPE_STRING;
            break;
        default:
            state = STRING;
            break;
    }
    return state;
}	//La funcion analiza si el string termino o no
//-------------------------------------------------------------------
bool run_program_again(){
    
    char continue_exec;
    
    printf("\n\nDesea continuar con la ejecucion del Programa? [Y/n]\n");
    do
    {
        scanf("%c",&continue_exec);
    }
    while(continue_exec!='Y' && continue_exec!='n');
    
    if(continue_exec=='Y')
    {
        return false;
    } else if (continue_exec=='n')
    {
        return true;
    }
    return true;
}	//La funcion permite volver a ejecutar el programa sin salir del mismo
//-------------------------------------------------------------------
void empty_array_for_new_program(char *input_array){
    int i=0;
    for(i=0;i<=MAXLENGTH-1;i++)
        input_array[i]='\0';
}
//-------------------------------------------------------------------
void error_message(int state){
    
    if (state==EMPTY_CHAR_ERROR){
        puts("\nError por caracter vacio\n");
    } else if (state==MORE_THAN_ONE_CHAR_ERROR){
        puts("\nError por ingresar mas de un simbolo para un caracter\n");
    } else if(state==STRING){
        puts("\nError por terminar el input con una cadena abierta\n");
    } else if(state==CHAR||state==END_OF_CHAR){
        puts("\nError por terminar el input con un caracter sin cerrar\n");
    } else if (state==COMMENT){
        puts("\nError por no cerrar el comentario\n");
    }
}	//La funcion imprime mensaje de error por ingresar un caracter invalido
//-------------------------------------------------------------------
