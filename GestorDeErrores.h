#ifndef GestorDeErrores_H
#define GestorDeErrores_H
#include <iostream>
#include <fstream>

using namespace std;

void notificarError(FILE* fd, string analizador, int linea, string mensaje);
void err(FILE* fd3, char buff[], int estado, char letra, int *linea);

#endif