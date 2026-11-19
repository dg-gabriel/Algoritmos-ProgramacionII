// Parcial: Ruta de Errod
// Backtracking - Encontra el camino de maximo costo posible (retornar el costo no el camino)
#include <iostream>
#include <map>
#include "GrafoNoDir.hpp"

using namespace std;

void leerEntrada(GrafoNoDir<string> &g){
    map<string,bool> insertados;
    string origen,dest;
    float costo;
    while(cin >> origen >> dest >> costo){
        if(!insertados[origen]){
            g.insertarVertice(origen);
            insertados[origen] = true;
        }
        if(!insertados[dest]){
            g.insertarVertice(dest);
            insertados[dest] = true;
        }
        g.insertarArco(origen,dest,costo);
    }
}

void mayorPeligroAux(GrafoNoDir<string> &g,string v,float suma,float &acum,map<string,bool> &visitados){
    if(suma > acum){
        acum = suma;
    }
    visitados[v] = true;
    list<string> vecinos = g.getVecinos(v);
    for(list<string>::iterator it = vecinos.begin(); it != vecinos.end(); ++it){
        string w = *it;
        if(!visitados[w]){
            mayorPeligroAux(g,w,suma + g.getCostoArco(v,w),acum,visitados);
        }
    }
    visitados[v] = false;
}

float mayorPeligro(GrafoNoDir<string> &g){
    float max = -1;
    map<string,bool> visitados;
    list<string> vertices = g.getVertices();
    for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
        string act = *it;
        mayorPeligroAux(g,act,0,max,visitados);
    }
    return max;
}

int main(){
    GrafoNoDir<string> mapa;
    leerEntrada(mapa);
    float max = mayorPeligro(mapa);
    cout << max << endl;
}