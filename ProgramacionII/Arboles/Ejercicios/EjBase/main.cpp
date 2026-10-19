#include <iostream>
#include <list>
#include <vector>
#include "ArbolN.hpp"

using namespace std;

void leerEntrada(ArbolN<int> &a,vector<int> &values,int nNodos){
    list<int> padres,hijos;
    int padre,hijo;
    for(int i=1;i<=nNodos;i++){
        cin >> values[i];
    }
    for(int i=0;i<nNodos-1;i++){
        cin >> padre >> hijo;
        padres.push_back(padre);
        hijos.push_back(hijo);
    }
    a.llenarPadresHijos(padres,hijos);
}

int obtenerEstabilidad(ArbolN<int> &a,vector<int> &values,int acum){
    if(a.esNulo()){
        return 0;
    }
    if(acum + values[a.getRaiz()] < 0){
        return -1;
    }
    list<ArbolN<int> > hijos = a.getHijos();
    int caminos = 0;
    for(list<ArbolN<int> >::iterator it = hijos.begin(); it != hijos.end(); ++it){
        ArbolN<int> hijo = *it;
        caminos += 1 + obtenerEstabilidad(hijo,values,acum + values[a.getRaiz()]);   
    }
    return caminos;
}

int main(){
    int nCasos;

    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        ArbolN<int> arbol;
        int nNodos;
        cin >> nNodos;
        vector<int> values(nNodos + 1);
        leerEntrada(arbol,values,nNodos);
        int alcance = obtenerEstabilidad(arbol,values,0)+1;
        (alcance < 0) ? cout << 0 : cout << alcance;
        cout << endl;
    }
}