#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <map>
#include "GrafoDir.hpp"

using namespace std;

void leerEntrada(GrafoDir<int> &g,vector<int> &iniciosA,vector<int> &iniciosB,int &N,int &M){
    map<int,bool> insertados;
    int KA,KB,num;
    cin >> N >> M;
    for(int i=0;i<M;i++){
        int origen,dest;
        if(cin >> origen >> dest){
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
    cin >> KA >> KB;
    for(int i=0;i<KA;i++){
        cin >> num;
        iniciosA.push_back(num);
    }
    for(int i=0;i<KB;i++){
        cin >> num;
        iniciosB.push_back(num);
    }
}

// marcar todos los origenes de A y B como activados
// realiza el recorrido por niveles desde todos los origenes de A y B
// guardar el estado de cada vertice progresivamente en vector<pair<int,int> >
// al final de la propagacion, si quedaron vertices del grafo no visitados marcarlos como tal

vector<pair<char,int> > recorrido(GrafoDir<int> &g,vector<int> &iniciosA,vector<int> &iniciosB,int nVertices){
    vector<pair<char,int> > result(nVertices+1);
    map<int,bool> activadosA,activadosB,bloqueados;
    vector<int> visitados(nVertices+1);
    queue<int> cola;
    list<int> sucesores;
    pair<char,int> parActual;

    for(vector<int>::iterator it = iniciosA.begin(); it != iniciosA.end();++it){
        activadosA[*it] = true;
        visitados[*it] = true;
        cola.push(*it);
        parActual.first = 'A';
        parActual.second = 0;
        result[*it] = parActual;
    }
    for(vector<int>::iterator it = iniciosB.begin(); it != iniciosB.end();++it){
        activadosB[*it] = true;
        visitados[*it] = true;
        cola.push(*it);
        parActual.first = 'B';
        parActual.second = 0;
        result[*it] = parActual;
    }
    while(!cola.empty()){
        int v = cola.front();
        sucesores = g.getSucesores(v);
        while(!sucesores.empty()){
            int w = sucesores.front();
            if(!visitados[w] && !bloqueados[v]){
                if(activadosA[v]){
                    activadosA[w] = true;
                    parActual.first = 'A';
                }
                if(activadosB[v]){
                    activadosB[w] = true;
                    parActual.first = 'B';
                }
                parActual.second = result[v].second+1;
            
                result[w] = parActual;
                visitados[w] = true;
                cola.push(w);
            }
            else{
                if(result[v].second + 1 == result[w].second){
                    // si ya fue visitado, y habia sido marcado por el contrario, debe ser bloqueado
                    if(activadosA[v] && activadosB[w]){
                        activadosB[w] = false;
                        bloqueados[w] = true;
                        result[w].first = 'X';
                    
                    }
                    if(activadosB[v] && activadosA[w]){
                        activadosA[w] = false;
                        bloqueados[w] = true;
                        result[w].first = 'X';
                    }
                }
            }
            sucesores.pop_front();
        }
        cola.pop();
    }

    for(int i=0;i<nVertices;i++){
        if(!visitados[i]){
            parActual.first = 'U';
            parActual.second = -1;
            result[i] = parActual;
        }
        
    }

    return result;
}



void imprimirSalida(vector<pair<char,int> > &result,int N){
    for(int i=0;i<N;i++){
        pair<char,int> act = result[i];
        cout << act.first << " " << act.second << endl;
    }
}

int main(){
    GrafoDir<int> mapa;
    vector<int> iniciosA,iniciosB;
    vector<pair<char,int> > result;
    int nVertices,nArcos;
    leerEntrada(mapa,iniciosA,iniciosB,nVertices,nArcos);
    result = recorrido(mapa,iniciosA,iniciosB,nVertices);
    imprimirSalida(result,nVertices);
}