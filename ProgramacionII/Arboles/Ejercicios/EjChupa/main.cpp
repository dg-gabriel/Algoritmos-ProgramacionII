// Ej. Parcial 2025
// "CHUPA"
// semerenda fumada
// de vaina usa arboles
// no cumple completamente con el enunciado, no da los valores esperados en MSI
#include <iostream>
#include <vector>
#include <list>
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

int calcularMSI(map<int,int> &niveles,vector<int> &values){
    int maxMSI = 0;
    map<int,list<int> > mapaInvertido;

    // invertimos el mapa para que dado un nivel, retorne la lista de nodos de ese nivel
    // (Es lo mismo que hacer un recorrido por niveles)
    for(map<int, int>::iterator it = niveles.begin(); it != niveles.end(); ++it){
        int nivelDelNodo = it->second;  
        int valorNodo = it->first;   
    
        mapaInvertido[nivelDelNodo].push_back(valorNodo);
    }

    for(int i=0;i<mapaInvertido.size();i++){
        // recorremos por niveles
        list<int> nivelAct = mapaInvertido[i];
        int MSI = 0;
        for(list<int>::iterator it = nivelAct.begin(); it != nivelAct.end(); ++it){
            // por cada valor de un nivel consultamos el vector de valores y lo anadimos al total
            MSI += values[*it];
        }
        if(MSI > maxMSI){
            maxMSI = MSI;
        }
    }
    // retornamos la suma maxima entre todos los niveles
    return maxMSI;
}

int calcularBalance(map<int,list<int> > &mapaHijos,map<int,int> &niveles){
    int nPares = 0,nImp = 0;
    // recorremos el mapa de hijos, y si hay un nodo cuyo mapa de hijos este vacio, es una hoja
    for(map<int,list<int> >::iterator it = mapaHijos.begin(); it != mapaHijos.end(); ++it){
        if(it->second.empty()){
            // si es una hoja revisamos el mapa de niveles para saber si es par
            if(niveles[it->first] % 2 == 0){
                nPares++;
            }
            else{
                nImp++;
            }
        }
    }
    return nPares - nImp;
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        int nNodos;
        cin >> nNodos;
        ArbolN<int> arbol;
        vector<int> values(nNodos + 1);
        leerEntrada(arbol,values,nNodos);
        map<int,int> niveles;
        map<int,list<int> > hijos;
        arbol.mapearNiveles(niveles);
        arbol.mapearHijos(hijos);
        int result = calcularMSI(niveles,values) * calcularBalance(hijos,niveles);
        cout << result << endl;
    }
}


