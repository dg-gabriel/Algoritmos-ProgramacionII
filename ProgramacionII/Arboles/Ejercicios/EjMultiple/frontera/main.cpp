#include <iostream>
#include <map>
#include <sstream>
#include <list>
#include "ArbolN.hpp"

using namespace std;

void leerEntrada(ArbolN<char> &a){
    list<char> padres,hijos;
    char padre,hijo;
    int nInserc;
    cin >> padre;
    cin >> nInserc;
    for(int i=0;i<nInserc;i++){
        cin >> padre >> hijo;
        padres.push_back(padre);
        hijos.push_back(hijo);
    }
    if(nInserc == 0){
        padres.push_back(padre);
    }
    a.llenarPadresHijos(padres,hijos);
}

void imprimirFrontera(list<char> preorden,map<char,list<char> > &hijos){
    for(list<char>::iterator it = preorden.begin();it != preorden.end();++it){
        if(hijos[*it].empty()){
            cout << *it << " ";
        }
    }
    cout << endl;
}

int main(){
    ArbolN<char> arbol;
    leerEntrada(arbol);
    map<char,list<char> >hijos;
    list<char> preorden = arbol.preOrden();
    arbol.mapearHijos(hijos);
    imprimirFrontera(preorden,hijos);

}