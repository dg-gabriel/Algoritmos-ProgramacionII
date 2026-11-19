// Ej. Aeropuertos
// Backtracking - Encontrar la mayor cantidad de vertices de forma que ninguno de la lista tenga adyacencia
// entre si
#include <iostream>
#include <list>
#include <map>
#include <string>
#include "GrafoNoDir.hpp"

using namespace std;

void leerEntrada(GrafoNoDir<string> &g){
    map<string, bool> insertados;
    string origen, dest;
    while(cin >> origen >> dest){
        if(!insertados[origen]){
            g.insertarVertice(origen);
            insertados[origen] = true;
        }
        if(!insertados[dest]){
            g.insertarVertice(dest);
            insertados[dest] = true;
        }
        g.insertarArco(origen, dest, 0);
    }
}

void mayorCantSeparadosAux(GrafoNoDir<string> &g,list<string>::iterator it,const list<string>::iterator &fin,int restantes,map<string, int> &bloqueados,list<string> &res,list<string> &mejor){
    // Caso base: se evaluaron todos los vértices del grafo
    if(it == fin){
        if(res.size() > mejor.size()){
            mejor = res;
        }
        return;
    }

    string v = *it;
    list<string>::iterator sig = it;
    ++sig;

    // RAMA A: INCLUIR 'v' (solo si ningún vecino ya elegido lo bloqueó)
    if(bloqueados[v] == 0){
        res.push_back(v);

        list<string> vecinos = g.getVecinos(v);
        list<string>::iterator jt;
        for(jt = vecinos.begin(); jt != vecinos.end(); ++jt){
            bloqueados[*jt]++;
        }

        mayorCantSeparadosAux(g, sig, fin, restantes - 1, bloqueados, res, mejor);

        // Backtrack: deshacer exactamente lo hecho arriba
        for(jt = vecinos.begin(); jt != vecinos.end(); ++jt){
            bloqueados[*jt]--;
        }
        res.pop_back();
    }

    // RAMA B: NO INCLUIR 'v' (probar saltar este vértice para ver si deja espacio a más vecinos)
    mayorCantSeparadosAux(g, sig, fin, restantes - 1, bloqueados, res, mejor);
}

list<string> mayorCantSeparados(GrafoNoDir<string> &g){
    list<string> res, mejor;
    list<string> vertices = g.getVertices();
    map<string, int> bloqueados;

    mayorCantSeparadosAux(g, vertices.begin(), vertices.end(), g.getNVertices(), bloqueados, res, mejor);
    return mejor;
}

void imprimirSalida(list<string> &res){
    for(list<string>::iterator it = res.begin(); it != res.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

int main(){
    GrafoNoDir<string> mapa;
    leerEntrada(mapa);
    list<string> res = mayorCantSeparados(mapa);
    imprimirSalida(res);
    return 0;
}