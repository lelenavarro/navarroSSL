/* 
TP1 - Grupo 01
16/11/2016
Ej1.23 Escriba un programa para eliminar todos los comentarios de un programa en C. 
No olvide manejar apropiadamente las cadenas entre comillas y las constantes de carácter. Los comentarios de C no se anidan.
*/
 
#include <stdio.h>

int main()
{
    int c;
    int c2;
    int simple_comment = 0;
    int quotes = 0;
    int comment = 0;
    int current_quote;
    c = getchar();
    while (c != EOF)
    {
        if (!comment && !quotes)
        {
            if (c == '\'' || c == '"')
            {
                quotes = 1;
                current_quote = c;
                putchar(c);
            }
            else if (c == '/')
            {
                c2 = getchar();
                if ((c2 != EOF && c2 == '*'))
                {
                    comment = 1;
                }
                else if (c2 == '/')
                {
                comment = 1;
                simple_comment = 1;
                }
                else
                {
                    putchar(c);
                    c = c2;
                    continue;
                }
            }
            else
            {
                putchar(c);
            }
        }
        else if (comment)
        {
            /* comentario que cierra */
            if (c == '*')
            {
                c2 = getchar();
                if (c2 != EOF && c2 == '/')
                {
                    comment = 0;
                }
                else
                {
                    c = c2;
                    continue;
                }
            }
            else if (simple_comment == 1)
            {
                if (c == '\n' )
                {
                    comment = 0;
                    simple_comment = 0;
                }
            }
        }
        else if (quotes)
        {
            if (c == '\\')
            {
                putchar(c);
                c = getchar();
            }
            else
            {
                /* quote que cierra */
                if (c == current_quote)
                    quotes = 0;
            }
            putchar(c);
        }

        c = getchar();
    }

    return 0;
}
