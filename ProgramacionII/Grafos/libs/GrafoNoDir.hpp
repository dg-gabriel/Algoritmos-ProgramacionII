#ifndef GRAFONODIR_HPP
#define GRAFONODIR_HPP

#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include "NodoVertice.hpp"
#include "NodoArco.hpp"

using namespace std;

template <class Element>
class GrafoNoDir{
    private:
        NodoVertice<Element>* primero;                                  
        int nVertices,nArcos;

        // metodos auxiliares
        NodoVertice<Element>* buscarVertice(const Element& v);                          // O(n)
        NodoArco<Element>* buscarArco(NodoVertice<Element>* v,NodoVertice<Element>* w); // O(arcos(v))
        void insertarArcoAux(NodoVertice<Element>* v,NodoVertice<Element>* w,float p);  // O(1), auxiliar de insercion
        bool eliminarArcoAux(NodoVertice<Element>* v,NodoVertice<Element>* w);          // O(arcos(o)), retorna true si exisita el arco                            
        int vaciarListaArcos(NodoArco<Element>* lista);                                 // vacia la lista de ady y retorna cuantos borro
        void copiarGrafo(const GrafoNoDir<Element>& target);                            // auxiliar para copiar un grafo
        void bfsAux(NodoVertice<Element>* inicio,                                       
                    map<NodoVertice<Element>*,bool>& visitado,                          // O(n+m), recorrido por niveles
                    list<Element>& recorrido); 
        void dfsAux(NodoVertice<Element>* act, 
                    map<NodoVertice<Element>*,bool>& visitado,                          // O(n+m), recorrido recursivo
                    list<Element>& recorrido);
        bool tieneCicloAux(NodoVertice<Element>* act,NodoVertice<Element>* padre
                            ,map<NodoVertice<Element>*,bool>& visitados);               // O(n+m), DFS con padre
        void dijkstraAux(NodoVertice<Element>* origen,NodoVertice<Element>* destino
                        ,map<NodoVertice<Element>*,float>& dist
                        ,map<NodoVertice<Element>*,NodoVertice<Element>*>& padre);      // O(n^2), pesos >= 0
        void tarjanAux(NodoVertice<Element>* v,NodoVertice<Element>* padre,int& tiempo
                      ,map<NodoVertice<Element>*,int>& disc
                      ,map<NodoVertice<Element>*,int>& low
                      ,list<Element>& puntos,list<list<Element> >& puentes);            // O(n+m), DFS con disc y low
        void calcularTarjan(list<Element>& puntos,list<list<Element> >& puentes);       // O(n+m), recorre todas las componentes
    public:
        GrafoNoDir();                                                           // O(1), constructor
        GrafoNoDir(const GrafoNoDir<Element>& target);                          // O(n+m), constructor copia
        ~GrafoNoDir();                                                          // O(n+m), destructor
        GrafoNoDir<Element>& operator=(const GrafoNoDir<Element>& target);      // O(n+m), sobrecarga del op. de asignacion
        void insertarVertice(const Element& v);                                 // O(1), inserta nuevo vertice al principio
        void insertarArco(const Element& v,const Element& w,float p);           // O(n), inserta nuevo arco al inicio de ambas listas de ady
        list<Element> getVecinos(const Element& v);                             // O(n+arcos(v)), retorna una lista de todos quienes inciden en v
        bool existeVertice(const Element& v);                                   // O(n), true si v esta en el grafo, false si no
        bool existeArco(const Element& v,const Element& w);                     // O(n+k), true si hay un arco de v a w, false si no
        float getCostoArco(const Element& v,const Element& w);                  // O(n+k), retorna el costo del arco
        list<list<Element> > getArcos();                                        // O(n+m), retorna una lista de todas las adyacencias [[v1,v2],[v2,v3]]
        list<Element> getVertices();                                            // O(n), retorna la lista de todos los vertices
        bool esVacio();                                                         // O(1), ya sabes que hace esto
        void eliminarArco(const Element& v,const Element& w);                   // O(n+k), elimina el arco entre v y w
        void eliminarVertice(const Element& v);                                 // O(n+m), elimina el vertice v y toda incidencia que haya en el
        void modificarPesoArco(const Element& v,const Element& w,float p);      // O(n+k)
        int getNVertices();                                                     // O(1)
        int getNArcos();                                                        // O(1)
        list<Element> bfs(const Element& v);                                    // O(n+m), busqueda en anchura
        list<Element> dfs(const Element& v);                                    // O(n+m), busqueda en profundidad
        int getNComponentesConexas();                                           // O(n+m), explora el grafo y retorna la cantidad de CCS
        bool tieneCiclo();                                                      // O(n+m), true si el grafo tiene al menos un ciclo
        list<Element> getCaminoMinimo(const Element& v,const Element& w);       // O((n+m) log n), camino de menor peso de v a w (Dijkstra), vacia si no hay
        float getCostoCaminoMinimo(const Element& v,const Element& w);          // O((n+m) log n), costo del camino minimo de v a w, -1 si no hay
        list<Element> getPuntosArticulacion();                                  // O(n+m), vertices cuya eliminacion desconecta el grafo
        list<list<Element> > getPuentes();                                      // O(n+m), aristas cuya eliminacion desconecta el grafo [[v1,v2],...]
        void imprimirGrafo() const;                                             // O(n+m), imprime el grafo para depurar
        void vaciar();                                                          // O(n+m), vacia el grafo
};

