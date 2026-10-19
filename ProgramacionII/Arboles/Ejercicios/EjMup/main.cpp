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

string obtenerLCA(ArbolBin<string> &a,string &x,string&y){
    if(a.esNulo()){
        return "";
    }
    string raiz = a.getRaiz();
    if(raiz == x || raiz == y){
        return raiz;
    }
    ArbolBin<string> izq = a.getHijoIzq();
    ArbolBin<string> der = a.getHijoDer();

    string izqLCA = obtenerLCA(izq,x,y);
    string derLCA = obtenerLCA(der,x,y);

    if(izqLCA != "" && derLCA != ""){
        return raiz;
    }
    //se devuelve el lado que haya encontrado algo
    return (izqLCA != "") ? izqLCA : derLCA;
}


int obtenerMUP(ArbolBin<string> &arbol,list<string> &conj,map<string,int> &niveles){
    int mup = 0;
    for(list<string>::iterator it1 = conj.begin(); it1 != conj.end(); ++it1){
        list<string>::iterator it2 = it1;
        it2++;
        for(; it2 != conj.end(); ++it2){
            string x = *it1;
            string y = *it2;
            string lca = obtenerLCA(arbol,x,y);
            int dist = niveles[x] + niveles[y] - 2 * niveles[lca];
            mup += (dist-1) * abs(niveles[x] - niveles[y]);
            cout << "la distancia entre " << x << " y " << y << " es de " << dist << endl;;
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