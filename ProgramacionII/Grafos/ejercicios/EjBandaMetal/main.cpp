#include <iostream>
#include "GrafoNoDir.hpp"

using namespace std;

void leerEntrada(GrafoNoDir<string> &g){
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

bool tieneVecinosNoCubiertos(GrafoNoDir<string> &g,string w,map<string,int> &cubierto){
    list<string> vecinosW = g.getVecinos(w);
    for(list<string>::iterator it = vecinosW.begin();it != vecinosW.end();++it){
        if(cubierto[*it] == 0){
            return true;
        }
    }
    return false;
}

void marcarVecinos(GrafoNoDir<string> &g,string u,map<string,int> &cubierto,int &totalCubierto){
    cubierto[u]++;
    if(cubierto[u] == 1){
        totalCubierto++;
    }
    list<string> vecinos = g.getVecinos(u);
    for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
        cubierto[*it]++;
        if(cubierto[*it] == 1){
            totalCubierto++;
        }
    }
}

void desmarcarVecinos(GrafoNoDir<string> &g,string w,string u,map<string,int> &cubierto,int &totalCubierto){
    cubierto[w]--;
    if(cubierto[w] == 0){
        totalCubierto--;
    }
    list<string> vecinos = g.getVecinos(w);
    for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
        if(*it != u){
            cubierto[*it]--;
            if(cubierto[*it] == 0){
                totalCubierto--;
            }
        }
    }
}

void mapaMinimoAux(GrafoNoDir<string> &g,string u,map<string,bool> &visitados,map<string,int> &cubierto,list<string> &res,list<string> &mejor,int &totalCubierto){
    
    visitados[u] = true;
    res.push_back(u);
    list<string> vecinos = g.getVecinos(u);
    marcarVecinos(g,u,cubierto,totalCubierto);
    if(totalCubierto == g.getNVertices()){
        if(res.size() < mejor.size()){
            mejor = res;
        }
    }
    else{
        while(!vecinos.empty()){
            string w = vecinos.front();
            if(!visitados[w]){
                if(tieneVecinosNoCubiertos(g,w,cubierto)){
                    mapaMinimoAux(g,w,visitados,cubierto,res,mejor,totalCubierto);
                }
            }
            vecinos.pop_front();
        
        }
    }
    visitados[u] = false;
    res.pop_back();
    desmarcarVecinos(g,u," ",cubierto,totalCubierto);
}

list<string> mapaMinimo(GrafoNoDir<string> &g){
    list<string> res,mejor,vertices;
    map<string,bool> visitados;
    map<string,int> cubierto;
    int total = 0;
    vertices = g.getVertices();
    mejor = vertices;
    for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
        string act = *it;
        mapaMinimoAux(g,act,visitados,cubierto,res,mejor,total);
    }
    mejor.sort();
    return mejor;
}

void imprimirSalida(list<string> &res){
    for(list<string>::iterator it = res.begin();it != res.end();++it){
        cout << *it << " ";
    }
    cout << endl;
}

int main(){
    GrafoNoDir<string> mapa;
    leerEntrada(mapa);
    list<string> res = mapaMinimo(mapa);
    imprimirSalida(res);
}