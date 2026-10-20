// Ej. Parcial 2026
// "Ruta de Defensa"
// divise la solucion yo solo
// funciona pero desborda en casos extremos 
//se puede hacer mas optimo usando un vector como lista de adyacencia
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
        // debes optimizar esto, lee primero el padre y luego el hijo, si el arbol tiene un solo nodo la lectura falla
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
        // corta la recursividad si en una rama el valor baja por debajo de cero
        return -1;
    }
    list<ArbolN<int> > hijos = a.getHijos();
    int caminos = 0;
    for(list<ArbolN<int> >::iterator it = hijos.begin(); it != hijos.end(); ++it){
        caminos += 1 + obtenerEstabilidad(*it,values,acum + values[a.getRaiz()]);   
    }
    return caminos;
    // recursivo = hola demonio, se va a desbordar en casos grandes
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
        if(arbol.getPeso() == 0){
            cout << 0;
        }
        else{
            int alcance = obtenerEstabilidad(arbol,values,0)+1;
            // condicion ? si_cumple : si no cumple
            (alcance < 0) ? cout << 0 : cout << alcance;
            
        }
        cout << endl;
        
    }
}