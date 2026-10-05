# JaveBolsa — Código base (Taller 3: Árboles)

## Qué debe completar

Todo `ArbolAVL.h` / `ArbolAVL.hxx`: `insertar`, `eliminar` (ambos con
rebalanceo), `buscar`, `mejorCompra`, `mejorVenta`, `recorridoInorden`
y el destructor. No hay nada dado dentro de la clase: es la
implementación completa que pide la Sección 4 del enunciado.

`Lector.cxx` y `main.cpp` ya están completos (la regla de cruce de
compras y ventas no es parte de lo que se evalúa).

## Compilar y ejecutar

```
g++ -std=c++11 -c *.c *.cxx *.cpp
g++ -std=c++11 -o javebolsa main.o Lector.o
./javebolsa eventos.txt
```

## Casos de prueba

`casos_prueba/` trae 9 casos (árbol vacío, eliminar hoja / un hijo /
dos hijos, cancelar un valor inexistente, y un caso que distingue
`mejorVenta()` de un simple mínimo — vea
`09_mejor_venta_no_es_minimo`). Cada uno trae su `eventos.txt` y la
`salida_esperada.txt` correspondiente:

```
./javebolsa casos_prueba/01_insertar_simple/eventos.txt
```

Recuerde que su documento de diseño debe incluir, además, un plan de
pruebas (Sección 5 del enunciado) con al menos un caso por función —
incluyendo una secuencia que fuerce cada uno de los 4 tipos de
rotación.

## Nota sobre los archivos `.hxx`

No se compilan como archivos independientes: se incluyen al final del
`.h` correspondiente, y por eso sus funciones están marcadas `inline`
— no las quite, o tendrá errores de "múltiples definiciones" al
enlazar.
