#include "ArbolBin.hpp"
#include "ArbolN.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <list>

using namespace std;

void leerEntrada(ArbolN<int> &tree){
    int padre,hijo;
    list<int> padres,hijos;
    while(cin >> padre >> hijo){
        padres.push_back(padre);
        hijos.push_back(hijo);
    }
    tree.llenarPadresHijos(padres,hijos);    
}

int main(){
    ArbolN<int> sacrificio;
    
    cout << "lectura" << endl;
    clock_t inicio = clock();
    leerEntrada(sacrificio);
    clock_t fin = clock();
    double segundos = double(fin - inicio) / CLOCKS_PER_SEC;
    cerr << "tiempo lectura: " << segundos << " s" << endl;


    cout << "getAltura" << endl;
    inicio = clock();
    cout << sacrificio.getAltura() << endl;
    fin = clock();
    segundos = double(fin - inicio) / CLOCKS_PER_SEC;
    cerr << "tiempo getAltura(): " << segundos << " s" << endl;

    inicio = clock();
    ArbolN<int> otroArbol = sacrificio;
    fin = clock();
    segundos = double(fin - inicio) / CLOCKS_PER_SEC;
    cerr << "tiempo asignacion: " << segundos << " s" << endl;

    cout << "raiz: " << otroArbol.getRaiz() << endl;
}