/////////// Privados ///////////

template <class Element>
NodoVertice<Element>* GrafoNoDir<Element>::buscarVertice(const Element& v){
    NodoVertice<Element>* act = primero;
    while(act){
        if(act->getInfo() == v){
            return act;
        }
        act = act->getSiguiente();
    }
    return NULL;
}

template <class Element>
NodoArco<Element>* GrafoNoDir<Element>::buscarArco(NodoVertice<Element>* v,NodoVertice<Element>* w){
    NodoArco<Element>* ptrArco = v->getListaAdy();
    while(ptrArco){
        if(ptrArco->getDestino() == w){
            return ptrArco;
        }
        ptrArco = ptrArco->getSiguiente();
    }
    return NULL;
}

template <class Element>
void GrafoNoDir<Element>::insertarArcoAux(NodoVertice<Element>* v, NodoVertice<Element>* w, float p){
    v->setListaAdy(new NodoArco<Element>(w, v->getListaAdy(), p));
}
 

template <class Element>
bool GrafoNoDir<Element>::eliminarArcoAux(NodoVertice<Element>* o, NodoVertice<Element>* d){
    NodoArco<Element>* act = o->getListaAdy();
    NodoArco<Element>* ant = NULL;
    while(act != NULL && act->getDestino() != d){
        ant = act;
        act = act->getSiguiente();
    }
    if(act == NULL){
        return false;
    }
    if(ant != NULL){
        ant->setSiguiente(act->getSiguiente());
    }
    else{
        o->setListaAdy(act->getSiguiente());
    }
    delete act;
    return true;
}

template <class Element>
int GrafoNoDir<Element>::vaciarListaArcos(NodoArco<Element>* lista){
    int cont = 0;
    NodoArco<Element> *sig,*act = lista;
    while(act){
        sig = act->getSiguiente();
        delete act;
        act = sig;
        cont++;
    }
    return cont;
}

template <class Element>
void GrafoNoDir<Element>::copiarGrafo(const GrafoNoDir<Element>& target){
    primero = NULL;
    map<NodoVertice<Element>*,NodoVertice<Element>*> mapa;
    NodoVertice<Element>* viejo = target.primero;
    NodoVertice<Element>* ult = NULL;

    while(viejo){
        NodoVertice<Element>* nuevo = new NodoVertice<Element>(viejo->getInfo(), NULL, NULL);
        mapa[viejo] = nuevo;
        if(!ult){
            primero = nuevo;
        }
        else{
            ult->setSiguiente(nuevo);
        }
        ult = nuevo;
        viejo = viejo->getSiguiente();
    }

    viejo = target.primero;
    while(viejo){
        NodoVertice<Element>* nuevo = mapa[viejo];
        NodoArco<Element>* arcoViejo = viejo->getListaAdy();
        NodoArco<Element>* colaArco = NULL;
        while(arcoViejo){
            NodoVertice<Element>* destinoNuevo = mapa[arcoViejo->getDestino()];
            NodoArco<Element>* arcoNuevo = new NodoArco<Element>(destinoNuevo, NULL, arcoViejo->getPeso());
            if(!colaArco){
                nuevo->setListaAdy(arcoNuevo);
            }
            else{
                colaArco->setSiguiente(arcoNuevo);
            }
            colaArco = arcoNuevo;
            arcoViejo = arcoViejo->getSiguiente();
        }
        viejo = viejo->getSiguiente();
    }
    nVertices = target.nVertices;
    nArcos = target.nArcos;
}

