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

string obtenerLCAMapas(string u, string v, map<string, string> &padres, map<string, int> &niveles) {
    // 1. Igualamos los pisos: el que esté más profundo sube a su padre
    while (niveles[u] > niveles[v]) {
        u = padres[u];
    }
    while (niveles[v] > niveles[u]) {
        v = padres[v];
    }
    
    // 2. Ahora que están en el mismo piso, suben juntos hasta encontrarse
    while (u != v) {
        u = padres[u];
        v = padres[v];
    }
    
    // 3. Cuando chocan, 'u' (o 'v', que valen lo mismo) es el LCA
    return u;
}

int obtenerMUP(ArbolBin<string> &arbol,list<string> &conj){
    map<string,int> niveles;
    map<string,string> padres;
    arbol.mapearNiveles(niveles);
    arbol.mapearPadres(padres);
    int mup = 0;
    for(list<string>::iterator it1 = conj.begin(); it1 != conj.end(); ++it1){
        list<string>::iterator it2 = it1;
        it2++;
        for(; it2 != conj.end(); ++it2){
            string x = *it1;
            string y = *it2;
            string lca = obtenerLCAMapas(x,y,padres,niveles);
            int dist = (niveles[x] + niveles[y] - 2 * niveles[lca])-1;
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

