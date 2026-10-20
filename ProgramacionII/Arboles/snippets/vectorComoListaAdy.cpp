// resuelve el ejercicio de base de defensa
// utilizando un vector como lista de adyacencia
#include <iostream>
#include <list>
#include <vector>
#include "ArbolN.hpp"

using namespace std;

void leerEntrada(ArbolN<int> &a, vector<int> &values, vector<list<int> > &hijosRapidos, int nNodos){
    list<int> padresTDA, hijosTDA;
    int padre, hijo;
    
    for(int i = 1; i <= nNodos; i++){
        cin >> values[i];
    }
    
    for(int i = 0; i < nNodos - 1; i++){
        cin >> padre >> hijo;
        padresTDA.push_back(padre);
        hijosTDA.push_back(hijo);
        
        // Guardamos a los hijos en un vector directo para el DFS
        hijosRapidos[padre].push_back(hijo); 
    }
    
    a.llenarPadresHijos(padresTDA, hijosTDA);
}

// MISMA LOGICA pero caminando por indices en vez de clonar subárboles
int obtenerEstabilidad(int u, vector<list<int> > &hijosRapidos, vector<int> &values, int acum){
    // Condicion de quiebre (Inestabilidad)
    if(acum + values[u] < 0){
        return -1;
    }
    
    int caminos = 0;
    // Iteramos sobre los hijos ligeros en O(1)
    for(list<int>::iterator it = hijosRapidos[u].begin(); it != hijosRapidos[u].end(); ++it){
        int hijo = *it;
        caminos += 1 + obtenerEstabilidad(hijo, hijosRapidos, values, acum + values[u]);   
    }
    
    return caminos;
}

int main(){
    int nCasos;
    if(!(cin >> nCasos)) return 0;
    
    for(int i = 0; i < nCasos; i++){
        ArbolN<int> arbol;
        int nNodos;
        cin >> nNodos;
        
        vector<int> values(nNodos + 1);
        vector<list<int> > hijosRapidos(nNodos + 1); // El mapa de atajos
        
        leerEntrada(arbol, values, hijosRapidos, nNodos);
        
        // La raíz siempre es 1 
        int alcance = obtenerEstabilidad(1, hijosRapidos, values, 0) + 1;
        
        (alcance < 0) ? cout << 0 : cout << alcance;
        cout << endl;
    }
}