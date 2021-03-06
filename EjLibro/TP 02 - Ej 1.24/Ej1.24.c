//-----------------------------------------------------------*
//			UTN FRBA - SSL
//-----------------------------------------------------------*
//		TP 2 - Ejercicio 1.24 K&R
//-----------------------------------------------------------*
//Curso: K2051 - Lunes noche
//Grupo 1
//-----------------------------------------------------------*
//DIRECTIVAS AL PREPROCESADOR
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

//ESTADOS DEL AUTOMATA
enum
{
    CODE,
    POSSIBLE_COMMENT_IN,
    POSSIBLE_COMMENT_OUT,
    COMMENT_SIMPLE,
    COMMENT_MULTI,
    QUOTE1,
    QUOTE2
};

int main(void)
{
    int ch;
    int state = CODE;
    int error = 0;  	/* para ok-message */
    char open;
    size_t line = 1;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            line++;
        }

        switch (state)
        {
        case CODE:
            if (ch == '\'')
            {
                state = QUOTE1;
            }
            else if (ch == '"')
            {
                state = QUOTE2;
            }
            else if (ch == '/')
            {
                    //Posible comienzo de comentario
                    state = POSSIBLE_COMMENT_IN;
            }
            else if (ch == '(' || ch == '[' || ch == '{')
            {
                push(ch);
            }
            else if (ch == ')' || ch == ']' || ch == '}')
            {
                if(isEmpty()) /* Hay un cierre pero no hay nada abierto */
                {
                    printf("Linea %lu: Cierre '%c' encontrado sin contraparte.\n", (unsigned long)line, ch);
                    error = 1;
                }
                else
                {
                    open = pop();

                    if ((ch == ')' && open != '(') ||
                        (ch == ']' && open != '[') ||
                        (ch == '}' && open != '{'))
                    {
                        printf("Linea %lu: Cierre '%c' no matchea con la apertura '%c'.\n", (unsigned long)line, ch, open);
			fin_del_programa_por_mal_cierre();    
                        error = 1;
                    }
                }
            }
            break;
			
	    case POSSIBLE_COMMENT_IN:
               
                  if ( ch == '*')
                    {
                      //Comienzo de comentario multilinea
                      state = COMMENT_MULTI;
                     }
                   else if(ch == '/')
                     {
                      //Comienzo de comentario de linea simple
                      state = COMMENT_SIMPLE;
                      }
                      else
                      {
                      state = CODE;
                    }
            break;
                
            case COMMENT_SIMPLE:
                
                if (ch == '\n')
                {
                    state = CODE;
                }
            break;
                
            case COMMENT_MULTI:
                
                if (ch == '*')
                {
                    //Posible final de comentario
                    state = POSSIBLE_COMMENT_OUT;
                }
            break;
                
            case POSSIBLE_COMMENT_OUT:
                
                if (ch == '/')
                {
                    state = CODE;
                }
            break;
			
        case QUOTE1:
            if (ch == '\\')
            {
                (void)getchar();
            }
            else if (ch == '\'')
            {
                state = CODE;
            }
        break;
			
        case QUOTE2:
            if (ch == '\\')
            {
                (void)getchar();
            }
            else if (ch == '"')
            {
                state = CODE;
            }
        break;
        }
    }

    if (state == COMMENT_SIMPLE || state == COMMENT_MULTI)
    {
        printf("El codigo termina dentro de un comentario\n");
    }
    else if (state == QUOTE1)
    {
        printf("El codigo termina en una cita\n");
    }
    else if (state == QUOTE2)
    {
        printf("El codigo termina en una cita\n");
    }
    else if (isEmpty() && error == 0)
    {
        printf("Perfecto!\n");
    }

    if (!(isEmpty())) /* quedo algo en la pila */
    {
        size_t i;
        for (i = 0; i < get_top(); i++)
        {
            char muestro_caracter = pop();
            printf("Se abrió un '%c' y no se cerró.\n", muestro_caracter);
        }
    }
    return 0;
}
