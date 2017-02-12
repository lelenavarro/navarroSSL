//-----------------------------------------------------------*
//			UTN FRBA - SSL
//-----------------------------------------------------------*
//		TP 1 - Ejercicio 1.23 K&R
//-----------------------------------------------------------*
//Curso: K2051 - Lunes noche
//Grupo 1
//-----------------------------------------------------------*

#ifndef header_h
#define header_h
#include <stdio.h>
#include<stdbool.h>
//ESTADOS DEL AUTOMATA
enum states {
    NO_COMMENT,
    CHAR,
    FIRST_CHAR,
    POSSIBLE_COMMENT,
    LINE_COMMENT,
    COMMENT,
    POSSIBLE_END_OF_COMMENT,
    STRING,
};

//DECLARACION DE FUNCIONES
int read_char_in_nc_state(char char_from_input_array, enum states);
int read_char_in_first_char_state(char char_from_input_array, enum states);
int read_char_in_char_state(char char_from_input_array, enum states);
int read_char_in_end_of_char_state(char char_from_input_array, enum states);
int read_char_in_pc_state(char char_from_input_array, enum states);
int read_char_in_lc_state(char char_from_input_array, enum states);
int read_char_in_comment_state(char char_from_input_array, enum states);
int read_char_in_peoc_state(char char_from_input_array, enum states);
int read_char_in_string_state(char char_from_input_array, enum states);
int print_input_array_until_end_of_string(char* part_of_input_array,int i);
void error_message(int state);

#endif /* header_h */
