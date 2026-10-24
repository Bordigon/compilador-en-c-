#ifndef AnalizadorLexico_H
#define AnalizadorLexico_H
#include <iostream>
#include <fstream>
#define cod_cadena 0
#define cod_numEntero 1
#define cod_numReal 2
#define cod_ident 3
#define cod_simb 4
#define cod_reserv 12

using namespace std;

void comentario(FILE *fd3, char buff[], char* letra, int* linea, int *process, int *estado, char *next, bool *fallo, bool *fin);
void cadena(FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, char *next, bool *fallo, bool *fin);
void num(FILE *fd1, FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, bool *fallo, bool *fin);
void id(FILE *fd1, FILE *fd2, FILE *fd3, char buff[], char* letra, int *linea, int *process, int *estado, bool *fallo, bool *fin);
void reserv(FILE *fd2, char buf[]);
char *analizadorLexico(FILE* fd1, FILE* fd2, FILE* fd3, int *linea, char *buff);
int simbolos(char simbolo,int *num);
#endif