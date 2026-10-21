// Ej. Parcial 2014
// "Diametro de un arbol"
// facil porque ya lo tenia hecho, me cuesta divisar una solucion con mapas
// solo hice la recursiva, que se desborda en casos graves, no cumple con la restriccion lineal del pdf
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

int getDiameter(ArbolBin<int> &a,int &maxDiam){
    if(a.esNulo()){
        return -1;
    }
    int alturaIzq,alturaDer;
    ArbolBin<int> hijoIzq = a.getHijoIzq(),hijoDer = a.getHijoDer();
    alturaIzq = getDiameter(hijoIzq,maxDiam);
    alturaDer = getDiameter(hijoDer,maxDiam);

    int diamLocal = (alturaIzq + 1) + (alturaDer + 1);
    if(diamLocal > maxDiam){
        maxDiam = diamLocal;
    }
    return 1 + max(alturaIzq,alturaDer);
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        ArbolBin<int> arbol;
        leerEntrada(arbol);
        int diametro = 0;
        getDiameter(arbol,diametro);
        cout << "El diametro del arbol #" << i+1 << " es " << diametro << "." << endl;
    }
}