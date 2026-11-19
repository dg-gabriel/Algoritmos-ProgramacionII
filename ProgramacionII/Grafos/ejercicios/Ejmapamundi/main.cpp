// Ej. Mapa Mundial
// Encontrar el Arbol de expansion minima con no mas de k incidencias por nodo
// Backtracking probando cada camino y volviendo si sobrepasa k
#include <iostream>
#include <list>
#include <map>
#include "GrafoNoDir.hpp"

using namespace std;

void leerEntrada(GrafoNoDir<string> &g,int &k){
    cin >> k;
    map<string,bool> insertados;
    string origen,dest;
    while(cin >> origen >> dest){
        if(!insertados[origen]){
            g.insertarVertice(origen);
            insertados[origen] = true;
        }
        if(!insertados[dest]){
            g.insertarVertice(dest);
            insertados[dest] = true;
        }
        g.insertarArco(origen,dest,0);
    }
}

bool getArbolAux(GrafoNoDir<string> &g,map<string,int> &grados,map<string,bool> &visitados,list<list<string> > &res,list<string> &vertices,int k){
    if(res.size() == g.getNVertices() - 1){
        return true;
    }
    else{
        for(list<string>::iterator it = vertices.begin(); it != vertices.end(); ++it){
            string u = *it;
            if(visitados[u] && grados[u] < k){
                list<string> vecinos = g.getVecinos(u);
                while(!vecinos.empty()){
                    string w = vecinos.front();
                    if(!visitados[w]){
                        visitados[w] = true;
                        grados[u]++;
                        grados[w]++;
                        list<string> par;
                        par.push_back(u);
                        par.push_back(w);
                        res.push_back(par);
                        if(getArbolAux(g,grados,visitados,res,vertices,k)){
                            return true;
                        }
                        else{
                            grados[u]--;
                            grados[w]--;
                            res.pop_back();
                            visitados[w] = false;
                        }
                    }
                   vecinos.pop_front();
                }
            }
        }
        return false;
    }
    
}

list<list<string> > getArbol(GrafoNoDir<string> &g,int k){
    map<string,int> grados;
    map<string,bool> visitados;
    list<list<string> > result;
    list<string> nombres = g.getVertices();
    for(list<string>::iterator it = nombres.begin(); it != nombres.end(); ++it){
        grados[*it] = 0;
        visitados[*it] = false;
    }
    visitados[nombres.front()] = true;
    if(getArbolAux(g,grados,visitados,result,nombres,k)){
        return result;
    }
    else{
        result.clear();
        return result;
    }
    
}

void printSalida(list<list<string> > &salida){
    for(list<list<string> >::iterator it = salida.begin();it != salida.end();++it){
        cout << it->front() << " " << it->back() << endl;
    }
}

int main(){
    GrafoNoDir<string> grafo;
    int k;
    list<list<string> > res;
    leerEntrada(grafo,k);
    if(grafo.getNComponentesConexas() == 1){
        res = getArbol(grafo,k);
        printSalida(res);
    }
}