template <class Element>
void GrafoNoDir<Element>::bfsAux(NodoVertice<Element>* inicio, map<NodoVertice<Element>*, bool>& visitado, list<Element>& recorrido){
    queue<NodoVertice<Element>*> cola;
    cola.push(inicio);
    visitado[inicio] = true;                       

    while(!cola.empty()){
        NodoVertice<Element>* act = cola.front();
        cola.pop();
        recorrido.push_back(act->getInfo());

        NodoArco<Element>* arco = act->getListaAdy();
        while(arco){
            NodoVertice<Element>* destino = arco->getDestino();
            if(!visitado[destino]){
                visitado[destino] = true;
                cola.push(destino);
            }
            arco = arco->getSiguiente();
        }
    }
}

template <class Element>
void GrafoNoDir<Element>::dfsAux(NodoVertice<Element>* inicio, map<NodoVertice<Element>*, bool>& visitado, list<Element>& recorrido){
    stack<NodoVertice<Element>*> pila;
    pila.push(inicio);

    while(!pila.empty()){
        NodoVertice<Element>* act = pila.top();
        pila.pop();

        if(!visitado[act]){                           
            visitado[act] = true;
            recorrido.push_back(act->getInfo());

            list<NodoVertice<Element>*> vecinos;
            NodoArco<Element>* arco = act->getListaAdy();
            while(arco){
                if(!visitado[arco->getDestino()]){
                    vecinos.push_front(arco->getDestino());
                }
                arco = arco->getSiguiente();
            }
            typename list<NodoVertice<Element>*>::iterator it;
            for(it = vecinos.begin(); it != vecinos.end(); ++it){
                pila.push(*it);
            }
        }
    }
}

template <class Element>
bool GrafoNoDir<Element>::tieneCicloAux(NodoVertice<Element>* act,NodoVertice<Element>* padre,map<NodoVertice<Element>*,bool>& visitados){
    visitados[act] = true;
    bool padreSaltado = false;
    NodoArco<Element>* arco = act->getListaAdy();
    while(arco){
        NodoVertice<Element>* w = arco->getDestino();
        if(w == padre && !padreSaltado){
            padreSaltado = true;                   
        }
        else if(visitados[w]){
            return true;                            
        }
        else if(tieneCicloAux(w,act,visitados)){
            return true;
        }
        arco = arco->getSiguiente();
    }
    return false;
}

template <class Element>
void GrafoNoDir<Element>::dijkstraAux(NodoVertice<Element>* origen,NodoVertice<Element>* destino,map<NodoVertice<Element>*,float>& dist,map<NodoVertice<Element>*,NodoVertice<Element>*>& padre){
    map<NodoVertice<Element>*,bool> fijado;        
    dist[origen] = 0;

    bool seguir = true;
    while(seguir){
        NodoVertice<Element>* act = NULL;
        NodoVertice<Element>* cand = primero;
        while(cand){
            if(!fijado[cand] && dist.count(cand) == 1 && (act == NULL || dist[cand] < dist[act])){
                act = cand;
            }
            cand = cand->getSiguiente();
        }

        if(act == NULL || act == destino){
            seguir = false;                        
        }
        else{
            fijado[act] = true;
            NodoArco<Element>* arco = act->getListaAdy();
            while(arco){
                NodoVertice<Element>* w = arco->getDestino();
                float nueva = dist[act] + arco->getPeso();
                if(!fijado[w] && (dist.count(w) == 0 || nueva < dist[w])){
                    dist[w] = nueva;                
                    padre[w] = act;
                }
                arco = arco->getSiguiente();
            }
        }
    }
}

