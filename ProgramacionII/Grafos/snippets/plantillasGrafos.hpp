#ifndef PLANTILLAS_GRAFOS_HPP
#define PLANTILLAS_GRAFOS_HPP

// ============================================================================
//  ALGORITMOS EXTERNOS (fuera de la clase), solo con la API publica del grafo.
//  C++98. Sin struct, sin pair, sin vector. Vertices de tipo string.
//
//  Incluye ANTES de este archivo tu libreria:
//      #include "GrafoNoDir.hpp"   (y/o "GrafoDir.hpp")
//      #include "plantillasGrafos.hpp"
//
//  Son template <class Grafo>, asi que sirven con GrafoNoDir<string> y
//  GrafoDir<string> segun se indica en cada una.
//
//   1. dijkstra     camino de menor costo (pesos >= 0).   NoDir y Dir.
//   2. prim         arbol (bosque) generador minimo.      SOLO NoDir.
//   3. esBipartito  2-coloreado, devuelve los dos grupos. NoDir y Dir.
//   4. getPuntosArticulacion / getPuentes   (Tarjan, low-link).   SOLO NoDir.
//   5. componentesFuertementeConexas        (Tarjan con pila).    SOLO Dir.
//   6. ordenTopologico                      (Kahn).               SOLO Dir.
// ============================================================================

#include <string>
using namespace std;

// ===========================================================================
// 1. DIJKSTRA (O(n^2) con map; pesos >= 0)
//    Retorna el costo del camino minimo de origen a destino, o -1 si no hay
//    (o si alguno no existe). El camino queda en "camino" (vacio si no hay).
//
//    Idea: dist[v] = mejor costo conocido hasta v. En cada vuelta se fija el
//    vertice no fijado con menor dist, y se relajan sus arcos.
//
//    Funciona con GrafoDir sin cambios: getVecinos en un dirigido trae
//    tambien predecesores, pero getCostoArco(act,w) devuelve -1 si NO existe
//    el arco act->w, y esos se saltan.
// ===========================================================================
template <class Grafo>
float dijkstra(Grafo &g,const string &origen,const string &destino,list<string> &camino){
    camino.clear();
    if(!g.existeVertice(origen) || !g.existeVertice(destino)){
        return -1;
    }
    list<string> vertices = g.getVertices();
    map<string,float> dist;                            // solo vertices ya alcanzados
    map<string,string> padre;
    map<string,bool> fijado;

    dist[origen] = 0;
    bool seguir = true;
    while(seguir){
        // elegir el vertice alcanzado, no fijado, de menor distancia
        string act = "";
        bool hay = false;
        for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
            if(!fijado[*it] && dist.count(*it) == 1 && (!hay || dist[*it] < dist[act])){
                act = *it;
                hay = true;
            }
        }
        if(!hay || act == destino){
            seguir = false;                            // nada alcanzable, o destino ya definitivo
        }
        else{
            fijado[act] = true;
            list<string> vecinos = g.getVecinos(act);
            for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
                float peso = g.getCostoArco(act,*it);
                if(peso < 0){
                    continue;                          // no existe el arco act->*it (caso dirigido)
                }
                float nueva = dist[act] + peso;
                if(!fijado[*it] && (dist.count(*it) == 0 || nueva < dist[*it])){
                    dist[*it] = nueva;                 // camino mejor hacia *it
                    padre[*it] = act;
                }
            }
        }
    }
    if(dist.count(destino) == 0){
        return -1;                                     // inalcanzable
    }
    string v = destino;                                // reconstruir camino hacia atras
    camino.push_front(v);
    while(v != origen){
        v = padre[v];
        camino.push_front(v);
    }
    return dist[destino];
}

// ===========================================================================
// 2. PRIM: arbol generador minimo (BOSQUE generador minimo si el grafo no es
//    conexo: un arbol por componente). SOLO para GrafoNoDir.
//    Retorna el peso total; "aristas" recibe las aristas elegidas [padre,hijo].
//
//    Idea: clave[v] = peso de la arista mas barata que conecta v al arbol.
//    En cada vuelta se agrega al arbol el vertice fuera de el con menor clave.
//    Cantidad de aristas = (#vertices) - (#componentes).
// ===========================================================================
template <class Grafo>
float prim(Grafo &g,list<list<string> > &aristas){
    float total = 0;
    aristas.clear();
    list<string> vertices = g.getVertices();
    map<string,bool> enArbol;
    map<string,float> clave;                           // solo vertices ya "vistos"
    map<string,string> padre;

    for(list<string>::iterator ini = vertices.begin();ini != vertices.end();++ini){
        if(enArbol[*ini]){
            continue;                                  // ya pertenece a un arbol anterior
        }
        clave[*ini] = 0;                               // nueva componente: arranca aqui
        bool seguir = true;
        while(seguir){
            string act = "";
            bool hay = false;
            for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
                if(!enArbol[*it] && clave.count(*it) == 1 && (!hay || clave[*it] < clave[act])){
                    act = *it;
                    hay = true;
                }
            }
            if(!hay){
                seguir = false;                        // componente completa
            }
            else{
                enArbol[act] = true;
                if(act != *ini){                       // el inicio no tiene arista de entrada
                    list<string> arista;
                    arista.push_back(padre[act]);
                    arista.push_back(act);
                    aristas.push_back(arista);
                    total += clave[act];
                }
                list<string> vecinos = g.getVecinos(act);
                for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
                    if(!enArbol[*it]){
                        float peso = g.getCostoArco(act,*it);
                        if(clave.count(*it) == 0 || peso < clave[*it]){
                            clave[*it] = peso;
                            padre[*it] = act;
                        }
                    }
                }
            }
        }
    }
    return total;
}

