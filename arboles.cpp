#include <iostream>
using namespace std;

// Estructura de nodo arbol
struct Nodo {
    int dato;
    Nodo *derecha;
    Nodo *izquierda;
};

Nodo *crearNodo(int n) {
    Nodo *nuevoNodo = new Nodo();

    nuevoNodo -> dato = n;
    nuevoNodo -> derecha = NULL;
    nuevoNodo -> izquierda = NULL;

    return nuevoNodo;
}

Nodo * arbol = NULL;

void insertar(Nodo *&arbol, int n) {

    // Si el arbol esta vacio
    if (arbol == NULL) {
        Nodo * nuevoNodo = crearNodo(n);
        arbol = nuevoNodo;
    } else {
        int valorRaiz = arbol -> dato;
        if (n < valorRaiz) {
            insertar(arbol -> izquierda,n);
        } else {
            insertar(arbol -> derecha, n);
        }
    }
}