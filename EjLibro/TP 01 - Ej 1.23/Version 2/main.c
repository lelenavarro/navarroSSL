//-----------------------------------------------------------*
//			UTN FRBA - SSL
//-----------------------------------------------------------*
//		TP 1 - Ejercicio 1.23 K&R
//-----------------------------------------------------------*
//Curso: K2051 - Lunes noche
//Grupo 1
//-----------------------------------------------------------*
//DIRECTIVAS AL PREPROCESADOR
#include<stdio.h>
#include<stdbool.h>
#include"header.h"

int main()
{
    int len, input_char, function_return;
    char input_array[MAXLENGTH];
    enum states state;
    bool finish_program;
    
    finish_program=false;
    
    while(finish_program==false)
    {
        puts("--------------------------------------------------");
        puts("Ingresar el codigo. Apretar Ctrl+D para finalizar:\n");
        empty_array_for_new_program(input_array);
        input_char=0;
        state=NO_COMMENT; //Estado de comienzo
        if((len=get_line(input_array,MAXLENGTH))>0)
        {
            while(input_array[input_char]!='\0')
            {
                function_return=0;
                switch(state)
                {
                    case NO_COMMENT:
                        state = read_char_in_nc_state(input_array[input_char], state);
                        break;
                    case ESCAPE_NO_COMMENT:
                        putchar(input_array[input_char]);
                        state=NO_COMMENT;
                        break;
                    case CHAR:
                        state = read_char_in_char_state(input_array[input_char], state);
                        break;
                    case ESCAPE_CHAR:
                        putchar(input_array[input_char]);
                        state=END_OF_CHAR;
                        break;
                    case END_OF_CHAR:
                        state = read_char_in_end_of_char_state(input_array[input_char],state);
                        //putchar(input_array[input_char]);
                        break;
                    case EMPTY_CHAR_ERROR:
                        goto END_OF_STATE_MACHINE;
                    case MORE_THAN_ONE_CHAR_ERROR:
                        goto END_OF_STATE_MACHINE;
                    case STRING:
                        state = read_char_in_string_state(input_array[input_char], state);
                        putchar(input_array[input_char]);
                        break;
                    case ESCAPE_STRING:
                        putchar(input_array[input_char]);
                        state=STRING;
                        break;
                    case POSSIBLE_COMMENT:
                        state = read_char_in_pc_state(input_array[input_char],state);
                        break;
                    case LINE_COMMENT:
                        state = read_char_in_lc_state(input_array[input_char],state);
                        break;
                    case COMMENT:
                        state = read_char_in_comment_state(input_array[input_char], state);
                        break;
                    case POSSIBLE_END_OF_COMMENT:
                        state = read_char_in_peoc_state(input_array[input_char],state);
                }
                input_char++;	//Para poder trabajar con el siguiente caracter en la proxima iteracion
            }
        }
    END_OF_STATE_MACHINE: error_message(state);
        finish_program = run_program_again();
    }
    return 0;
}	//Fin de la FUNCION MAIN