// ===========================================================================
// 3. GRAFO BIPARTITO (2-coloreado con BFS). NoDir y Dir (en Dir se ignora el
//    sentido de los arcos, porque getVecinos trae sucesores y predecesores).
//    Retorna true si se pueden separar los vertices en dos grupos sin ninguna
//    arista dentro de un mismo grupo; los grupos quedan en grupoA y grupoB.
//    Si retorna false, ambos quedan vacios. Un lazo (v,v) lo hace NO bipartito.
//    Maneja grafos no conexos: se colorea cada componente.
// ===========================================================================
template <class Grafo>
bool esBipartito(Grafo &g,list<string> &grupoA,list<string> &grupoB){
    grupoA.clear();
    grupoB.clear();
    list<string> vertices = g.getVertices();
    map<string,int> color;                             // 0 sin color, 1 grupo A, 2 grupo B

    for(list<string>::iterator ini = vertices.begin();ini != vertices.end();++ini){
        if(color[*ini] != 0){
            continue;
        }
        color[*ini] = 1;
        queue<string> cola;
        cola.push(*ini);
        while(!cola.empty()){
            string act = cola.front();
            cola.pop();
            if(color[act] == 1){
                grupoA.push_back(act);
            }
            else{
                grupoB.push_back(act);
            }
            list<string> vecinos = g.getVecinos(act);
            for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
                if(color[*it] == 0){
                    color[*it] = 3 - color[act];       // el color contrario (1<->2)
                    cola.push(*it);
                }
                else if(color[*it] == color[act]){     // dos vecinos del mismo grupo
                    grupoA.clear();
                    grupoB.clear();
                    return false;
                }
            }
        }
    }
    return true;
}

// ===========================================================================
// 4. PUNTOS DE ARTICULACION Y PUENTES (Tarjan). SOLO GrafoNoDir.
//    disc[v] = momento en que el DFS descubre v (0 = no visitado).
//    low[v]  = menor disc alcanzable desde el subarbol de v usando A LO SUMO
//              una arista de retroceso.
//    Para un hijo w de v en el arbol DFS:
//      - arista (v,w) es PUENTE            si low[w] >  disc[v]
//      - v es PUNTO DE ARTICULACION        si low[w] >= disc[v] y v NO es raiz
//      - la raiz es punto si tiene > 1 hijo en el arbol DFS
//    La arista hacia el padre se salta UNA vez (por si hubiera arista doble).
//    Salida: puntos y cada puente [a,b] con a < b, ambas listas ordenadas.
// ===========================================================================
template <class Grafo>
void tarjanNoDirAux(Grafo &g,const string &v,const string &padre,bool tienePadre,int &tiempo,map<string,int> &disc,map<string,int> &low,list<string> &puntos,list<list<string> > &puentes){
    tiempo++;
    disc[v] = tiempo;
    low[v] = tiempo;
    int hijos = 0;
    bool esPunto = false;
    bool padreSaltado = false;

    list<string> vecinos = g.getVecinos(v);
    for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
        const string &w = *it;
        if(tienePadre && w == padre && !padreSaltado){
            padreSaltado = true;                       // la arista por la que llegue
        }
        else if(disc[w] != 0){                         // arista de retroceso
            if(disc[w] < low[v]){
                low[v] = disc[w];
            }
        }
        else{                                          // arista del arbol DFS
            hijos++;
            tarjanNoDirAux(g,w,v,true,tiempo,disc,low,puntos,puentes);
            if(low[w] < low[v]){
                low[v] = low[w];
            }
            if(low[w] > disc[v]){                      // puente
                list<string> puente;
                if(v < w){
                    puente.push_back(v);
                    puente.push_back(w);
                }
                else{
                    puente.push_back(w);
                    puente.push_back(v);
                }
                puentes.push_back(puente);
            }
            if(tienePadre && low[w] >= disc[v]){
                esPunto = true;
            }
        }
    }
    if((!tienePadre && hijos > 1) || esPunto){
        puntos.push_back(v);
    }
}

