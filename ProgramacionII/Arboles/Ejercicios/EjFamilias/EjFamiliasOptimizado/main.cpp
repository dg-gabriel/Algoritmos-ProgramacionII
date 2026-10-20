// Ej. Parcial 2020
// "Familias"
// acomodado, ahora usa mapas para encontrar el LCA y sacar la distancia con una formula
// snippets vibecodeados y pegados sobre el anterior ejercicio
#include <iostream>
#include "ArbolBin.hpp"
#include <list>
#include <map>
#include <sstream>

using namespace std;

void leerEntrada(ArbolBin<int> &arbol,list<int> &conj){
    list<char> inorderStr,otherStr;
    string line,otroRec;

    for(int i=0;i<2;i++){
        string line,tag;
        cin >> tag;
        getline(cin >> ws,line);

        stringstream ss(line);
        char s;
        while(ss >> s){
            if(tag == "INORDEN"){
                inorderStr.push_back(s);
            }
            else{
                otroRec = tag;
                otherStr.push_back(s);
            }
        }
    }

    map<char,int> traductor;
    list<int> in,other;
    int i = 1;

    for(list<char>::iterator it = inorderStr.begin(); it != inorderStr.end(); ++it){
        traductor[*it] = i;
        in.push_back(i);
        i++;
    }
    for(list<char>::iterator it = otherStr.begin(); it != otherStr.end(); ++it){
        other.push_back(traductor[*it]);
    }

    if(otroRec == "PREORDEN"){
        arbol.llenarPreIn(other,in);
    }
    else{
        arbol.llenarPostIn(other,in);
    }

    // leer el conjunto
    getline(cin >> ws,line);
    stringstream ss(line);
    int num;
    while(ss >> num){
        conj.push_back(num);
    }
}

int obtenerLCA(int u, int v, map<int, int> &padres, map<int, int> &niveles) {
    while (niveles[u] > niveles[v]) {
        u = padres[u];
    }
    while (niveles[v] > niveles[u]) {
        v = padres[v];
    }
    while (u != v) {
        u = padres[u];
        v = padres[v];
    }
    return u;
}

int distancia(map<int,int> &niveles,map<int,int> &padres,int u,int v){
    int lca = obtenerLCA(u,v,padres,niveles);
    return niveles[u] + niveles[v] - 2 * niveles[lca];
}

long obtenerValorFamilia(ArbolBin<int> &arbol,list<int> &Q){
    map<int,int> niveles,padres;
    arbol.mapearNiveles(niveles);
    arbol.mapearPadres(padres);
    long sum = 0;
    for(list<int>::iterator it1 = Q.begin(); it1 != Q.end(); ++it1){
    // 1. Creamos el segundo iterador en la misma posición que it1
        list<int>::iterator it2 = it1;
    // 2. Lo adelantamos un paso (equivalente a hacer j = i + 1)
        ++it2; 
    // 3. Recorremos desde ese siguiente elemento hasta el final
        for(; it2 != Q.end(); ++it2){
            int u = *it1; // Equivalente a Q[i]
            int v = *it2; // Equivalente a Q[j]
            sum += u * v * distancia(niveles,padres,u,v);
        }
    }
    return sum;
}

int main(){
    int nCasos,nFamilias,nNodos;

    if(!(cin >> nCasos)) return 0;
    cout << nCasos;
    for(int i=0;i<nCasos;i++){
        long maxSum = -1,familiaMax = 0;
        if(!(cin >> nFamilias)) break;
        for(int j=1;j<=nFamilias;j++){
            cin >> nNodos;
            ArbolBin<int> arbol;
            list<int> conjQ;
            int sum;
            leerEntrada(arbol,conjQ);
            sum = obtenerValorFamilia(arbol,conjQ);
            if(sum > maxSum){
                maxSum = sum;
                familiaMax = j;
            }
        }
        cout << familiaMax << "\n";
    }
}

