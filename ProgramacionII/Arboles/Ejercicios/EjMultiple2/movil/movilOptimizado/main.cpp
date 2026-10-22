#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <cmath>
#include "ArbolBin.hpp"

using namespace std;

void leerEntrada(ArbolBin<int> &a){
    list<int> preorden,inorden;
    string line;
    for(int i=0;i<2;i++){
        getline(cin,line);
        stringstream ss(line);
        int num;
        while(ss >> num){
            if(i == 0){
                preorden.push_back(num);
            }
            else{
                inorden.push_back(num);
            }
        }
    }
    a.llenarPreIn(preorden,inorden);
}

int contenido(int u, map<int,list<int> > &h, bool &movil){
    list<int> &hs = h[u];
    int suma = u;                       // el nodo aporta su valor
    int c1 = 0, c2 = 0;                 // contenido de hijo 1 y hijo 2 (ausente = 0)
    int k = 0;                          // cuántos hijos van
    for(list<int>::iterator it = hs.begin(); it != hs.end(); ++it){
        int c = contenido(*it, h, movil);
        suma += c;
        if(k == 0) c1 = c; else c2 = c;
        k++;
    }
    if(k > 0 && abs(c1 - c2) != 1){     // solo nodos con hijos
        movil = false;
    }
    return suma;
}

int main(){
    ArbolBin<int> arbol;
    leerEntrada(arbol);
    map<int,list<int> > hijos;
    arbol.mapearHijos(hijos);
    bool esMovil = true;
    contenido(arbol.getRaiz(),hijos,esMovil);
    (esMovil) ? cout << "El arbol dado es movil" : cout << "El arbol dado no es movil";
    cout << "." << endl;
}