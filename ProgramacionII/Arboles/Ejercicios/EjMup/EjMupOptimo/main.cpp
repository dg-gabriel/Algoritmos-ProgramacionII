// Ej Parcial 2025
// "MUP"
// la solucion no es completamente optima no aguanta caso de desborde
// esta bastante copiada del ejercicio de lasfamilias
#include <iostream>
#include "ArbolBin.hpp"
#include <sstream>
#include <map>
#include <cmath>
#include <list>

void leerEntrada(ArbolBin<string>& arbol,list<string> &conj){
    list<string> inorden,otro;
    string line,tag,otroTag,alum;
    stringstream ss;
    for(int i=0;i<2;i++){
        getline(cin >> ws,line);
        ss.clear();
        ss.str(line);
        ss >> tag;
        
        while(ss >> alum){
            if(tag == "INORDEN"){
                inorden.push_back(alum);
            }
            else{
                otroTag = tag;
                otro.push_back(alum);
            }
        }
    }
    getline(cin,line);
    ss.clear();
    ss.str(line);
    while(ss >> alum){
        conj.push_back(alum);
    }

    if(otroTag == "PREORDEN"){
        arbol.llenarPreIn(otro,inorden);
    }
    else{
        arbol.llenarPostIn(otro,inorden);
    }
}

void mapearNiveles(ArbolBin<string> &arbol,map<string,int> &mapa,int nivAct){
    if(arbol.esNulo()) return;

    mapa[arbol.getRaiz()] = nivAct;
    ArbolBin<string> izq = arbol.getHijoIzq();
    ArbolBin<string> der = arbol.getHijoDer();

    mapearNiveles(izq,mapa,nivAct+1);
    mapearNiveles(der,mapa,nivAct+1);
}

int profundidad(ArbolBin<string> &a, string elem, int depth){
    if(a.esNulo()){
        return -1;
    }
    if(a.getRaiz() == elem){
        return depth;
    }
    
    // Pasando por referencia los hijos para evitar copias pesadas
    ArbolBin<string> izq = a.getHijoIzq();
    ArbolBin<string> der = a.getHijoDer();
    
    int leftPath = profundidad(izq, elem, depth + 1);
    if(leftPath != -1) return leftPath; // Si lo encuentra por la izquierda, retorna directo
    
    return profundidad(der, elem, depth + 1); // Si no, busca por la derecha
}

bool findValue(ArbolBin<string> &a, string elem){
    if(a.esNulo()){
        return false;
    }
    if(a.getRaiz() == elem){
        return true;
    }
    ArbolBin<string> izq = a.getHijoIzq();
    ArbolBin<string> der = a.getHijoDer();
    return findValue(izq, elem) || findValue(der, elem);
}

int distancia(ArbolBin<string> &a, string x, string y){
    if(a.esNulo()){
        return 0;
    }
    ArbolBin<string> izq = a.getHijoIzq();
    ArbolBin<string> der = a.getHijoDer();
    
    if(findValue(izq, x) && findValue(izq, y)){
        return distancia(izq, x, y);
    }
    if(findValue(der, x) && findValue(der, y)){
        return distancia(der, x, y);
    }
    return profundidad(a, x, 0) + profundidad(a, y, 0);
}


int obtenerMUP(ArbolBin<string> &arbol,list<string> &conj,map<string,int> &niveles){
    int mup = 0;
    for(list<string>::iterator it1 = conj.begin(); it1 != conj.end(); ++it1){
        list<string>::iterator it2 = it1;
        it2++;
        for(; it2 != conj.end(); ++it2){
            string x = *it1;
            string y = *it2;
            int dist = distancia(arbol,x,y)-1;
            mup +=  dist * abs(niveles[x] - niveles[y]);
        }
    }
    return mup;
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        int nArboles,maxMup = -1,arbolMaxMup;
        cin >> nArboles;
        for(int j=1;j<=nArboles;j++){
            ArbolBin<string> arbol;
            list<string> conjunto;
            map<string,int> niveles;
            leerEntrada(arbol,conjunto);
            mapearNiveles(arbol,niveles,0);
            int mup = obtenerMUP(arbol,conjunto,niveles);
            if(mup > maxMup){
                maxMup = mup;
                arbolMaxMup = j;
            }
            
        }
        cout << arbolMaxMup << endl;
    }
}

