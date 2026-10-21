#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;

void preOrdenMapa(int u, map<int, list<int> > &mapaHijos) {
    // 1. PROCESAR EL NODO ACTUAL (Raíz del subárbol)
    cout << u << " "; 

    // 2. BAJAR A TODOS LOS HIJOS
    list<int> &hijos = mapaHijos[u];
    for (list<int>::iterator it = hijos.begin(); it != hijos.end(); ++it) {
        preOrdenMapa(*it, mapaHijos);
    }
}

void postOrdenMapa(int u, map<int, list<int> > &mapaHijos) {
    // 1. BAJAR A TODOS LOS HIJOS PRIMERO
    list<int> &hijos = mapaHijos[u];
    for (list<int>::iterator it = hijos.begin(); it != hijos.end(); ++it) {
        postOrdenMapa(*it, mapaHijos);
    }

    // 2. PROCESAR EL NODO ACTUAL (Cuando ya regresó de todos sus hijos)
    cout << u << " "; 
}

void inOrdenMapa(int u, map<int, list<int> > &mapaHijos) {
    list<int> &hijos = mapaHijos[u];

    // Si es una hoja (no tiene hijos), solo procesamos el nodo y salimos
    if (hijos.empty()) {
        cout << u << " ";
        return;
    }

    list<int>::iterator it = hijos.begin();

    // 1. BAJAR AL PRIMER HIJO (Hijo Izquierdo)
    inOrdenMapa(*it, mapaHijos);

    // 2. PROCESAR EL NODO ACTUAL (Padre)
    cout << u << " ";

    // 3. BAJAR AL RESTO DE LOS HIJOS (Hermanos derechos)
    ++it; 
    for (; it != hijos.end(); ++it) {
        inOrdenMapa(*it, mapaHijos);
    }
}