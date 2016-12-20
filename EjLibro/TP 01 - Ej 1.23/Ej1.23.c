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
#define MAXLENGTH 1024

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

//DECLARACION DE FUNCIONES
int get_line(char s[], int max);
int read_char_in_nc_state(char char_from_input_array);
int read_char_in_char_state(char char_from_input_array);
int read_char_in_end_of_char_state(char char_from_input_array);
int read_char_in_pc_state(char char_from_input_array);
int read_char_in_lc_state(char char_from_input_array);
int read_char_in_comment_state(char char_from_input_array);
int read_char_in_peoc_state(char char_from_input_array);
int read_char_in_string_state(char char_from_input_array);
int print_input_array_until_end_of_string(char* part_of_input_array,int i);
bool run_program_again();
void empty_array_for_new_program(char *input_array);
void error_message(int state);

int main()
{

	int 	len,
		input_char,
		function_return;

	char 	input_array[MAXLENGTH];

	enum states state;

	bool 	finish_program;

	finish_program=false;

	while(finish_program==false)
	{
	puts("--------------------------------------------------");
	puts("Ingresar el codigo. Apretar Ctrl+D para finalizar:\n");
	empty_array_for_new_program(input_array);
	input_char=0;
	state=NO_COMMENT;
	if((len=get_line(input_array,MAXLENGTH))>0)
	{
		while(input_array[input_char]!='\0')
		{
			function_return=0;
			switch(state)
			{
			case NO_COMMENT:
				function_return=read_char_in_nc_state(input_array[input_char]);
				if(function_return==POSSIBLE_COMMENT){
					state=POSSIBLE_COMMENT;
					break;
				} else if (function_return==STRING){
					state=STRING;
				} else if (function_return==CHAR){
					state=CHAR;
				} else if (function_return==ESCAPE_NO_COMMENT){
					state=ESCAPE_NO_COMMENT;
					break;
				}
				putchar(input_array[input_char]);
				break;
			case ESCAPE_NO_COMMENT:
				putchar(input_array[input_char]);
				state=NO_COMMENT;
				break;
			case CHAR:
				function_return=read_char_in_char_state(input_array[input_char]);
				if(function_return==EMPTY_CHAR_ERROR){
					state=EMPTY_CHAR_ERROR;
					goto END_OF_STATE_MACHINE;
				} else if (function_return==END_OF_CHAR){
					state=END_OF_CHAR;
					putchar(input_array[input_char]);
					break;
				} else if (function_return==ESCAPE_CHAR){
					state=ESCAPE_CHAR;
					break;
				}
				break;
			case ESCAPE_CHAR:
				putchar(input_array[input_char]);
				state=END_OF_CHAR;
				break;
			case END_OF_CHAR:
				function_return=read_char_in_end_of_char_state(input_array[input_char]);
				if(function_return==NO_COMMENT){
					state=NO_COMMENT;
				} else if (function_return==MORE_THAN_ONE_CHAR_ERROR) {
					state=MORE_THAN_ONE_CHAR_ERROR;
					goto END_OF_STATE_MACHINE;
				}
				putchar(input_array[input_char]);
				break;
			case EMPTY_CHAR_ERROR:
				goto END_OF_STATE_MACHINE;
			case MORE_THAN_ONE_CHAR_ERROR:
				goto END_OF_STATE_MACHINE;
			case STRING:
				function_return=read_char_in_string_state(input_array[input_char]);
				if(function_return==NO_COMMENT)
				{
					state=NO_COMMENT;
					putchar(input_array[input_char]);
					break;
				} else if (function_return==ESCAPE_STRING){
					state=ESCAPE_STRING;
					break;
				}
				putchar(input_array[input_char]);
				break;
			case ESCAPE_STRING:
				putchar(input_array[input_char]);
				state=STRING;
				break;
			case POSSIBLE_COMMENT:
				function_return=read_char_in_pc_state(input_array[input_char]);
				if(function_return==NO_COMMENT){
					state=NO_COMMENT;
				} else if (function_return==LINE_COMMENT){
					state=LINE_COMMENT;
				} else if (function_return==COMMENT){
					state=COMMENT;
				}
			break;
			case LINE_COMMENT:
				function_return=read_char_in_lc_state(input_array[input_char]);
				if(function_return==NO_COMMENT)
					state=NO_COMMENT;
			break;
			case COMMENT:
				function_return=read_char_in_comment_state(input_array[input_char]);
				if(function_return==POSSIBLE_END_OF_COMMENT)
					state=POSSIBLE_END_OF_COMMENT;
			break;
			case POSSIBLE_END_OF_COMMENT:
				function_return=read_char_in_peoc_state(input_array[input_char]);
				if(function_return==COMMENT){
					state=COMMENT;
					break;
				} else if (function_return==NO_COMMENT){
					state=NO_COMMENT;
					break;
				}
			}
			input_char++;	//Para poder trabajar con el siguiente caracter en la proxima iteracion
		}
	}
	END_OF_STATE_MACHINE: error_message(state);
	finish_program = run_program_again();

	}
	return 0;
}	//Fin de la FUNCION MAIN


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