template <class Grafo>
void tarjanNoDir(Grafo &g,list<string> &puntos,list<list<string> > &puentes){
    puntos.clear();
    puentes.clear();
    list<string> vertices = g.getVertices();
    map<string,int> disc;
    map<string,int> low;
    int tiempo = 0;
    for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
        if(disc[*it] == 0){                            // una pasada por componente
            tarjanNoDirAux(g,*it,"",false,tiempo,disc,low,puntos,puentes);
        }
    }
    puntos.sort();                                     // salida alfabetica
    puentes.sort();
}

template <class Grafo>
list<string> getPuntosArticulacion(Grafo &g){
    list<string> puntos;
    list<list<string> > puentes;
    tarjanNoDir(g,puntos,puentes);
    return puntos;
}

template <class Grafo>
list<list<string> > getPuentes(Grafo &g){
    list<string> puntos;
    list<list<string> > puentes;
    tarjanNoDir(g,puntos,puentes);
    return puentes;
}

// ===========================================================================
// 5. COMPONENTES FUERTEMENTE CONEXAS (Tarjan con pila). SOLO GrafoDir.
//    Un vertice es "raiz" de su componente cuando low[v] == disc[v]; al
//    terminar de explorarlo se desapila hasta v y eso forma la componente.
//    Solo se actualiza low con vertices que SIGUEN en la pila (enPila).
//    Salida: cada componente ordenada, y la lista de componentes ordenada.
// ===========================================================================
template <class Grafo>
void sccAux(Grafo &g,const string &v,int &tiempo,map<string,int> &disc,map<string,int> &low,map<string,bool> &enPila,stack<string> &pila,list<list<string> > &componentes){
    tiempo++;
    disc[v] = tiempo;
    low[v] = tiempo;
    pila.push(v);
    enPila[v] = true;

    list<string> sucesores = g.getSucesores(v);
    for(list<string>::iterator it = sucesores.begin();it != sucesores.end();++it){
        const string &w = *it;
        if(disc[w] == 0){                              // no visitado: explorar
            sccAux(g,w,tiempo,disc,low,enPila,pila,componentes);
            if(low[w] < low[v]){
                low[v] = low[w];
            }
        }
        else if(enPila[w]){                            // arco de retroceso dentro de la pila
            if(disc[w] < low[v]){
                low[v] = disc[w];
            }
        }
    }
    if(low[v] == disc[v]){                             // v es raiz de una componente
        list<string> componente;
        string x;
        do{
            x = pila.top();
            pila.pop();
            enPila[x] = false;
            componente.push_back(x);
        }while(x != v);
        componente.sort();
        componentes.push_back(componente);
    }
}

template <class Grafo>
list<list<string> > componentesFuertementeConexas(Grafo &g){
    list<list<string> > componentes;
    list<string> vertices = g.getVertices();
    map<string,int> disc;
    map<string,int> low;
    map<string,bool> enPila;
    stack<string> pila;
    int tiempo = 0;
    for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
        if(disc[*it] == 0){
            sccAux(g,*it,tiempo,disc,low,enPila,pila,componentes);
        }
    }
    componentes.sort();
    return componentes;
}

// ===========================================================================
// 6. ORDENAMIENTO TOPOLOGICO (Kahn). SOLO GrafoDir.
//    grado[v] = cuantos arcos entran a v. Se saca un vertice de grado 0, se
//    "borran" sus arcos (se resta 1 a sus sucesores) y se repite.
//    Retorna true y deja el orden en "orden" si el grafo es un DAG; retorna
//    false (orden vacio) si hay ciclo (incluye lazos), pues quedan vertices
//    que nunca llegan a grado 0.
//    Entre los candidatos se toma siempre el MENOR alfabeticamente, asi la
//    salida es unica y reproducible (orden topologico lexicograficamente
//    menor). Si da igual cual, cualquiera de los de grado 0 sirve.
// ===========================================================================
template <class Grafo>
bool ordenTopologico(Grafo &g,list<string> &orden){
    orden.clear();
    list<string> vertices = g.getVertices();
    map<string,int> grado;
    map<string,bool> usado;
    for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
        list<string> sucesores = g.getSucesores(*it);
        for(list<string>::iterator jt = sucesores.begin();jt != sucesores.end();++jt){
            grado[*jt]++;
        }
    }
    int n = (int)vertices.size();
    for(int i = 0;i < n;i++){
        string act = "";
        bool hay = false;
        for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
            if(!usado[*it] && grado[*it] == 0 && (!hay || *it < act)){
                act = *it;
                hay = true;
            }
        }
        if(!hay){                                      // todos los restantes tienen predecesores: ciclo
            orden.clear();
            return false;
        }
        usado[act] = true;
        orden.push_back(act);
        list<string> sucesores = g.getSucesores(act);
        for(list<string>::iterator it = sucesores.begin();it != sucesores.end();++it){
            grado[*it]--;
        }
    }
    return true;
}

#endif
