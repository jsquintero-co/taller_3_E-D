#ifndef ORDEN_H
#define ORDEN_H

#include <string>

// TAD sencillo: representa el identificador del evento y su precio
// con signo. El arbol almacena solamente precioConSigno, puesto que
// el taller garantiza que los precios de ordenes pendientes son unicos.
struct Orden {
    std::string identificador;
    int precioConSigno;

    Orden(const std::string& id, int precio)
        : identificador(id), precioConSigno(precio) {}
};

#endif
