/* Leandro Navarro Grupo1 1.24 con pila */
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK 1024

enum
{
    CODE,
    COMMENT,
    QUOTE1,
    QUOTE2
};

void fin_del_programa_por_mal_cierre(char stack[1024], int *top);

int main(void)
{
    int ch;
    int state = CODE;
    char stack[MAX_STACK];
    int top = 0; 	/* puntero a la cima de la pila */
    int error = 0;  	/* para ok-message */
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
                int aux = getchar();

                if (aux == '*')
                {
                    state = COMMENT;
                }
                else
                {
                    ungetc(aux, stdin);
                }
            }
            else if (ch == '(' || ch == '[' || ch == '{')
            {
                if (top < MAX_STACK)
                {
                    stack[top++] = ch;
                }
                else
                {
                    printf("Pila chica!\n");
                    return EXIT_FAILURE;
                }
            }
            else if (ch == ')' || ch == ']' || ch == '}')
            {
                if (top == 0) /* Hay un cierre pero no hay nada abierto */
                {
                    printf("Linea %lu: Cierre '%c' encontrado sin contraparte.\n", (unsigned long)line, ch);
                    error = 1;
                }
                else
                {
                    char open = stack[--top];

                    if ((ch == ')' && open != '(') ||
                        (ch == ']' && open != '[') ||
                        (ch == '}' && open != '{'))
                    {
                        printf("Linea %lu: Cierre '%c' no matchea con la apertura '%c'.\n", (unsigned long)line, ch, open);
			fin_del_programa_por_mal_cierre(stack, &top);    
                        error = 1;
                    }
                }
            }
            break;
			
        case COMMENT:
            if (ch == '*')
            {
                int aux = getchar();

                if (aux == '/')
                {
                    state = CODE;
                }
                else
                {
                    ungetc(aux, stdin);
                }
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

    if (state == COMMENT)
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
    else if (top == 0 && error == 0)
    {
        printf("Perfecto!\n");
    }

    if (top > 0) /* quedo algo en la pila */
    {
        size_t i;
        for (i = 0; i < top; i++)
        {
            printf("Se abrió un '%c' y no se cerró.\n", stack[i]);
        }
    }

    return 0;
}

void fin_del_programa_por_mal_cierre(char stack[], int *top){
	system("cls");
	printf("El programa vuelve a iniciar. Se limpia la pila\n");
	*top = 0;
};
