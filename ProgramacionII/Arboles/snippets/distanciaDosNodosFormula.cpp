#include <iostream>
#include <map>
#include <string>
using namespace std;

// pre condicion: tener el LCA de u y v, y el mapa de niveles del arbol
// u y v deben, obviamente, pertenecer al arbol
// Calcula la distancia en cantidad de aristas entre u y v
int calcularDistancia(string u, string v, string lca, map<string, int> &niveles) {
    return niveles[u] + niveles[v] - 2 * niveles[lca];
}