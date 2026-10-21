#include <iostream>
#include "ArbolBin.hpp"
#include <list>
#include <sstream>

using namespace std;

void leerEntrada(ArbolBin<char> &arbol,int &n,int &m){
    list<char> inorden,otro;
    string line,tag,otroTag;
    char nombre;
    stringstream ss;
    int nNodos;
    cin >> nNodos >> n >> m;
    cout << nNodos << n << m << endl;
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

    if(otroTag == "PREORDEN"){
        arbol.llenarPreIn(otro,inorden);
    }
    else{
        arbol.llenarPostIn(otro,inorden);
    }
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        ArbolBin<char> arbol;
        int n,m;
        leerEntrada(arbol,n,m);
        arbol.imprimirArbol();
    }
}