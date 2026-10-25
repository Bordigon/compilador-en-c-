#include "TS/TS_CPP/TSManager.h"
#include "TS/TS_CPP/Include/SymbolTable.h"
#include "TS/TS_CPP/Include/Entry.h"
#include "TS/TS_CPP/Include/TSUtils.h"
#include <iostream>
using namespace TS_CPP;

int main() {
    std::cout << "Hola" << std::endl;
 
    TSManager manager;
    SymbolTable* nombre_tabla = manager.createNewTable("nombre_tabla");
    Entry* nombre_entrada = nombre_tabla->createNewEntry("lexema");
    Entry* nombre_entrada1 = nombre_tabla->createNewEntry("x");
    Entry* nombre_entrada2 = nombre_tabla->createNewEntry("y"); 
    TSUtils::writeAllTablesToFile(&manager, "ejemplo_salida.txt");
    return 0;
}
