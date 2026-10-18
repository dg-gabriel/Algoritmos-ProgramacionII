#include <iostream>
#include "ArbolBin.hpp"
#include <list>
#include <map>
#include <sstream>

using namespace std;

void leerEntrada(ArbolBin<int> &arbol,list<int> &conj){
    string rec1,rec2;
    cin >> rec1;
    cout << rec1;
}

int main(){
    int nCasos,nFamilias;

    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        cin >> nFamilias;
        for(int i=0;i<nFamilias;i++){
            ArbolBin<int> arbol;
            list<int> conjQ;
            leerEntrada(arbol,conjQ);
        }
    }
}