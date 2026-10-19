#include <iostream>
#include <map>
#include "ArbolN.hpp"

// Llenas el mapa una sola vez con recursión:
void mapearNiveles(ArbolN<string> a, int nivActual, map<string, int> &mapaNivel) {
    if (a.esNulo()) return;

    // Asociamos el nombre de la raíz actual con su nivel
    mapaNivel[a.getRaiz()] = nivActual;

    // Bajamos a los hijos sumando 1 al nivel
    list<ArbolN<string> > hijos = a.getHijos();
    for (list<ArbolN<string> >::iterator it = hijos.begin(); it != hijos.end(); ++it) {
        mapearNiveles(*it, nivActual + 1, mapaNivel);
    }
}

int main(){
    ArbolN<string> miArbol;
    // uso en el main
    map<string, int> nivel;
    mapearNiveles(miArbol, 0, nivel); // La raíz arranca en nivel 0

    // Ahora puedes responder cualquier consulta al instante:
    cout << "El nivel de Eustaquio es: " << nivel["Eustaquio"] << endl;
    if (nivel["Casimiro"] == nivel["Ruperta"]) {
        cout << "Estan en el mismo nivel!" << endl;
    }
}
