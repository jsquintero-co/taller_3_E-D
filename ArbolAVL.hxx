// (ArbolAVL.h ya esta incluido: este archivo se incluye desde su
// final). Todas las funciones son TODO. Si agrega funciones nuevas
// aqui, marquelas 'inline' para evitar errores de multiples
// definiciones al enlazar (ver nota en el README).

inline ArbolAVL::ArbolAVL() : raiz_(nullptr) {}

//Se destruye en posOrden (izquierda, derecha y luego padre)
inline void ArbolAVL::destruir(Nodo* nodo){
    if (nodo == nullptr){
        return;
    }

    destruir(nodo->izquierdo);
    destruir(nodo->derecho);

    delete nodo;
}


inline ArbolAVL::~ArbolAVL() {
    // TODO(Estudiante): libere la memoria de todos los nodos del
    // arbol (recorrido postorden: primero los hijos, despues el nodo).
    destruir(raiz_);
}

inline int ArbolAVL::altura(Nodo* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }

    return nodo->altura;
}

inline void ArbolAVL::actualizarAltura(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    nodo->altura = 1 + std::max(
        altura(nodo->izquierdo),
        altura(nodo->derecho)
    );
}

/*Se usa la fórmula de: alutra(izquierda) - altura(derecha)
  Y se sabe que está bien balanceado cuando -1 <= FE <= 1*/
inline int ArbolAVL::factorEquilibrio(Nodo* nodo) const{
    if(nodo == nullptr){
        return 0;
    }

    return altura(nodo->izquierdo) - altura(nodo->derecho); 
}

inline ArbolAVL::Nodo* ArbolAVL::rotarIzquierda(Nodo* nodo){
    Nodo* nuevoRaiz = nodo->derecho;
    Nodo* subarbol = nuevoRaiz->izquierdo;

    nuevoRaiz->izquierdo = nodo;
    nodo->derecho = subarbol;

    actualizarAltura(nodo);
    actualizarAltura(nuevoRaiz);

    return nuevoRaiz;
}


inline ArbolAVL::Nodo* ArbolAVL::rotarDerecha(Nodo* nodo){
    Nodo* nuevoRaiz = nodo->izquierdo;
    Nodo* subarbol = nodo->derecho;

    nuevoRaiz->derecho = nodo;
    nodo->izquierdo = subarbol;

    actualizarAltura(nodo);
    actualizarAltura(nuevoRaiz);

    return nuevoRaiz;
}


