// =====================================================================
// Lector.h
// Procesa eventos.txt aplicando la regla de cruce de JaveBolsa sobre un
// ArbolAVL. Archivo COMPLETO: la regla de cruce no es parte de lo que
// se evalua en este taller (lo que se evalua es el arbol); esta dada
// para que pueda probar su ArbolAVL de punta a punta con
// ./javebolsa eventos.txt.
// =====================================================================
#ifndef LECTOR_H
#define LECTOR_H

#include <string>
#include "ArbolAVL.h"

// Lee eventos.txt y procesa cada evento sobre 'arbol', imprimiendo por
// pantalla el resultado de cada uno.
// Formato esperado (ver Seccion 4.3 del enunciado):
//   COMPRA <id> <precio>
//   VENTA <id> <precio>
//   CANCELAR <precio>
//   CONSULTAR
void procesarEventos(const std::string& rutaArchivo, ArbolAVL& arbol);

#endif
