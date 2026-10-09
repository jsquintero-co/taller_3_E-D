// =====================================================================
// plan_pruebas.cpp
// Plan de pruebas para el TAD ArbolAVL.
// Ejecuta los 9 casos de prueba y solo imprime [OK] <titulo> cuando
// la verificacion coincide con la salida esperada.
// =====================================================================
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include "ArbolAVL.h"

static int totalPruebas = 0;
static int pruebasOk    = 0;

static std::string aTexto(const ResultadoConsulta& r, bool esVenta) {
    if (!r.existe) return "ninguna";
    int v = esVenta ? -r.valor : r.valor;
    return std::to_string(v);
}

static std::string inordenATexto(const std::list<int>& lista) {
    std::ostringstream oss;
    bool primero = true;
    for (int v : lista) {
        if (!primero) oss << " ";
        oss << v;
        primero = false;
    }
    return oss.str();
}

// Verifica que 'obtenido' == 'esperado'. Solo imprime el OK.
static void verificar(const std::string& nombre,
                      const std::string& obtenido,
                      const std::string& esperado) {
    totalPruebas++;
    if (obtenido == esperado) {
        pruebasOk++;
        std::cout << "[OK] " << nombre << std::endl;
    } else {
        std::cout << "[FALLO] " << nombre << std::endl;
    }
}

// Captura el estado del arbol como string para comparar.
static std::string estadoATexto(const ArbolAVL& arbol) {
    std::ostringstream oss;
    ResultadoConsulta compra = arbol.mejorCompra();
    ResultadoConsulta venta  = arbol.mejorVenta();

    oss << "Mejor compra: " << aTexto(compra, false) << "\n";
    oss << "Mejor venta: "  << aTexto(venta,  true)  << "\n";
    oss << "Arbol (inorden): "
        << inordenATexto(arbol.recorridoInorden());
    return oss.str();
}
// 01_insertar_simple
static void caso01() {
    ArbolAVL arbol;
    arbol.insertar(50);

    std::string esperado =
        "Mejor compra: 50\n"
        "Mejor venta: ninguna\n"
        "Arbol (inorden): 50";
    verificar("01_insertar_simple",
              estadoATexto(arbol), esperado);
}

// 02_arbol_vacio
static void caso02() {
    ArbolAVL arbol;

    std::string esperado =
        "Mejor compra: ninguna\n"
        "Mejor venta: ninguna\n"
        "Arbol (inorden): ";
    verificar("02_arbol_vacio",
              estadoATexto(arbol), esperado);
}
// 03_solo_ventas_sin_compra
static void caso03() {
    ArbolAVL arbol;
    arbol.insertar(-80);
    arbol.insertar(-60);
    arbol.insertar(-70);

    std::string esperado =
        "Mejor compra: ninguna\n"
        "Mejor venta: 60\n"
        "Arbol (inorden): -80 -70 -60";
    verificar("03_solo_ventas_sin_compra",
              estadoATexto(arbol), esperado);
}
// 04_eliminar_hoja
static void caso04() {
    ArbolAVL arbol;
    arbol.insertar(50);
    arbol.eliminar(50);

    std::string esperado =
        "Mejor compra: ninguna\n"
        "Mejor venta: ninguna\n"
        "Arbol (inorden): ";
    verificar("04_eliminar_hoja",
              estadoATexto(arbol), esperado);
}
// 05_eliminar_un_hijo
static void caso05() {
    ArbolAVL arbol;
    arbol.insertar(50);
    arbol.insertar(40);
    arbol.insertar(30);
    arbol.eliminar(40);

    std::string esperado =
        "Mejor compra: 50\n"
        "Mejor venta: ninguna\n"
        "Arbol (inorden): 30 50";
    verificar("05_eliminar_un_hijo",
              estadoATexto(arbol), esperado);
}
// 06_eliminar_dos_hijos
static void caso06() {
    ArbolAVL arbol;
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    arbol.insertar(20);
    arbol.insertar(40);
    arbol.eliminar(30);

    std::string esperado =
        "Mejor compra: 70\n"
        "Mejor venta: ninguna\n"
        "Arbol (inorden): 20 40 50 70";
    verificar("06_eliminar_dos_hijos",
              estadoATexto(arbol), esperado);
}
// 07_secuencia_cruce_completa
static void caso07() {
    ArbolAVL arbol;

    arbol.insertar(50);   // COMPRA c1 50
    arbol.insertar(52);   // COMPRA c2 52
    arbol.insertar(-55);  // VENTA v1 55
    arbol.insertar(-53);  // VENTA v2 53

    // VENTA v3 51 -> cruza con compra a 52
    {
        ResultadoConsulta compra = arbol.mejorCompra();
        bool cruza = compra.existe && compra.valor >= 51;
        if (cruza) arbol.eliminar(compra.valor);
    }

    // CANCELAR 50 -> OK (compra)
    if (arbol.buscar(50)) arbol.eliminar(50);

    // COMPRA c3 55 -> cruza con venta a 53
    {
        ResultadoConsulta venta = arbol.mejorVenta();
        bool cruza = venta.existe && 55 >= (-venta.valor);
        if (cruza) arbol.eliminar(venta.valor);
    }

    std::string esperado =
        "Mejor compra: ninguna\n"
        "Mejor venta: 55\n"
        "Arbol (inorden): -55";
    verificar("07_secuencia_cruce_completa",
              estadoATexto(arbol), esperado);
}
// 08_cancelar_inexistente
static void caso08() {
    ArbolAVL arbol;
    arbol.insertar(50);

    bool existe99 = arbol.buscar(99);
    verificar("08_cancelar_inexistente (buscar 99 = false)",
              existe99 ? "true" : "false", "false");

    arbol.eliminar(99);

    std::string esperado =
        "Mejor compra: 50\n"
        "Mejor venta: ninguna\n"
        "Arbol (inorden): 50";
    verificar("08_cancelar_inexistente (estado intacto)",
              estadoATexto(arbol), esperado);
}
// 09_mejor_venta_no_es_minimo
static void caso09() {
    ArbolAVL arbol;
    arbol.insertar(-80);
    arbol.insertar(-60);
    arbol.insertar(-70);

    ResultadoConsulta venta = arbol.mejorVenta();
    verificar("09_mejor_venta_no_es_minimo (existe)",
              venta.existe ? "true" : "false", "true");
    verificar("09_mejor_venta_no_es_minimo (es -60, no -80)",
              std::to_string(-venta.valor), "60");

    std::string esperado =
        "Mejor compra: ninguna\n"
        "Mejor venta: 60\n"
        "Arbol (inorden): -80 -70 -60";
    verificar("09_mejor_venta_no_es_minimo (estado)",
              estadoATexto(arbol), esperado);
}

int main() {
    std::cout << " plan de pruebas - ArbolAVL\n";
    std::cout << "----------------------------------------"<<std::endl;

    caso01();
    std::cout<<std::endl;
    caso02();
    std::cout<<std::endl;
    caso03();
    std::cout<<std::endl;
    caso04();
    std::cout<<std::endl;
    caso05();
    std::cout<<std::endl;
    caso06();
    std::cout<<std::endl;
    caso07();
    std::cout<<std::endl;
    caso08();
    std::cout<<std::endl;
    caso09();
    std::cout<<std::endl;

    std::cout<<std::endl<< "----------------------------------------"<<std::endl;
    std::cout << " resultado: " << pruebasOk << "/" << totalPruebas
              << " verificaciones OK\n";

    return (pruebasOk == totalPruebas) ? 0 : 1;
}
