#include "TS/TS_CPP/TSManager.h"
#include "TS/TS_CPP/Include/SymbolTable.h"
#include "TS/TS_CPP/Include/Entry.h"
#include "TS/TS_CPP/Include/TSUtils.h"
#include <iostream>
using namespace TS_CPP;

#include "AnalizadorLexico.h"
#include <fcntl.h>

int main(int argc, char *argv[]){	

	/*Como máximo solo se puede poner un fichero de entrada y dos de salida, uno de tokens y otra de errores*/
	if(argc!=4){
		cout<<"Es necesario 4 argumentos\n";
		exit(1);
	}
	
	if(string(argv[2])=="AnalizadorLexico.cpp" || string(argv[3])=="AnalizadorLexico.cpp"){
		cout<<"Se intento sobreescribir sobre el analizador lexico\n";
		exit(1);
	}

	/*fd1 lee de fichero*/
	FILE* fd1= fopen(argv[1],"r");
	if(!fd1){
		cout<<"ERROR en: "<<argv[1]<<"\n";
		exit(1);
	}
	
	/*fd2 escribe los tokens en un fichero*/
	FILE* fd2= fopen(argv[2],"w");
	if(!fd2){
		fclose(fd1);
		cout<<"ERROR en: "<<argv[2]<<"\n";
		exit(1);
	}
	
	/*fd3 escribe los errores en un fichero*/
	FILE* fd3= fopen(argv[3],"w");
	if(!fd3){
		fclose(fd1);
		fclose(fd2);
		cout<<"ERROR en: "<<argv[2]<<"\n";
		exit(1);
	}

	/*Análisis de tokens*/
	int linea=1;			/*Porque linea del fichero vamos leyendo*/
	string lexema=string("hola");			/*Representa los atributos de los tokens*/
	char buff[1024];

	TSManager manager;
	SymbolTable* identi = manager.createNewTable("identi");

	while(lexema!=string(" "))
		lexema=string(analizadorLexico(fd1,fd2,fd3,&linea,buff,identi)); /*Se encarga del análisis*/

	TSUtils::writeAllTablesToFile(&manager, "ejemplo_salida.txt");
	fclose(fd1);
	fclose(fd2);
	fclose(fd3);
	
	return 0;
}