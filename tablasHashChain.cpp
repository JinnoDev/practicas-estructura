#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
using namespace std;

// Chaining
class TablaHash {
private:
    static const int TAM = 10;
    vector<list<pair<string, int>>> tabla;
    int funcionHash(string key) const; // Ya

public:
    TablaHash();

    void insertar(string key, int valor); // Ya
    void eliminar(string key); // Ya
    int buscar(string key) const; // Ya
    bool existe(string key) const; // Ya
    void mostrarTabla() const; // Ya
};

TablaHash::TablaHash() : tabla(TAM){}

int TablaHash::funcionHash(string key) const {
    unsigned long suma = 0;
    unsigned long primo = 31;
    unsigned long potencia = 1;

    // Ciclo for que va de 0 hasta la cantidad de caracteres de la key
    for (int i = 0; i < key.length(); i++) {
        suma += static_cast<int>(key[i]) * potencia; // suma de el codigo ASCII la llave
        potencia *= primo;
    }

    return static_cast<int>(suma % TAM); // Devuelve la key hasheada
}

void TablaHash::insertar(string key, int valor) {
    bool flag = false;
    int pos = funcionHash(key);

    // verificacion de que el valor no exista
    for (auto& par : tabla[pos]) {
        if (par.first == key) {
            par.second = valor; // actualizar la tabla con el nuevo valor
            flag = true;
            break;
        }
    }

    if (!flag) {
        tabla[pos].push_back(make_pair(key,valor));
    }
}

int TablaHash::buscar(string key) const {
    int pos = funcionHash(key);

    for (const auto& elemento : tabla[pos]) {
        if (elemento.first == key) {
            return elemento.second;
        }
        return -1; // elemento no encontrado
    }
}

bool TablaHash::existe(string key) const {
    int pos = funcionHash(key);

    for (const auto& elemento : tabla[pos]) {
        if (elemento.first == key) {
            return true;
        }
    }
    return false;
}

void TablaHash::mostrarTabla() const {
    for (int i = 0; i < TAM; i++) {
        cout << "[" << i << "]: ";

        for (const auto& elemento : tabla[i]) {
            cout << "("<< elemento.first << "," << elemento.second << ") ->";
        }
    cout << "null" << endl;
    }
}

void TablaHash::eliminar(string key) {
    int pos = funcionHash(key);

    for (auto i = tabla[pos].begin(); i != tabla[pos].end(); i++) {
            if (i->first == key) {
                tabla[pos].erase(i);
                return;
            }
    }
}
