#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <cmath>
#include "ArbolBin.hpp"

using namespace std;

void leerEntrada(ArbolBin<int> &a){
    list<int> preorden,inorden;
    string line;
    for(int i=0;i<2;i++){
        getline(cin,line);
        stringstream ss(line);
        int num;
        while(ss >> num){
            if(i == 0){
                preorden.push_back(num);
            }
            else{
                inorden.push_back(num);
            }
        }
    }
    a.llenarPreIn(preorden,inorden);
}

int sumaArbol(int u, map<int, list<int> > &hijos) {
    list<int> &misHijos = hijos[u];

    if (misHijos.empty()) {
        return 0;
    }

    int suma = u;
    for (list<int>::iterator it = misHijos.begin(); it != misHijos.end(); ++it) {
        suma += *it + sumaArbol(*it, hijos);
    }
    cout << suma << endl;
    return suma;
}

bool esMovil(int raiz,map<int,list<int> > &hijos){
    list<int> &misHijos = hijos[raiz];
    if(misHijos.empty()){
        return true;
    }
    if(abs(sumaArbol(misHijos.front(),hijos) - sumaArbol(misHijos.back(),hijos)) != 1){
        return false;
    }
    return esMovil(misHijos.front(),hijos) && esMovil(misHijos.back(),hijos);

}

int main(){
    ArbolBin<int> arbol;
    leerEntrada(arbol);
    map<int,list<int> > hijos;
    arbol.mapearHijos(hijos);
    (esMovil(arbol.getRaiz(),hijos)) ? cout << "El arbol dado es movil" : cout << "El arbol dado no es movil";
    cout << "." << endl;
}