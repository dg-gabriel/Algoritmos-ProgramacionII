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

//  buscar el camino entre dos nodos
bool buscarCamino(string u, string destino, map<string, list<string> > &hijos, list<string> &camino) {
    camino.push_back(u);
    if (u == destino) return true;

    list<string> &misHijos = hijos[u];
    for (list<string>::iterator it = misHijos.begin(); it != misHijos.end(); ++it) {
        if (buscarCamino(*it, destino, hijos, camino)) {
            return true;
        }
    }

    camino.pop_back(); // No estaba por esta rama, retrocedemos
    return false;
}


// Ejemplo: Contar hojas (o sumar pesos) que cuelgan de 'u'
int acumularSubarbol(string u, map<string, list<string> > &hijos) {
    list<string> &misHijos = hijos[u];

    // Si la lista de hijos está vacía, 'u' es una HOJA
    if (misHijos.empty()) {
        return 1; // Caso base de hoja
    }

    int suma = 0; // (O pon suma = valor[u] si también quieres sumar a los padres)
    for (list<string>::iterator it = misHijos.begin(); it != misHijos.end(); ++it) {
        suma += acumularSubarbol(*it, hijos);
    }
    return suma;
}