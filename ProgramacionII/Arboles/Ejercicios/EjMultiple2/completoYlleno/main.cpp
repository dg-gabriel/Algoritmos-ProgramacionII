#include <iostream>
#include <list>
#include <sstream>
#include <map>
#include "ArbolBin.hpp"

using namespace std;

void leerEntrada(ArbolBin<char> &a){
    list<char> inorden,preorden;
    string rec1,rec2;
    getline(cin,rec1);
    getline(cin,rec2);
    for(string::iterator it = rec1.begin(); it != rec1.end(); ++it){
        preorden.push_back(*it);
    }
    for(string::iterator it = rec2.begin(); it != rec2.end(); ++it){
        inorden.push_back(*it);
    }
    a.llenarPreIn(preorden,inorden);
}

bool esCompleto(map<char,list<char> >&hijos,map<char,int> &niveles,bool &esLLeno){
    list<int> nivelesHojas;
    esLLeno = true;
    for(map<char,list<char> >::iterator it = hijos.begin();it != hijos.end();++it){
        if(!(it->second.empty())){
            if(it->second.size() < 2){
                cout << "sale falso" << endl;
                return false;
            }
        }
        else{
            nivelesHojas.push_back(niveles[it->first]);
            if(niveles[it->first] != nivelesHojas.front()){
                esLLeno = false;
            }
        }
    }
    return true;
}

int main(){
    ArbolBin<char> arbol;
    leerEntrada(arbol);
    map<char,list<char> > hijos;
    map<char,int> niveles;
    bool esLLeno;
    arbol.mapearHijos(hijos);
    arbol.mapearNiveles(niveles);
    if(esCompleto(hijos,niveles,esLLeno)){
        cout << "El arbol dado es completo" << endl;
        if(esLLeno){
            cout << "El arbol dado es lleno" << endl;
        }
        else{
            cout << "El arbol dado no es lleno" << endl;
        }
    }
    else{
        cout << "El arbol dado no es completo" << endl;
        cout << "El arbol dado no es lleno" << endl;
    }

}