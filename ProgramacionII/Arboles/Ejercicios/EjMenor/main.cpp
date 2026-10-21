#include <iostream>
#include <list>
#include <sstream>
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

bool aMenorQueB(ArbolBin<int> &a,ArbolBin<int> &b){
    list<int> listA = a.preOrden();
    int mayorA = listA.front();
    for(list<int>::iterator it = listA.begin(); it != listA.end(); ++it){
        if(*it > mayorA){
            mayorA = *it;
        }
    }
    list<int> listB = b.preOrden();
    int menorB = listB.front();
    for(list<int>::iterator it = listB.begin();it != listB.end(); ++it){
        if(*it < menorB){
            menorB = *it;
        }
    }
    return (mayorA < menorB) ? true : false; 
}

int main(){
    ArbolBin<int> a,b;
    while(leerEntrada(a)){
        leerEntrada(b);
        (aMenorQueB(a,b)) ? cout << "Es menor" : cout << "No es menor";
        cout << endl;
    }
}