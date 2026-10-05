// =====================================================================
// ArbolAVL.h — Sección 4 del enunciado: árbol AVL completo.
//
// Este archivo declara el TAD que usted debe construir EN SU
// TOTALIDAD: ningún método tiene implementación dada. El árbol debe
// quedar balanceado tanto al insertar como al eliminar (ver Sección
// 4.2), no solo funcionar como un árbol binario de búsqueda simple.
//
// El árbol guarda enteros con signo: positivos representan compras,
// negativos representan ventas (ver Sección 3 del enunciado).
// =====================================================================
#ifndef ARBOL_AVL_H
#define ARBOL_AVL_H

#include <list>
#include <algorithm>

// Resultado de una consulta que puede no tener respuesta (por ejemplo,
// pedir la mejor compra cuando no hay ninguna compra esperando).
struct ResultadoConsulta {
    bool existe;
    int valor; // valido solo si existe == true
};

class ArbolAVL {
public:
    ArbolAVL();
    ~ArbolAVL();

    // TODO(Estudiante): inserta 'valor' en el arbol, respetando el
    // orden de un arbol binario de busqueda, y dejando el arbol
    // balanceado al terminar: actualice la altura de cada nodo en el
    // camino de vuelta hacia la raiz y rote cuando el factor de
    // equilibrio de algun nodo quede fuera de [-1, 1]. El
    // comportamiento es indefinido si 'valor' ya esta en el arbol (el
    // enunciado garantiza que no se repiten valores).
    void insertar(int valor);

    // TODO(Estudiante): elimina 'valor' del arbol si existe (no hace
    // nada si no existe), y rebalancea de la misma forma que en
    // insertar. Considere los tres casos clasicos de eliminacion en un
    // BST:
    //   1) el nodo es una hoja,
    //   2) el nodo tiene un solo hijo,
    //   3) el nodo tiene dos hijos (sustituir por su sucesor inorden:
    //      el menor valor de su subarbol derecho, y eliminar ese
    //      sucesor de su posicion original).
    void eliminar(int valor);

    // TODO(Estudiante): retorna true si 'valor' esta en el arbol.
    bool buscar(int valor) const;

    // TODO(Estudiante): la mejor compra es el valor mas alto del
    // arbol, siempre que sea positivo. Si el arbol esta vacio o su
    // valor mas alto no es positivo, retorne {false, 0}.
    ResultadoConsulta mejorCompra() const;

    // TODO(Estudiante): la mejor venta es el mayor valor del arbol que
    // sea ESTRICTAMENTE MENOR que cero (la venta mas barata). Si no
    // existe ningun valor negativo, retorne {false, 0}.
    //
    // Esta busqueda NO es simetrica a mejorCompra(): piense por que
    // una corresponde al extremo del arbol y la otra a un valor
    // cercano a un punto de referencia (cero), y documentelo en su
    // informe de diseno.
    ResultadoConsulta mejorVenta() const;

    // TODO(Estudiante): retorna, en una lista, todos los valores del
    // arbol en orden ascendente (recorrido inorden).
    std::list<int> recorridoInorden() const;

private:
    struct Nodo {
        int valor;
        int altura;
        Nodo* izquierdo;
        Nodo* derecho;
    };

    Nodo* raiz_;
    int altura(Nodo* nodo) const;
    void actualizarAltura(Nodo* nodo);
    int factorEquilibrio(Nodo* nodo) const;

    Nodo* rotarIzquierda(Nodo* nodo);
    Nodo* rotarDerecha(Nodo* nodo);
    Nodo* balancear(Nodo* nodo);

    Nodo* insertar(Nodo* nodo, int valor);
    Nodo* eliminar(Nodo* nodo, int valor);
    Nodo* minimo(Nodo* nodo);

    bool buscar(Nodo* nodo, int valor) const;

    void recorridoInorden(Nodo* nodo, std::list<int>& lista) const;

    void destruir(Nodo* nodo);
};

#include "ArbolAVL.hxx"

#endif