template <class Element>
void GrafoNoDir<Element>::tarjanAux(NodoVertice<Element>* v,NodoVertice<Element>* padre,int& tiempo,map<NodoVertice<Element>*,int>& disc,map<NodoVertice<Element>*,int>& low,list<Element>& puntos,list<list<Element> >& puentes){
    tiempo++;
    disc[v] = tiempo;
    low[v] = tiempo;
    int hijos = 0;
    bool esPunto = false;
    bool padreSaltado = false;

    NodoArco<Element>* arco = v->getListaAdy();
    while(arco){
        NodoVertice<Element>* w = arco->getDestino();
        if(w == padre && !padreSaltado){
            padreSaltado = true;
        }
        else if(disc[w] != 0){
            if(disc[w] < low[v]){
                low[v] = disc[w];
            }
        }
        else{
            hijos++;
            tarjanAux(w,v,tiempo,disc,low,puntos,puentes);
            if(low[w] < low[v]){
                low[v] = low[w];
            }
            if(low[w] > disc[v]){
                list<Element> puente;
                puente.push_back(v->getInfo());
                puente.push_back(w->getInfo());
                puentes.push_back(puente);
            }
            if(padre != NULL && low[w] >= disc[v]){ 
                esPunto = true;
            }
        }
        arco = arco->getSiguiente();
    }
    if((padre == NULL && hijos > 1) || esPunto){    
        puntos.push_back(v->getInfo());
    }
}

template <class Element>
void GrafoNoDir<Element>::calcularTarjan(list<Element>& puntos,list<list<Element> >& puentes){
    map<NodoVertice<Element>*,int> disc;
    map<NodoVertice<Element>*,int> low;
    int tiempo = 0;

    NodoVertice<Element>* act = primero;
    while(act){
        if(disc[act] == 0){
            tarjanAux(act,NULL,tiempo,disc,low,puntos,puentes);
        }
        act = act->getSiguiente();
    }
}

/////////// Publicos ///////////

template <class Element>
GrafoNoDir<Element>::GrafoNoDir(){
    primero = NULL;
    nVertices = 0;
    nArcos = 0;
}

template <class Element>
GrafoNoDir<Element>::GrafoNoDir(const GrafoNoDir<Element>& target){
    copiarGrafo(target);
}

template <class Element>
GrafoNoDir<Element>::~GrafoNoDir(){
    vaciar();
}

template <class Element>
GrafoNoDir<Element>& GrafoNoDir<Element>::operator=(const GrafoNoDir<Element>& target){
    if(this == &target){
        return *this;
    }
    vaciar();
    copiarGrafo(target);
    return *this;
}

template <class Element>
void GrafoNoDir<Element>::insertarVertice(const Element& v){
    NodoVertice<Element>* nuevo = new NodoVertice<Element>(v,primero,NULL);
    primero = nuevo;
    nVertices++;
}

template <class Element>
void GrafoNoDir<Element>::insertarArco(const Element& v,const Element& w,float p){
    NodoVertice<Element> *ptrV,*ptrW;
    ptrV = buscarVertice(v);
    ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return;
    }
    if(existeArco(v,w)){
        return;
    }
    if(ptrV == ptrW){
        insertarArcoAux(ptrV,ptrW,p);
    }
    else{
        insertarArcoAux(ptrV,ptrW,p);
        insertarArcoAux(ptrW,ptrV,p);
    }
    nArcos++;
}

template <class Element>
list<Element> GrafoNoDir<Element>::getVecinos(const Element& v){
    list<Element> res;
    NodoVertice<Element>* ptrV = buscarVertice(v);
    if(ptrV){
        NodoArco<Element>* arcos = ptrV->getListaAdy();
        while(arcos){
            res.push_back(arcos->getDestino()->getInfo());
            arcos = arcos->getSiguiente();
        }
    }
    return res;
}

template <class Element>
bool GrafoNoDir<Element>::existeVertice(const Element& v){
    return buscarVertice(v) != NULL;
}

