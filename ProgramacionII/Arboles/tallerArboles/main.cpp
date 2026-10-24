#include "ArbolBin.hpp"
#include <iostream>
#include <list>
#include <map>

using namespace std;

void leerEntrada(map<int,list<int> > &hijos,int nNodos,int &raiz){
    int act,hijoIzq,hijoDer;
    for(int i=0;i<nNodos;i++){
        if(!(cin >> act >> hijoIzq >> hijoDer)) break;;
        hijos[act].push_back(hijoIzq);
        hijos[act].push_back(hijoDer);
        if(i == 0){
            // guardamos la raiz para el orden de construccion
            raiz = act;
        }
        // leemos el caso de entrada y lo guardamos en un mapa
    }
}

ArbolBin<int> construirArbol(int raiz,map<int,list<int> > &hijos){
    ArbolBin<int> arbolAct;
    if(raiz == -1){
        return arbolAct;
    }
    // construimos el arbol recursivamente
    list<int> &hijosAct = hijos[raiz];
    arbolAct.construir(raiz,construirArbol(hijosAct.front(),hijos),construirArbol(hijosAct.back(),hijos));
    return arbolAct;
}

bool esEspejeado(int u,int v,map<int,list<int> > &hijos){
    // si hijoIzq de u e hijoDer de v son iguales (existen o no existen ambos)
    if((hijos[u].front() != -1 && hijos[v].back() != -1) || (hijos[u].front() == -1 && hijos[v].back() == -1)){
        // si hijoDer de u e hijoIzq de v son iguales (existen o no exsisten ambos)
        if((hijos[u].back() != -1 && hijos[v].front() != -1) || ((hijos[u].back() == -1 && hijos[v].front() == -1))){
            // confirmamos que u y v son especulares
            return true;
        }
    }
    return false; 
} // nos apoyamos en el [-1] del mapa de hijos para determinar si cada hijo izquierdo  y derecho son espejeados

void nroEspejosArbol(ArbolBin<int> &a,map<int,list<int> > &hijos,int &n){
    if(a.esNulo()){
        return;
    }
    if(hijos[a.getRaiz()].front() == -1 && hijos[a.getRaiz()].back() == -1){
        // si es hoja es espejeado automaticamente
        n++;
        return;
    }
    // si alguno de los dos subarboles es nulo pasamos como parametro el equivalente del mapa (-1)
    int u = -1,v = -1; 
    ArbolBin<int> hijoIzq = a.getHijoIzq();
    ArbolBin<int> hijoDer = a.getHijoDer();
    if(!hijoIzq.esNulo()){
        u = hijoIzq.getRaiz();
    }
    if(!hijoDer.esNulo()){
        v = hijoDer.getRaiz();
    }
    if(esEspejeado(u,v,hijos)){
        // si u y v son espejeados incrementamos
        n++;
    }
    nroEspejosArbol(hijoIzq,hijos,n);
    nroEspejosArbol(hijoDer,hijos,n); 
    
    return;
}

int main(){
    int nCasos;
    // blindamos la lectura de casos y la lectura de nodos
    if(!(cin >> nCasos)) return 0;
    for(int i=0;i<nCasos;i++){
        int nNodos,raiz;
        if(!(cin >> nNodos)) break;
        ArbolBin<int> arbol;
        map<int,list<int> > hijos;
        leerEntrada(hijos,nNodos,raiz);  
        arbol = construirArbol(raiz,hijos);
        int nEspejos;
        nroEspejosArbol(arbol,hijos,nEspejos);
        cout << nEspejos << endl;
    }
}

