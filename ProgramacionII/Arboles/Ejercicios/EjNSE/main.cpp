// Ej. Parcial 2022
// "NSE"
// me enrede calculando los N de nodo a nodo
// recorrido del LCA por el mapa
// asi ni hace falta utilizar un arbol
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "ArbolBin.hpp"

using namespace std;

void leerEntrada(ArbolBin<string> &arbol,string &u,string &v){
    list<string> inorden,otro;
    string line,tag,otroTag,nombre;
    stringstream ss;
    for(int i=0;i<2;i++){
        getline(cin >> ws,line);
        ss.clear();
        ss.str(line);
        ss >> tag;
        
        while(ss >> nombre){
            if(tag == "INORDEN"){
                inorden.push_back(nombre);
            }
            else{
                otroTag = tag;
                otro.push_back(nombre);
            }
        }
    }

    cin >> u >> v;

    if(otroTag == "PREORDEN"){
        arbol.llenarPreIn(otro,inorden);
    }
    else{
        arbol.llenarPostIn(otro,inorden);
    }
}

string obtenerLCAMapas(string u, string v, map<string, string> &padres, map<string, int> &niveles,float &nroNs) {

    while(niveles[u] > niveles[v]){
        if(u[u.length()-1] == 'N') nroNs++; 
        u = padres[u];
    }

    while (niveles[v] > niveles[u]) {
        if(v[v.length()-1] == 'N') nroNs++;
        v = padres[v];
    }
    
    while (u != v) {
        if(u[u.length()-1] == 'N') nroNs++;
        if(v[v.length()-1] == 'N') nroNs++;
        u = padres[u];
        v = padres[v];
    }

     if(u[u.length()-1] == 'N') nroNs++; 
    
    return u;
}

float calcularNSE(ArbolBin<string> &arbol,string u,string v){
    map<string,string> padres;
    map<string,int> niveles;
    arbol.mapearPadres(padres);
    arbol.mapearNiveles(niveles);
    float nroNephis = 0;
    string lca = obtenerLCAMapas(u,v,padres,niveles,nroNephis);
    float distancia = niveles[u] + niveles[v] - 2 * niveles[lca];
    float NSE = nroNephis / distancia;
    return NSE;
}

int main(){
    int nCasos;
    if(!(cin >> nCasos)) return 0;
    for(int i=0;i<nCasos;i++){
        ArbolBin<string> arbol;
        string u,v;
        leerEntrada(arbol,u,v);
        float NSE = calcularNSE(arbol,u,v);
        cout << NSE << endl;
    }
}