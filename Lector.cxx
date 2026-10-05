#include "Lector.h"
#include <fstream>
#include <iostream>
#include <sstream>

static void imprimirConsulta(const ArbolAVL& arbol) {
    ResultadoConsulta compra = arbol.mejorCompra();
    ResultadoConsulta venta = arbol.mejorVenta();

    std::cout << "Mejor compra: ";
    if (compra.existe) std::cout << compra.valor;
    else std::cout << "ninguna";
    std::cout << std::endl;

    std::cout << "Mejor venta: ";
    if (venta.existe) std::cout << (-venta.valor);
    else std::cout << "ninguna";
    std::cout << std::endl;

    std::cout << "Arbol (inorden):";
    for (int v : arbol.recorridoInorden()) {
        std::cout << " " << v;
    }
    std::cout << std::endl;
}

void procesarEventos(const std::string& rutaArchivo, ArbolAVL& arbol) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir " << rutaArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        std::istringstream iss(linea);
        std::string comando;
        iss >> comando;

        if (comando == "COMPRA") {
            std::string id;
            int precio;
            iss >> id >> precio;
            ResultadoConsulta venta = arbol.mejorVenta();
            if (venta.existe && precio >= (-venta.valor)) {
                arbol.eliminar(venta.valor);
                std::cout << "COMPRA " << id << " " << precio
                          << " -> cruza con venta a " << (-venta.valor) << std::endl;
            } else {
                arbol.insertar(precio);
                std::cout << "COMPRA " << id << " " << precio << " -> en espera" << std::endl;
            }
        } else if (comando == "VENTA") {
            std::string id;
            int precio;
            iss >> id >> precio;
            ResultadoConsulta compra = arbol.mejorCompra();
            if (compra.existe && compra.valor >= precio) {
                arbol.eliminar(compra.valor);
                std::cout << "VENTA " << id << " " << precio
                          << " -> cruza con compra a " << compra.valor << std::endl;
            } else {
                arbol.insertar(-precio);
                std::cout << "VENTA " << id << " " << precio << " -> en espera" << std::endl;
            }
        } else if (comando == "CANCELAR") {
            int precio;
            iss >> precio;
            if (arbol.buscar(precio)) {
                arbol.eliminar(precio);
                std::cout << "CANCELAR " << precio << " -> OK (compra)" << std::endl;
            } else if (arbol.buscar(-precio)) {
                arbol.eliminar(-precio);
                std::cout << "CANCELAR " << precio << " -> OK (venta)" << std::endl;
            } else {
                std::cout << "CANCELAR " << precio << " -> no encontrada" << std::endl;
            }
        } else if (comando == "CONSULTAR") {
            imprimirConsulta(arbol);
        } else {
            std::cerr << "Evento desconocido: " << comando << std::endl;
        }
    }
    archivo.close();
}
