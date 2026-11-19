// Ej. Renos Zombi
// Encontrar los puentes del grafo
#include <iostream>
#include <map>
#include "GrafoNoDir.hpp"

using namespace std;

void leerEntrada(GrafoNoDir<string> &g){
    map<string,bool> insertados;
    string origen,dest;
    while(cin >> origen >> dest){
        if(!insertados[origen]){
            g.insertarVertice(origen);
            insertados[origen] = true;
        }
        if(!insertados[dest]){
            g.insertarVertice(dest);
            insertados[dest] = true;
        }
        g.insertarArco(origen,dest,1);
    }
}

void imprimirSalida(list<list<string> > &salida){
    for(list<list<string> >::iterator it = salida.begin(); it != salida.end(); ++it){
        cout << it->front() << " " << it->back() << endl;
    }
}

int main(){
    GrafoNoDir<string> mapa;
    leerEntrada(mapa);
    list<list<string> > puentes = mapa.getPuentes();
    imprimirSalida(puentes);
}