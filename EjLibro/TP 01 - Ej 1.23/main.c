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
    int ch;
    enum states state;

    state=NO_COMMENT; //Estado de comienzo
    
            while ((ch = getchar()) != EOF)
            {
                switch(state)
                {
                    case NO_COMMENT:
                        state = read_char_in_nc_state(ch, state);
                        break;
                    case FIRST_CHAR:
                        state = read_char_in_first_char_state(ch, state);
                        break;
                    case CHAR:
                        state = read_char_in_char_state(ch, state);
                        break;
                    case STRING:
                        state = read_char_in_string_state(ch, state);
                        putchar(ch);
                        break;
                    case POSSIBLE_COMMENT:
                        state = read_char_in_pc_state(ch,state);
                        break;
                    case LINE_COMMENT:
                        state = read_char_in_lc_state(ch,state);
                        break;
                    case COMMENT:
                        state = read_char_in_comment_state(ch, state);
                        break;
                    case POSSIBLE_END_OF_COMMENT:
                        state = read_char_in_peoc_state(ch,state);
                        break;
                }
            }
    //Se evaluan posibles errores
    error_message(state);
    return 0;
}//Fin MAIN