inline ArbolAVL::Nodo* ArbolAVL::balancear(Nodo* nodo){
    if (nodo == nullptr){
        return;
    }

    actualizarAltura(nodo);

    int factor = factorEquilibrio(nodo);

    //Caso izquierdo-izquierdo
    if(factor > 1 && factorEquilibrio(nodo->izquierdo) >= 0){
        return rotarDerecha(nodo);
    }

    //Caso derecho-derecho
    if(factor < -1 && factorEquilibrio(nodo->derecho) <= 0){
        return rotarDerecha(nodo);
    }

    //Caso izqueirda-derecha
    if(factor > 1 && factorEquilibrio(nodo->izquierdo) < 0){
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }

    //Caso derecha-izquierda
    if(factor < -1 && factorEquilibrio(nodo->derecho) > 0){
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}


inline ArbolAVL::Nodo* ArbolAVL::insertar(Nodo* nodo, int valor) {
    // Encontramos la posición donde insertar
    if (nodo == nullptr) {
        Nodo* nuevo = new Nodo;
        nuevo->valor = valor;
        nuevo->altura = 1;
        nuevo->izquierdo = nullptr;
        nuevo->derecho = nullptr;

        return nuevo;
    }

    // Insertar en el subárbol izquierdo
    if (valor < nodo->valor) {
        nodo->izquierdo = insertar(nodo->izquierdo, valor);
    }
    // Insertar en el subárbol derecho
    else if (valor > nodo->valor) {
        nodo->derecho = insertar(nodo->derecho, valor);
    }
    // Si ya existe, no hacemos nada
    else {
        return nodo;
    }

    // Al regresar de la recursión, actualizamos y balanceamos
    return balancear(nodo);
}

//Mínimo nodo del sub-árbol
inline ArbolAVL::Nodo* ArbolAVL::minimo(Nodo* nodo) {
    while (nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }

    return nodo;
}


inline void ArbolAVL::insertar(int valor) {
    raiz_ = insertar(raiz_, valor);
}

//Eliminar
inline ArbolAVL::Nodo* ArbolAVL::eliminar(Nodo* nodo, int valor) {
    // El valor no está en el árbol
    if (nodo == nullptr) {
        return nullptr;
    }

    // Buscar en el subárbol izquierdo
    if (valor < nodo->valor) {
        nodo->izquierdo = eliminar(nodo->izquierdo, valor);
    }

    // Buscar en el subárbol derecho
    else if (valor > nodo->valor) {
        nodo->derecho = eliminar(nodo->derecho, valor);
    }

    // Encontramos el nodo
    else {

        // Caso 1: no tiene hijos
        if (nodo->izquierdo == nullptr &&
            nodo->derecho == nullptr) {

            delete nodo;
            return nullptr;
        }

        // Caso 2: solamente tiene hijo derecho
        if (nodo->izquierdo == nullptr) {
            Nodo* temporal = nodo->derecho;

            delete nodo;
            return temporal;
        }

        // Caso 3: solamente tiene hijo izquierdo
        if (nodo->derecho == nullptr) {
            Nodo* temporal = nodo->izquierdo;

            delete nodo;
            return temporal;
        }

        // Caso 4: tiene dos hijos
        Nodo* sucesor = minimo(nodo->derecho);

        nodo->valor = sucesor->valor;

        nodo->derecho = eliminar(nodo->derecho, sucesor->valor);
    }

    // Actualizar altura y rebalancear
    return balancear(nodo);
}

inline void ArbolAVL::eliminar(int valor) {
    raiz_ = eliminar(raiz_, valor);
}


//Falta buscar() y mejorCompra(), mejorVenta() y recorridoInorden()

//Compara el nodo actual, Si es menor busca por izquierda, si es mayor por derecha
inline bool ArbolAVL::buscar(int valor) const {
    return buscar(raiz_, valor);
}

inline bool ArbolAVL::buscar(Nodo* nodo, int valor) const {
    if (nodo == nullptr) {
        return false;
    }

    if (valor == nodo->valor) {
        return true;
    }

    if (valor < nodo->valor) {
        return buscar(nodo->izquierdo, valor);
    }

    return buscar(nodo->derecho, valor);
}


//Valores postivios (el valor más grande)
//Osea, el máximo es el nodo de más a la derecha
inline ResultadoConsulta ArbolAVL::mejorCompra() const {
    Nodo* actual = raiz_;

    while (actual != nullptr && actual->derecho != nullptr) {
        actual = actual->derecho;
    }

    if (actual == nullptr || actual->valor <= 0) {
        return ResultadoConsulta{false, 0};
    }

    return ResultadoConsulta{true, actual->valor};
}


/*Se representan con valores negativos, la mejor venta es la que más
Cerca está de 0*/
inline ResultadoConsulta ArbolAVL::mejorVenta() const {
    Nodo* actual = raiz_;
    Nodo* candidato = nullptr;

    while (actual != nullptr) {
        if (actual->valor < 0) {
            candidato = actual;
            actual = actual->derecho;
        }
        else {
            actual = actual->izquierdo;
        }
    }

    if (candidato == nullptr) {
        return ResultadoConsulta{false, 0};
    }

    return ResultadoConsulta{true, candidato->valor};
}

//  

inline std::list<int> ArbolAVL::recorridoInorden() const {
    std::list<int> lista;
    recorridoInorden(raiz_, lista);

    return lista;
}

inline void ArbolAVL::recorridoInorden(
    Nodo* nodo,
    std::list<int>& lista
) const {
    if (nodo == nullptr) {
        return;
    }

    recorridoInorden(nodo->izquierdo, lista);
    lista.push_back(nodo->valor);
    recorridoInorden(nodo->derecho, lista);
}