template <class Element>
bool GrafoNoDir<Element>::existeArco(const Element& v,const Element& w){
    NodoVertice<Element> *ptrV = buscarVertice(v),*ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return false;
    }
    return buscarArco(ptrV,ptrW) != NULL;
}

template <class Element>
float GrafoNoDir<Element>::getCostoArco(const Element& v,const Element& w){
    NodoVertice<Element>* ptrV = buscarVertice(v),*ptrW = buscarVertice(w);
    if(ptrV && ptrW){
        NodoArco<Element>* ptrArco = buscarArco(ptrV,ptrW);
        if(ptrArco){
            return ptrArco->getPeso();
        }
    }
    return -1;
}

template <class Element>
list<list<Element> > GrafoNoDir<Element>::getArcos(){
    list<list<Element> > res;
    NodoVertice<Element>* act = primero;
    while(act){
        NodoArco<Element> *arcoAct = act->getListaAdy();
        while(arcoAct){
            if(arcoAct->getDestino()->getInfo() <= act->getInfo()){
                list<Element> arco;
                arco.push_back(act->getInfo());
                arco.push_back(arcoAct->getDestino()->getInfo());
                res.push_back(arco);
            }
            arcoAct = arcoAct->getSiguiente();
        }
        act = act->getSiguiente();
    }
    return res;
}

template <class Element>
list<Element> GrafoNoDir<Element>::getVertices(){
    list<Element> res;
    NodoVertice<Element> *act = primero;
    while(act){
        res.push_back(act->getInfo());
        act = act->getSiguiente();
    }
    return res;
}

template <class Element>
bool GrafoNoDir<Element>::esVacio(){
    return primero == NULL;
}

template <class Element>
void GrafoNoDir<Element>::eliminarArco(const Element& v,const Element& w){
    NodoVertice<Element> *ptrV = buscarVertice(v), *ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return;
    }
    if(eliminarArcoAux(ptrV, ptrW)){      
        if(ptrV != ptrW){
            eliminarArcoAux(ptrW, ptrV); 
        }
        nArcos--;                     
    }
}

template <class Element>
void GrafoNoDir<Element>::eliminarVertice(const Element& v){
    NodoVertice<Element> *ptrV = buscarVertice(v);
    if(!ptrV){
        return;
    }
    NodoArco<Element>* arcosV = ptrV->getListaAdy();
    while(arcosV){
        NodoVertice<Element> *w = arcosV->getDestino();
        if(w != ptrV){
            eliminarArcoAux(arcosV->getDestino(),ptrV);
        }
        arcosV = arcosV->getSiguiente();
    }
    nArcos -= vaciarListaArcos(ptrV->getListaAdy());

    NodoVertice<Element>* act = primero;
    NodoVertice<Element>* ant = NULL;
    while(act != ptrV){
        ant = act;
        act = act->getSiguiente();
    }
    if(ant){
        ant->setSiguiente(ptrV->getSiguiente());
    }
    else{
        primero = ptrV->getSiguiente();
    }
        
    delete ptrV;     
    nVertices--;
}

template <class Element>
void GrafoNoDir<Element>::modificarPesoArco(const Element& v,const Element& w,float p){
    NodoVertice<Element> *ptrV,*ptrW;
    ptrV = buscarVertice(v);
    ptrW = buscarVertice(w);
    if((!ptrV || !ptrW) || p < 0){
        return;
    }
    NodoArco<Element> *ptrArco = buscarArco(ptrV,ptrW);
    if(ptrArco){
        ptrArco->setPeso(p);
        if(ptrV != ptrW){
            NodoArco<Element> *ptrArcoRet = buscarArco(ptrW,ptrV);
            if(ptrArcoRet){
                ptrArcoRet->setPeso(p);
            }
        }
    }
    return;
}

template <class Element>
int GrafoNoDir<Element>::getNVertices(){
    return nVertices;
}

template <class Element>
int GrafoNoDir<Element>::getNArcos(){
    return nArcos;
}

template <class Element>
list<Element> GrafoNoDir<Element>::bfs(const Element& v){
    list<Element> recorrido;
    NodoVertice<Element>* inicio = buscarVertice(v);
    if(inicio){
        map<NodoVertice<Element>*, bool> visitado;
        bfsAux(inicio, visitado, recorrido);
    }
    return recorrido;
}

