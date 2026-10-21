#include <iostream>
#include "ArbolBin.hpp"
#include <list>
#include <sstream>

using namespace std;

void leerEntrada(ArbolBin<string> &arbol,string &u,string &v){
    list<string> inorden,otro;
    string line,tag,otroTag,nombre;
    stringstream ss;
    for(int i=0;i<2;i++){
        getline(cin >> ws,line);
        ss.clear();
        ss.str(line);
        ss >> tag;
        
        while(ss >> nombre){
            if(tag == "INORDEN"){
                inorden.push_back(nombre);
            }
            else{
                otroTag = tag;
                otro.push_back(nombre);
            }
        }
    }

    cin >> u >> v;

    if(otroTag == "PREORDEN"){
        arbol.llenarPreIn(otro,inorden);
    }
    else{
        arbol.llenarPostIn(otro,inorden);
    }
}