// =====================================================================
// main.cpp
// Punto de entrada del Punto 1. Archivo COMPLETO.
//
// Uso: ./javebolsa eventos.txt
// =====================================================================
#include <iostream>
#include "ArbolAVL.h"
#include "Lector.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " eventos.txt" << std::endl;
        return 1;
    }

    ArbolAVL arbol;
    procesarEventos(argv[1], arbol);

    return 0;
}
