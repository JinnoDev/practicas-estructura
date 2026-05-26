#include <float.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
using namespace std;

// Tablas hash con direccionamiento abierto lineal

enum Estado {VACIO, OCUPADO, ELIMINADO};

class tablasHash {
private:
    static const int TAM = 10;
    vector<pair<pair<string, int>, Estado>> tabla;
    int funcionHash(string key) const; // Ya

public:
    tablasHash();

    bool existe(string key) const; // Ya
    void insertar(string key, int value); // Ya
    int buscar(string key) const; // Ya
    void mostrarTabla() const; // Ya
    void eliminarElemento(string key); //
};

tablasHash::tablasHash() : tabla(TAM, make_pair(make_pair("", 0), VACIO)) {}

int tablasHash::funcionHash(string key) const {
    unsigned long suma = 0;
    unsigned long primo = 31;
    unsigned long potencia = 1;

    for (int i = 0; i < key.length(); i++) {
        suma += static_cast<int>(key[i]) * potencia;
        potencia *= primo;
    }

    return static_cast<int>(suma % TAM);
}

bool tablasHash::existe(string key) const {
    int pos = funcionHash(key);
    int origen = pos;

    do {
        if (tabla[pos].second == OCUPADO && tabla[pos].first.first == key) {
            return true;
        }
        else if (tabla[pos].second == VACIO) {
            return false;
        }

        pos = (pos + 1) % TAM;
    } while (pos != origen);

    return false;
}

void tablasHash::insertar(string key, int value) {
    int pos = funcionHash(key);
    int origen = pos;

    do {
        if (tabla[pos].second == OCUPADO && tabla[pos].first.first == key) {
            tabla[pos].first.second = value;
            return;
        }

        if (tabla[pos].second == VACIO || tabla[pos].second == ELIMINADO) {
            tabla[pos].first.first = key;
            tabla[pos].first.second = value;
            return;
        }

        pos = (pos + 1) % TAM;
    } while (pos != origen);
    cout << "Error." << endl;
}

int tablasHash::buscar(string key) const {
    int pos = funcionHash(key);
    int origen = pos;

    do {
        if (tabla[pos].first.first == key && tabla[pos].second == OCUPADO) {
            return tabla[pos].first.second;
        }

        if (tabla[pos].second == VACIO) {
            return -1;
        }
        pos = (pos + 1) % TAM;
    } while (pos != origen);
}

void tablasHash::mostrarTabla() const {
    // Recorremos el vector principal posición por posición
    for (int i = 0; i < TAM; i++) {
        // Imprimimos el índice actual de forma genérica
        cout << "[" << i << "]: ";

        // Evaluamos el estado de la casilla actual usando un switch o un if
        switch (tabla[i].second) {
            case OCUPADO:
                // Si está ocupada, mostramos los datos reales
                cout << "(" << tabla[i].first.first << ", " << tabla[i].first.second << ")" << endl;
                break;

            case VACIO:
                // Si está vacía, usamos una etiqueta genérica clara
                cout << "VACIO" << endl;
                break;

            case ELIMINADO:
                // Si fue eliminada, también lo indicamos de forma genérica
                cout << "ELIMINADO" << endl;
                break;
        }
    }
}

void tablasHash::eliminarElemento(string key) {
    int pos = funcionHash(key);
    int origen = pos;

    do {
        if (tabla[pos].first.first == key && tabla[pos].second == OCUPADO) {
            tabla[pos].first.first.clear();
            tabla[pos].first.second = 0;
            tabla[pos].second = ELIMINADO;
            return;
        }
        if (tabla[pos].second == VACIO) {
            return;
        }

        pos = (pos + 1) % TAM;
    } while (pos != origen);
}

