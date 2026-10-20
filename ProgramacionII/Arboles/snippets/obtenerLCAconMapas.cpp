#include <iostream>
#include <map>
#include <string>
using namespace std;

// Devuelve el Ancestro Común Más Cercano (LCA) entre u y v en O(altura)
// Pre condicion: mapa de niveles y mapa de padres del arbol, u y v deben pertenecer al arbol
string obtenerLCAMapas(string u, string v, map<string, string> &padres, map<string, int> &niveles) {
    // 1. Igualamos los pisos: el que esté más profundo sube a su padre
    while (niveles[u] > niveles[v]) {
        u = padres[u];
    }
    while (niveles[v] > niveles[u]) {
        v = padres[v];
    }
    
    // 2. Ahora que están en el mismo piso, suben juntos hasta encontrarse
    while (u != v) {
        u = padres[u];
        v = padres[v];
    }
    
    // 3. Cuando chocan, 'u' (o 'v', que valen lo mismo) es el LCA
    return u;
}

int main(){

}