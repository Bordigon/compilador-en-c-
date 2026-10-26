#include "AnalizadorLexico.h"
#include "GestorDeErrores.h"

#include "TS/TS_CPP/TSManager.h"
#include "TS/TS_CPP/Include/SymbolTable.h"
#include "TS/TS_CPP/Include/Entry.h"
#include "TS/TS_CPP/Include/TSUtils.h"
#include "TS/TS_CPP/Include/SymbolTable.h"

using namespace TS_CPP;

void comentario(FILE *fd3, char buff[], char* letra, int* linea, int *process, int *estado, char *next, bool *fallo, bool *fin){
	buff[*process]=*letra; /*Se almacena la letra*/

	/*Si indice=0 y entonces comienza el comentario*/
	if(!*process){ 
		*estado=0;
		*next='*';
		(*process)++;
	}

	/* Si la letra=* y el indice=1 se interpreta que es el comienzo del comentario, pero si indice>1 buscaremos / 
	como siguiente caracter */		
	else if(*letra=='*'){ 

		if(*process==1)
			*next='.';
		else
			*next='/';

		(*process)++;
	}

	/*Si se estaba buscando "/" y se encuentra "/", entonces es fin de comentario*/
	else if(*letra=='/' && *next=='/'){ 
		cout<<"[PROCESADOR]: comentario procesado\n";
		*estado=-1;
		*process=0;
		*next='$';
	}

	/*Identifica letras, números y espacios. Si se buscaba /, se debe buscar * porque el* ya no inidca fin*/
	else if(*process>1){

		if(*next=='/')
			*next='*';
		else if(*letra=='\n')
			(*linea)++;

		(*process)++;
	}	

	else{
		if(*process==1){
			err(fd3, buff, *estado, *letra, linea);
			*fin=1;
		}
		else{
			(*process)++;
			*fallo=1;
			*next='$';
		}
	}
}

void cadena(FILE *fd1, FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, char *next, bool *fallo, bool *fin, SymbolTable* identi){
	
	/*Si indice=0 comenzamos a buscar el final de la cadena, el otro ' */
	if(!*process){
		*estado=1;
		*next=39;
		(*process)++;
	}

	else if(*letra==39 && *next==39){ 
		/*Crear el token cadena y vaciar el buffer*/
		buff[*process-1]='\0';

		if(*process>2)
			crearToken(fd1,fd2,estado,linea,fin,*letra,buff, identi);
		else
			*fin=1;
	}

	/*Símbolos y letras que puede contener la cadena*/
	else if(*letra!='\n'){
		buff[*process-1]=*letra; /*Se almacena el caracter*/
		(*process)++;
	}

	/*La cadena acepta todo menos un salto de linea puesto a mano con el enter*/
	else{
		buff[--(*process)]='\0';
		err(fd3, buff, *estado, *letra, linea);
		*fin=1;
	}
}

void num(FILE *fd1, FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, bool *fallo, bool *fin, SymbolTable* identi){
	
	buff[*process]=*letra; /*Se almacena el caracter*/

	/*Si indice=0 es el primer dígito, por lo que se cambia al estado 2 (busqueda de enteros) y se aumenta en uno el número de caracteres procesados*/
	if(!*process){
		*estado=2;
		(*process)++;
	}
	
	/*Procesamos un digito*/
	else if(*letra>='0' && *letra<='9')
		(*process)++;
	
	/*Se procesa un . por lo que el número debe ser real*/
	else if(*letra=='.' && *estado!=3){
		*estado=3;
		(*process)++;
	}

	/*Si llegamos a un delimitador y lo que se proceso antes es un digito tenemos un token*/
	else if(buff[*process-1]!='.'&&(*letra==' '||*letra=='\n'||*letra=='+'||*letra=='='||*letra==';'||*letra=='/'||*letra=='('||*letra==')')){ 
		buff[*process]='\0';
		crearToken(fd1,fd2,estado,linea,fin,*letra,buff, identi);
	}

	/*Si el símbolo no está contemplado, da error*/
	else{
		if(*letra==' '||*letra=='\n'||*letra=='+'||*letra=='='||*letra==';'||*letra=='/'||*letra=='!'||*letra=='('||*letra==')'){
			buff[*process]='\0';
			err(fd3, buff, *estado, *letra, linea);

			if(*letra!='\n' && *letra!=' ')
				fseek(fd1,-1,SEEK_CUR);
			
			*fin=1;
		}

		else{
			*fallo=1;
			(*process)++;
		}
	}
}

void id(FILE *fd1, FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, bool *fallo, bool *fin, SymbolTable* identi){
	
	buff[*process]=*letra; /*Se almacena el caracter*/

	/*Si indice=0 es el primer dígito, por lo que se cambia al estado 4*/
	if(!*process){
		*estado=4;
		(*process)++;
	}
	
	/*Procesamos un digito, una letra o _*/
	else if(*letra>='0' && *letra<='9' || *letra>='a' && *letra<='z' || *letra>='A' && *letra<='Z' || *letra=='_')
		(*process)++;

	/*Si llegamos a un delimitador se crea el token*/
	else if(*letra==' '||*letra=='\n'||*letra=='+'||*letra=='='||*letra==';'||*letra=='/'||*letra=='('||*letra==')'){ 
		buff[*process]='\0';
		crearToken(fd1,fd2,estado,linea,fin,*letra,buff, identi);
	}

	/*Si el símbolo no está contemplado, da error*/
	else{
		if(*letra==' '||*letra=='\n'||*letra=='+'||*letra=='='||*letra==';'||*letra=='/'||*letra=='!'||*letra=='('||*letra==')'){
			buff[*process]='\0';
			err(fd3, buff, *estado, *letra, linea);

			if(*letra!='\n' && *letra!=' ')
				fseek(fd1,-1,SEEK_CUR);
			
			*fin=1;
		}

		else{
			*fallo=1;
			(*process)++;
		}
	}
}

