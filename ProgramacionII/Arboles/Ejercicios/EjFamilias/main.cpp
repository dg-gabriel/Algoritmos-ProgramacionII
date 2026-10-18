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
    getline(cin,line);
    stringstream ss(line);
    int num;
    while(ss >> num){
        conj.push_back(num);
    }
}

int profundidad(ArbolBin<int> root,int elem,int depth){
    if(root.esNulo()){
        return -1;
    }
    else{
        if(root.getRaiz() == elem){
            return depth;
        }
        if(elem < root.getRaiz()){
            return profundidad(root.getHijoIzq(),elem,depth+1);
        }
        else{
            return profundidad(root.getHijoDer(),elem,depth+1);
        }
    }
}

int distancia(ArbolBin<int> arbol,int u,int v){
    if(arbol.esNulo()){
        return 0;
    }
    if(u < arbol.getRaiz() && v < arbol.getRaiz()){
        return distancia(arbol.getHijoIzq(),u,v);
    }
    if(u > arbol.getRaiz() && v > arbol.getRaiz()){
        return distancia(arbol.getHijoDer(),u,v);
    }
    return profundidad(arbol,u,0) + profundidad(arbol,v,0);
}

int obtenerValorFamilia(ArbolBin<int> &arbol,list<int> &Q){
    int sum = 0;
    for(list<int>::iterator it1 = Q.begin(); it1 != Q.end(); ++it1){
    // 1. Creamos el segundo iterador en la misma posición que it1
        list<int>::iterator it2 = it1;
    // 2. Lo adelantamos un paso (equivalente a hacer j = i + 1)
        ++it2; 
    // 3. Recorremos desde ese siguiente elemento hasta el final
        for(; it2 != Q.end(); ++it2){
            int u = *it1; // Equivalente a Q[i]
            int v = *it2; // Equivalente a Q[j]
            sum += u * v * distancia(arbol,u,v);
        }
    }
    return sum;
}

int main(){
    int nCasos,nFamilias,nNodos;

    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        int maxSum = -1;
        cin >> nFamilias;
        for(int j=0;j<nFamilias;j++){
            cin >> nNodos;
            ArbolBin<int> arbol;
            list<int> conjQ;
            int sum;
            leerEntrada(arbol,conjQ);
            sum = obtenerValorFamilia(arbol,conjQ);
            if(sum > maxSum){
                maxSum = sum;
            }
        }
        cout << maxSum << endl;
    }
}

// no me di cuenta que el arbol era un BST
// vibe codee la obtencion de los pares de u,v del conjunto q
// las demas funciones las saque de la guia