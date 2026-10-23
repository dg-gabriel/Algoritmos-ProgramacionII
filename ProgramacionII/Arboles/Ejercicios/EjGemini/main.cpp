#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include "ArbolBin.hpp"

using namespace std;

void leerEntrada(ArbolBin<string>& arbol,string &x,string &y){
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
    cin >> x >> y;

    if(otroTag == "PREORDEN"){
        arbol.llenarPreIn(otro,inorden);
    }
    else{
        arbol.llenarPostIn(otro,inorden);
    }
}

string obtenerLCAMapas(string u, string v, map<string, string> &padres, map<string, int> &niveles,int &nroNs) {

    while (niveles[u] > niveles[v]){
        if(u[u.length()-1] % 2 == 0) nroNs++; 
        u = padres[u];
    }
    while (niveles[v] > niveles[u]) {
        if(v[v.length()-1] % 2 == 0) nroNs++;
        v = padres[v];
    }
    
    while (u != v) {
        if(u[u.length()-1] % 2 == 0) nroNs++;
        if(v[v.length()-1] % 2 == 0) nroNs++;
        u = padres[u];
        v = padres[v];
    }

    if(u[u.length()-1] % 2 == 0) nroNs++;
    return u;
}

void cantHojasSubArbol(string u,map<string,list<string> > &hijos,int &cantHojas){
    list<string> &misHijos = hijos[u];
    if(misHijos.empty()){
        cantHojas++;
        return;
    }
    for(list<string>::iterator it = misHijos.begin();it != misHijos.end(); ++it){
        cantHojasSubArbol(*it,hijos,cantHojas);
    }
    return;
}

int calcularIVE(string a,string b,map<string,string> &padres,map<string,list<string> > &hijos,map<string,int> &niveles){
    int C = 0,H = 0;
    string lca = obtenerLCAMapas(a,b,padres,niveles,C);
    cantHojasSubArbol(lca,hijos,H);
    int dist = niveles[a] + niveles[b] - 2 * niveles[lca];
    return ((dist + C) * H);
}

int main(){
    int nCasos,nArboles;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        int menor = 99999999;
        string mayorRaiz = "";
        cin >> nArboles;
        for(int j=0;j<nArboles;j++){
            ArbolBin<string> arbol;
            string a,b;
            leerEntrada(arbol,a,b);
            map<string,list<string> > hijos;
            map<string,string> padres;
            map<string,int> niveles;
            arbol.mapearHijos(hijos);
            arbol.mapearPadres(padres);
            arbol.mapearNiveles(niveles);
            int IVE = calcularIVE(a,b,padres,hijos,niveles);
            if(IVE < menor){
                menor = IVE;
                mayorRaiz = arbol.getRaiz();
            }
        }
        cout << "Red seleccionada: " << mayorRaiz << " (IVE = " << menor << ")" << endl;
    }
}