int read_char_in_nc_state(char char_from_input_array){
	if(char_from_input_array=='/')
		return POSSIBLE_COMMENT;
	if(char_from_input_array=='"')
		return STRING;
	if(char_from_input_array=='\'')
		return CHAR;
	if(char_from_input_array=='\\')
		return ESCAPE_NO_COMMENT;
	return NO_COMMENT;

}	//La funcion analiza si el caracter que se recibe puede indicar el inicio de un comentario
//-------------------------------------------------------------------
int read_char_in_char_state(char char_from_input_array){
	if(char_from_input_array=='\'')
		return EMPTY_CHAR_ERROR;
	if(char_from_input_array=='\\')
		return ESCAPE_CHAR;
	return END_OF_CHAR;
}	//La funcion analiza si el caracter que se recibe finaliza un caracter vacio (error) o si se pasa a un estado que espera el cierre del caracter
//-------------------------------------------------------------------
int read_char_in_end_of_char_state(char char_from_input_array){
	if(char_from_input_array=='\'')
		return NO_COMMENT;
	return MORE_THAN_ONE_CHAR_ERROR;
}

//-------------------------------------------------------------------

int read_char_in_pc_state(char char_from_input_array){
	if(char_from_input_array!='/' && char_from_input_array!='*')
		return NO_COMMENT;

	if(char_from_input_array=='/')
		return LINE_COMMENT;

	return COMMENT;	//Si no es un No Comentario, ni es un Comentario de Linea, entonces es un Comentario

}	//La funcion analiza si el caracter que se recibe hace que se pase a un comentario de varias lineas, de una linea, o que no sea un comentario
//-------------------------------------------------------------------
int read_char_in_lc_state(char char_from_input_array){
	if(char_from_input_array!='\n')
		return LINE_COMMENT;
	return NO_COMMENT;

}	//La funcion analiza si el caracter que se lee es un salto de linea (fin del comentario de linea) o no
//-------------------------------------------------------------------
int read_char_in_comment_state(char char_from_input_array){
	if(char_from_input_array=='*')
		return POSSIBLE_END_OF_COMMENT;

	return COMMENT;

}	//La funcion analiza si el caracter puede ocasionar un fin de comentario o no
//-------------------------------------------------------------------
int read_char_in_peoc_state(char char_from_input_array){
	if(char_from_input_array=='/')
		return NO_COMMENT;

	return COMMENT;
}	//La funcion analiza si finalizo el comentario o no
//-------------------------------------------------------------------
int read_char_in_string_state(char char_from_input_array){
	if(char_from_input_array=='"')
		return NO_COMMENT;
	if(char_from_input_array=='\\')
		return ESCAPE_STRING;
	return STRING;
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
