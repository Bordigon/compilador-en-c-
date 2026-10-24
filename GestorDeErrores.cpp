#include "GestorDeErrores.h"

void notificarError(FILE* fd, string analizador, int linea, string mensaje){
	fprintf(fd,"[ERROR %s]: la linea %d no es valida, %s\n",analizador.c_str(),linea,mensaje.c_str());
}

void err(FILE* fd3, char buff[], int estado, char letra, int *linea){
	if(estado==0)
		notificarError(fd3, "LEXICO", *linea, string(buff)+"el comentario no es correcto debe acabar con * y barra");

	else if(estado==1)
		notificarError(fd3, "LEXICO", *linea, string("'")+string(buff)+" es una cadena incompleta, debe empezar por ' y acabar por ', y debe estar en un unica linea.");

	else if(estado==2)
		notificarError(fd3, "LEXICO", *linea, string(buff)+" no tiene un formato correcto. Para hacer que sea un numero entero valido, solo puede ser una secuancia de digitos del 0 al 9, ejemplo: 9032.");

	else if(estado==3)
		notificarError(fd3, "LEXICO", *linea, string(buff)+" no tiene un formato correcto. Para hacerlo un numero real valido debe ser asi: una secuencia de digitos del 0 al 9, un punto y otra secuencia de digitos del 0 al 9, ejemplo: 84.827");
	else
		notificarError(fd3, "LEXICO", *linea,string(buff)+" no se reconoce como un inicio valido.\n Los numeros empiezan por digitos del 0 al 9. \n Los cometarios con /*.\n Las cadenas empiezan por '.\n Los identificadores empiezan por _ o una letra.");

	if(letra=='\n')
		(*linea)++;
	
	fprintf(fd3,"\n");
}