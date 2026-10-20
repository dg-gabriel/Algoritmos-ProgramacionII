// convierte un mapa de nombre -> nivel en un mapa de
//                      nivel -> nombre
#include <iostream>
#include <list>
#include "ArbolBin.hpp"
#include <map>

int main(){
    // 1. Tienes tu mapa original (Nombre -> Nivel)
    ArbolBin<string> miArbol;
    map<string, int> niveles;
    miArbol.mapearNiveles(niveles);

    // 2. Creas el mapa invertido (Nivel -> Lista de Nombres)
    map<int, list<string> > nodosPorNivel;

    // 3. Recorres el primer mapa y llenas el segundo
    for(map<string, int>::iterator it = niveles.begin(); it != niveles.end(); ++it){
        int nivelDelNodo = it->second;   // El valor (ej. 2)
        string nombreNodo = it->first;   // La clave (ej. "Carlos")
    
        nodosPorNivel[nivelDelNodo].push_back(nombreNodo);
    }

    cout << "Estudiantes en el Nivel 3: ";
    list<string> capa3 = nodosPorNivel[3];

    for(list<string>::iterator it = capa3.begin(); it != capa3.end(); ++it){
        cout << *it << " ";
    }   
    cout << endl;
}