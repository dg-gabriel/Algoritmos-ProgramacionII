#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include "ArbolBin.hpp"

using namespace std;

void leerEntrada(ArbolBin<string> &arbol){
    list<string> inorden,otro;
    string otroTag;
    stringstream ss;
    for(int i=0;i<2;i++){
        string line,tag;
        getline(cin >> ws,line);
        for(int i=0;i<line.length();i++){
            if(line[i] == '[' || line[i] == ']' || line[i] == ',' || line[i] == '='){
                line[i] = ' ';
            }
        }
        ss.clear();
        ss.str(line);
        ss >> tag;
        string nodo;
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
        arbol.llenarPreIn(otro,inorden);
    }
    else{
        arbol.llenarPostIn(otro,inorden);
    }
}

list<string> recorridoRata(ArbolBin<string> &arbol){
    queue<ArbolBin<string> > colaAux;
    queue<bool> colaBool;
    ArbolBin<string> hijoIzq,hijoDer;
    stack<string> pilaAux;
    list<string> result;

    if(arbol.esNulo()){
        return result;
    }

    colaAux.push(arbol);
    colaBool.push(true);
    while(!colaAux.empty()){
        hijoIzq = colaAux.front().getHijoIzq();
        hijoDer = colaAux.front().getHijoDer();
        
        if(!hijoIzq.esNulo()){
            colaAux.push(hijoIzq);
            colaBool.push(!colaBool.front());
            if(colaBool.front()){
                pilaAux.push(hijoIzq.getRaiz());
            }
        }
        if(!hijoDer.esNulo()){
            colaAux.push(hijoDer);
            colaBool.push(!colaBool.front());
            if(colaBool.front()){
                pilaAux.push(hijoDer.getRaiz());
            }
        }
        
        if(colaBool.front()){
            result.push_back(colaAux.front().getRaiz());
        }
        else{
            result.push_back(pilaAux.top());
            pilaAux.pop();
        }
        colaAux.pop();
        colaBool.pop();
    }
    return result;
}

int main(){
    int nCasos;
    cin >> nCasos;
    cin >> ws;

    for(int i=0;i<nCasos;i++){
        ArbolBin<string> arbol;
        leerEntrada(arbol);
        list<string> serpentina = recorridoRata(arbol);
        cout << "[";
        for(list<string>::iterator it = serpentina.begin(); it != serpentina.end(); ++it){
            if(it != serpentina.begin()){
                cout << ", ";
            }
            cout << *it;
        }
        cout << "]" << endl;
    }

}

// no adapte del todo bien el recorrido serpentina del prof
// aprendi que stringstream no es tan costoso en memoria como pensaba si se usa sin redeclarar