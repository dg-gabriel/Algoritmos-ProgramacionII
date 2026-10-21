// Ej. Parcial 2013
// "Niveles"
// es trivial con el metodo recorridoPorNiveles()
// solo es imprimir los niveles entre n y m incluyendoles
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

void imprimirNiveles(ArbolBin<char> &a,int n,int m){
    list<list<char> > rec = a.recorridoPorNiveles();
    for(int i=0;i<n;i++){
        rec.pop_front();
    }
    for(int i=n;i<=m;i++){
        list<char> niv = rec.front();
        for(list<char>::iterator it = niv.begin();it != niv.end();++it){
            cout << *it << " ";
        }
        rec.pop_front();
    }
    
    cout << endl;
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        ArbolBin<char> arbol;
        int n,m;
        leerEntrada(arbol,n,m);
        cout << "Caso #" << i+1 << " ";
        imprimirNiveles(arbol,n,m);
    }
}