template <class Element>
list<Element> GrafoNoDir<Element>::dfs(const Element& v){
    list<Element> recorrido;
    NodoVertice<Element>* inicio = buscarVertice(v);
    if(inicio){
        map<NodoVertice<Element>*, bool> visitado;
        dfsAux(inicio, visitado, recorrido);
    }
    return recorrido;
}

template <class Element>
bool GrafoNoDir<Element>::tieneCiclo(){
    map<NodoVertice<Element>*,bool> visitados;
    NodoVertice<Element>* act = primero;
    while(act){
        if(!visitados[act] && tieneCicloAux(act,NULL,visitados)){
            return true;
        }
        act = act->getSiguiente();
    }
    return false;
}

template <class Element>
int GrafoNoDir<Element>::getNComponentesConexas(){
    int cont = 0;
    map<NodoVertice<Element>*,bool> visitados;
    list<Element> descartada;                 

    NodoVertice<Element>* act = primero;
    while(act){
        if(!visitados[act]){                       
            cont++;
            bfsAux(act,visitados,descartada);       
        }
        act = act->getSiguiente();
    }
    return cont;
}

template <class Element>
list<Element> GrafoNoDir<Element>::getCaminoMinimo(const Element& v,const Element& w){
    list<Element> camino;
    NodoVertice<Element>* ptrV = buscarVertice(v);
    NodoVertice<Element>* ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return camino;
    }
    map<NodoVertice<Element>*,float> dist;
    map<NodoVertice<Element>*,NodoVertice<Element>*> padre;
    dijkstraAux(ptrV,ptrW,dist,padre);

    if(dist.count(ptrW) == 0){
        return camino;                              
    }
    NodoVertice<Element>* act = ptrW;
    while(act != ptrV){
        camino.push_front(act->getInfo());
        act = padre[act];
    }
    camino.push_front(ptrV->getInfo());
    return camino;
}

template <class Element>
float GrafoNoDir<Element>::getCostoCaminoMinimo(const Element& v,const Element& w){
    NodoVertice<Element>* ptrV = buscarVertice(v);
    NodoVertice<Element>* ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return -1;
    }
    map<NodoVertice<Element>*,float> dist;
    map<NodoVertice<Element>*,NodoVertice<Element>*> padre;
    dijkstraAux(ptrV,ptrW,dist,padre);

    if(dist.count(ptrW) == 0){
        return -1;                                  
    }
    return dist[ptrW];
}

template <class Element>
list<Element> GrafoNoDir<Element>::getPuntosArticulacion(){
    list<Element> puntos;
    list<list<Element> > puentes;
    calcularTarjan(puntos,puentes);
    return puntos;
}

template <class Element>
list<list<Element> > GrafoNoDir<Element>::getPuentes(){
    list<Element> puntos;
    list<list<Element> > puentes;
    calcularTarjan(puntos,puentes);
    return puentes;
}

template <class Element>
void GrafoNoDir<Element>::imprimirGrafo() const {
    NodoVertice<Element>* act = primero;
    cout << "Total Vertices: " << nVertices << " | Total Arcos: " << nArcos << endl;
    
    while (act) {
        cout << "Vertice [" << act->getInfo() << "] -> ";
        NodoArco<Element>* arco = act->getListaAdy();
        
        if (!arco) {
            cout << "(Sin adyacencias)";
        }
        
        while (arco) {
            Element destino = arco->getDestino()->getInfo();
            float peso = arco->getPeso();
            cout << "[Destino: " << destino << ", Peso: " << peso << "] ";
            arco = arco->getSiguiente();
        }
        cout << endl;
        act = act->getSiguiente();
    }
    cout << "====================================" << endl;
}

template <class Element>
void GrafoNoDir<Element>::vaciar(){
    NodoVertice<Element>* act = primero;
    NodoVertice<Element>* sig;
    while(act){
        sig = act->getSiguiente();              
        vaciarListaArcos(act->getListaAdy());   
        delete act;                             
        act = sig;                              
    }
    primero = NULL;
    nVertices = 0;
    nArcos = 0;
}

#endif