void reserv(FILE *fd2, char buff[], char aux[], bool *coincidencia){
	string palReserv[]={string("if"), string("else"),string("let"),string("int"),string("float"),string("string"),string("boolean"),string("echo"),string("prompt"),string("function"),string("return")};
	string pal=string(buff);
	int index=0;
	
	while(index<sizeof(palReserv)/sizeof(string) && !(*coincidencia)){
		*coincidencia=(pal==palReserv[index]);
		
		if(!(*coincidencia))
			index++;
	}
	
	if(!(*coincidencia))
		sprintf(aux,"%d",cod_ident);
	else
		sprintf(aux,"%d",(cod_reserv+index));
}

int simbolos(char simbolo,int *num){
	char simbolos[]={'*','=','!','+',';','/','(',')'};
	int index=1;
	*num=cod_simb;
	
	while(simbolos[index-1]!=simbolo){
		*num=cod_simb+index;
		index++;
	}
	
	return *num;
}

void crearToken(FILE *fd1, FILE *fd2, int *estado, int *linea, bool *fin, char letra, char buff[], SymbolTable* identi){
	fputc('<',fd2);
	char aux[5];	/*Variables auxiliares para sprintf*/
	int num;		/*Variables auxiliares para la creación de tokens para símbolos*/
	bool coinciden=0;
	
	if(*estado==1)
		sprintf(aux,"%d",cod_cadena);
	else if(*estado==2)
		sprintf(aux,"%d",cod_numEntero);
	else if(*estado==3)
		sprintf(aux,"%d",cod_numReal);
	else if(*estado==4)
		reserv(fd2,buff,aux,&coinciden);
	else
		sprintf(aux,"%d",simbolos(letra,&num));
	
		fputs(aux,fd2);
		fputs(", ",fd2);
		
	if(!coinciden)//----------------------------- cambio ----------------------------------
		{
		    if(*estado==4)   /* identificador */
		    {
		        Entry* e = identi->searchEntry(buff);
		        if(e == nullptr)
		            e = identi->createNewEntry(buff);
		        fprintf(fd2, "%d", e->getId());
		    }
		    else             /* cadena, entero, real y símbolo */
		        fputs(buff,fd2);
		}	//----------------------------- cambio	-----------------------------------	 	
	
	fputs(">\n",fd2);
		
	if(letra=='\n')
		(*linea)++;
	else if(*estado!=1 && *estado!=-1 && letra!=' ')
		fseek(fd1,-1,SEEK_CUR);
	
	*estado=-1;
	*fin=1;
}

char *analizadorLexico(FILE* fd1, FILE* fd2, FILE* fd3, int *linea, char buff[], SymbolTable* identi){
	
	char letra=getc(fd1);	/*Primer caracter del fichero a analizar*/
	char next='$'; 			/*Se ha elegido $ por coger uno que no es inicio de ningún token*/
	int process=0;			/*Caracteres procesados*/
	int estado=-1;			/*Indica que esta buscando el analizador léxico*/
	bool fallo=0;			/*Notifica fallos léxicos*/
	bool fin=0;

	while(letra!=EOF && !fin){
		cout<<"[DEPURADOR]: procesando: ("<<letra<<")\n";
		if(!fallo && (!process && letra=='/' || estado==0))
			comentario(fd3, buff, &letra, linea, &process, &estado, &next, &fallo, &fin);

		else if(!fallo && (!process && letra==39 || estado==1))
			cadena(fd1,fd2, fd3, buff, &letra, linea, &process, &estado, &next, &fallo, &fin, identi);

		else if(!fallo && (!process && (letra>='0' && letra<='9') || estado==2 || estado==3))
			num(fd1, fd2, fd3, buff, &letra, linea, &process, &estado, &fallo, &fin, identi);
		
		else if(!fallo && (!process && ( letra>='a' && letra<='z' || letra>='A' && letra<='Z' || letra=='_') || estado==4)){
			id(fd1, fd2, fd3, buff, &letra, linea, &process, &estado, &fallo, &fin, identi);
		}
		
		else if(letra=='\n'||letra==' '||letra=='*'||letra=='='||letra=='!'||letra=='+'||letra==';'||letra=='/'||letra=='('||letra==')'){

			if(fallo){
				buff[process]='\0';
				err(fd3, buff, estado, letra, linea);
				buff[0]='\0';
				estado=-1;
				
				if(letra!='\n' && letra!=' ')
					fseek(fd1, -1, SEEK_CUR);

			}
			else if(letra!='\n'&&letra!=' '){
				buff[0]=letra;
				buff[1]='\0';
				crearToken(fd1, fd2, &estado, linea, &fin, letra, buff, identi);
			}
			else if(letra=='\n')
				(*linea)++;

			fin=1;
		}

		/*No se puede identificar*/
		else if(!process || fallo){
			fallo=1;
			buff[process++]=letra;
		}
		
		if(!fin)
			letra=getc(fd1);
	}
	
	if(letra==EOF && estado!=-1){
		buff[process]='\0';
		
		if(estado==0)
			notificarError(fd3, "LEXICO", *linea, string(buff)+" es un comentario incompleto.");
		else
			notificarError(fd3, "LEXICO", *linea, string(buff)+" es un lexema incompleto.");
	}
	
	if(letra==EOF){ //-------------------------------------- cambio ----------------
	    strcpy(buff, " ");
	}		//-------------------------------------- cambio ----------------
	
	return buff;
}