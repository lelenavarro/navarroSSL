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
    ESCAPE_NO_COMMENT,
    ESCAPE_STRING,
    ESCAPE_CHAR,
    CHAR,
    END_OF_CHAR,
    POSSIBLE_COMMENT,
    LINE_COMMENT,
    COMMENT,
    POSSIBLE_END_OF_COMMENT,
    STRING,
    EMPTY_CHAR_ERROR,
    MORE_THAN_ONE_CHAR_ERROR
};
#define MAXLENGTH 1024

//DECLARACION DE FUNCIONES
int get_line(char s[], int max);
int read_char_in_nc_state(char char_from_input_array, enum states);
int read_char_in_char_state(char char_from_input_array, enum states);
int read_char_in_end_of_char_state(char char_from_input_array, enum states);
int read_char_in_pc_state(char char_from_input_array, enum states);
int read_char_in_lc_state(char char_from_input_array, enum states);
int read_char_in_comment_state(char char_from_input_array, enum states);
int read_char_in_peoc_state(char char_from_input_array, enum states);
int read_char_in_string_state(char char_from_input_array, enum states);
int print_input_array_until_end_of_string(char* part_of_input_array,int i);
bool run_program_again();
void empty_array_for_new_program(char *input_array);
void error_message(int state);

#endif /* header_h */
