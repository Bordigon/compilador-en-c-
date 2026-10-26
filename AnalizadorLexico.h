#include "TS/TS_CPP/TSManager.h"
#include "TS/TS_CPP/Include/SymbolTable.h"
#include "TS/TS_CPP/Include/Entry.h"
#include "TS/TS_CPP/Include/TSUtils.h"

#ifndef AnalizadorLexico_H
#define AnalizadorLexico_H
#include <iostream>
#include <fstream>
#define cod_cadena 0
#define cod_numEntero 1
#define cod_numReal 2
#define cod_ident 3
#define cod_simb 4
#define cod_reserv 15

using namespace std;

void comentario(FILE *fd3, char buff[], char* letra, int* linea, int *process, int *estado, char *next, bool *fallo, bool *fin);
void cadena(FILE *fd1, FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, char *next, bool *fallo, bool *fin);
void num(FILE *fd1, FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, bool *fallo, bool *fin);
void id(FILE *fd1, FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, bool *fallo, bool *fin);
void reserv(FILE *fd2, char buff[], char aux, bool *coincidencia);
int simbolos(char simbolo,int *num);
void crearToken(FILE *fd1, FILE *fd2, int *estado, int *linea, bool *fin, char letra, char buff[], TS_CPP::SymbolTable* identi);
char *analizadorLexico(FILE* fd1, FILE* fd2, FILE* fd3, int *linea, char *buff, TS_CPP::SymbolTable* identi);
#endif