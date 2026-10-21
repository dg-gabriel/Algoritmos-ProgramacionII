#include <iostream>
#include <map>
#include <sstream>
#include <list>
#include "ArbolBin.hpp"

using namespace std;

bool leerEntrada(ArbolBin<int> &a){
    list<int> inorden,otro;
    string line,tag,otroTag;
    int nodo;
    stringstream ss;
    for(int i=0;i<2;i++){
        if(!(getline(cin >> ws,line))) return false;
        ss.clear();
        ss.str(line);
        ss >> tag;
        int nNodos;
        ss >> nNodos;
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
    return true;
}

bool esCompleto(map<int,list<int> >&hijos){
    for(map<int,list<int> >::iterator it = hijos.begin();it != hijos.end();++it){
        if(!(it->second.empty())){
            if(it->second.size() < 2){
                return false;
            }
        }
    }
    return true;
}

int main(){
    ArbolBin<int> arbol;
    while(leerEntrada(arbol)){
        map<int,list<int> > hijos;
        arbol.mapearHijos(hijos);
        (esCompleto(hijos)) ? cout << "ES completo" : cout << "NO es completo";
        cout << endl;
    }
}