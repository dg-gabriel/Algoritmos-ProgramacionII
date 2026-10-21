// Ej. Parcial 2014
// "Diametro de un arbol"
// version con mapeo de arboles, me costo mucho
// me cuesta mucho hacer las cosas con mapas
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include "ArbolBin.hpp"

using namespace std;

void leerEntrada(ArbolBin<int> &a){
    list<int> inorden,otro;
    string line,tag,otroTag;
    int nodo;
    stringstream ss;
    int nNodos;
    cin >> nNodos;
    for(int i=0;i<2;i++){
        getline(cin >> ws,line);
        ss.clear();
        ss.str(line);
        ss >> tag;
        while(ss >> nodo){
            if(tag == "INORDEN"){
                inorden.push_back(nodo);
            }
            else{
                otroTag = tag;
                otro.push_back(nodo);
            }
        }
    }

    if(otroTag == "PREORDEN"){
        a.llenarPreIn(otro,inorden);
    }
    else{
        a.llenarPostIn(otro,inorden);
    }
}

int getDiameter(int u, map<int, list<int> > &mapaHijos, int &maxDiam){
    list<int> &hijos = mapaHijos[u];
    int mayor1 = 0, mayor2 = 0;
    for(list<int>::iterator it = hijos.begin(); it != hijos.end(); ++it){
        int h = 1 + getDiameter(*it, mapaHijos, maxDiam);
        if(h > mayor1){
            mayor2 = mayor1;
            mayor1 = h;
        }
        else if(h > mayor2){
            mayor2 = h;
        }
    }
    int diamLocal = mayor1 + mayor2;
    if(diamLocal > maxDiam){
        maxDiam = diamLocal;
    }
    return mayor1;
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        ArbolBin<int> arbol;
        leerEntrada(arbol);
        int diametro = 0;
        if(arbol.esNulo()){
            diametro = -1;
        }
        else{
            map<int,list<int> > hijos;
            arbol.mapearHijos(hijos);
            getDiameter(arbol.getRaiz(),hijos,diametro);
        }
        
        cout << "El diametro del arbol #" << i+1 << " es " << diametro << "." << endl;
    }
}