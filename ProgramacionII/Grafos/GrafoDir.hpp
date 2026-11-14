#ifndef GRAFODIR_HPP
#define GRAFODIR_HPP

#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include "NodoVertice.hpp"
#include "NodoArco.hpp"

using namespace std;

template <class Element>
class GrafoDir{
    private:
        NodoVertice<Element>* primero;                                  
        int nVertices,nArcos;

        // metodos auxiliares
        NodoVertice<Element>* buscarVertice(const Element& v);                          // O(n)
        NodoArco<Element>* buscarArco(NodoVertice<Element>* v,NodoVertice<Element>* w); // O(arcos(v))
        void insertarArcoAux(NodoVertice<Element>* v,NodoVertice<Element>* w,float p);  // O(1), auxiliar de insercion
        bool eliminarArcoAux(NodoVertice<Element>* v,NodoVertice<Element>* w);          // O(arcos(o)), retorna true si exisita el arco      
        int vaciarListaArcos(NodoArco<Element>* lista);                                 // vacia la lista de ady y retorna cuantos borro
        void copiarGrafo(const GrafoDir<Element>& target);                              // auxiliar para copiar un grafo                      
        
    public:
        GrafoDir();                                                             // O(1), constructor
        GrafoDir(const GrafoDir<Element>& target);                              // O(n+m), constructor copia
        ~GrafoDir();                                                            // O(n+m), destructor
        GrafoDir<Element>& operator=(const GrafoDir<Element>& target);          // O(n+m), sobrecarga del op. de asignacion
        void insertarVertice(const Element& v);                                 // O(1), inserta nuevo vertice al principio
        void insertarArco(const Element& v,const Element& w,float p);           // O(n), inserta nuevo arco al inicio de la lista de ady
        list<Element> getSucesores(const Element& v);                           // O(n+k) k <= m, retorna una lista de quienes van despues de v (Grafo Dirigido)
        list<Element> getPredecesores(const Element& v);                        // O(n+k) k <= m, retorna una lista de quienes van antes de v (Grafo Dirigido)
        list<Element> getVecinos(const Element& v);                             // O(n+m), retorna una lista de todos quienes inciden en v
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
        void vaciar();                                                          // O(n+m)
        // tarjan para componentes fuertemente conexas
        // ordenamiento topologico (funciona solo en DAG)
        // get nro componentes conexas
        // tiene ciclo
        // mapear grafo

};

//////////// Privados //////////

template <class Element>
NodoVertice<Element>* GrafoDir<Element>::buscarVertice(const Element& v){
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
NodoArco<Element>* GrafoDir<Element>::buscarArco(NodoVertice<Element>* v,NodoVertice<Element>* w){
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
void GrafoDir<Element>::insertarArcoAux(NodoVertice<Element>* v, NodoVertice<Element>* w, float p){
    v->setListaAdy(new NodoArco<Element>(w, v->getListaAdy(), p));
}
 

template <class Element>
bool GrafoDir<Element>::eliminarArcoAux(NodoVertice<Element>* o, NodoVertice<Element>* d){
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
int GrafoDir<Element>::vaciarListaArcos(NodoArco<Element>* lista){
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
void GrafoDir<Element>::copiarGrafo(const GrafoDir<Element>& target){
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

/////////// Publicos ///////////

template <class Element>
GrafoDir<Element>::GrafoDir(){
    primero = NULL;
    nVertices = 0;
    nArcos = 0;
}

template <class Element>
GrafoDir<Element>::GrafoDir(const GrafoDir<Element>& target){
    copiarGrafo(target);
}

template <class Element>
GrafoDir<Element>::~GrafoDir(){
    vaciar();
}

template <class Element>
GrafoDir<Element>& GrafoDir<Element>::operator=(const GrafoDir<Element>& target){
    if(this == &target){
        return *this;
    }
    vaciar();
    copiarGrafo(target);
    return *this;
}

template <class Element>
void GrafoDir<Element>::insertarVertice(const Element& v){
    NodoVertice<Element> *nuevo = new NodoVertice<Element>(v,primero,NULL);
    primero = nuevo;
    nVertices++;
}

template <class Element>
void GrafoDir<Element>::insertarArco(const Element& v,const Element& w,float p){
    NodoVertice<Element> *ptrV,*ptrW;
    ptrV = buscarVertice(v);
    ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return;
    }
    insertarArcoAux(ptrV,ptrW,p);
    nArcos++;
}

template <class Element>
list<Element> GrafoDir<Element>::getSucesores(const Element& v){
    list<Element> res;
    NodoVertice<Element> *ptrV = buscarVertice(v);
    NodoArco<Element> *arcoV;
    if(ptrV){
        arcoV = ptrV->getListaAdy();
        while(arcoV){
            res.push_back(arcoV->getDestino()->getInfo());
            arcoV = arcoV->getSiguiente();
        }
    }
    return res;
}

template <class Element>
list<Element> GrafoDir<Element>::getSucesores(const Element &v){
    list<Element>: res; 
    NodoVertice<Element> *ptrV = buscarVertice(v);
    while(ptrV){
        NodoArco<Element> *arcoAct = ptrV->getListaAdy();
        while(arcoAct){
            
        }
    }
}

// sucesores y vecinos

template <class Element>
bool GrafoDir<Element>::existeVertice(const Element& v){
    return buscarVertice(v) != NULL;
}

template <class Element>
bool GrafoDir<Element>::existeArco(const Element& v,const Element& w){
    NodoVertice<Element> *ptrV = buscarVertice(v);
    NodoVertice<Element> *ptrW = buscarVertice(w);
    if(ptrV && ptrW){
        return buscarArco(ptrV,ptrW) != NULL;
    }
    return false;
}

template <class Element>
float GrafoDir<Element>::getCostoArco(const Element& v,const Element& w){
    NodoVertice<Element> *ptrV = buscarVertice(v);
    NodoVertice<Element> *ptrW = buscarVertice(w);
    if(ptrV && ptrW){
        NodoArco<Element> *ptrArco = buscarArco(ptrV,ptrW);
        if(ptrArco){
            return ptrArco->getPeso();
        }
    }
    return -1;
}

template <class Element>
list<list<Element> > GrafoDir<Element>::getArcos(){
    list<list<Element> > res;
    NodoVertice<Element>* act = primero;
    while(act){
        NodoArco<Element> *arcoAct = act->getListaAdy();
        while(arcoAct){
            list<Element> arco;
            arco.push_back(act->getInfo());
            arco.push_back(arcoAct->getDestino()->getInfo());
            res.push_back(arco);
            arcoAct = arcoAct->getSiguiente();
        }
        act = act->getSiguiente();
    }
    return res;
}

template <class Element>
list<Element> GrafoDir<Element>::getVertices(){
    list<Element> res;
    NodoVertice<Element> *act = primero;
    while(act){
        res.push_back(act->getInfo());
        act = act->getSiguiente();
    }
    return res;
}

template <class Element>
bool GrafoDir<Element>::esVacio(){
    return primero == NULL;
}

template <class Element>
void GrafoDir<Element>::eliminarArco(const Element& v,const Element& w){
    NodoVertice<Element> *ptrV = buscarVertice(v), *ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return;
    }
    if(eliminarArcoAux(ptrV, ptrW)){      
        nArcos--;                     
    }
}

template <class Element>
void GrafoDir<Element>::eliminarVertice(const Element& v){
    NodoVertice<Element>* ptrV = buscarVertice(v);
    if(!ptrV){
        return;
    }
    NodoVertice<Element>* act = primero;
    NodoVertice<Element>* ant = NULL;

    while(act){
        if(act != ptrV){
            if(eliminarArcoAux(act, ptrV)){
                nArcos--;
            }
        }
        if(act->getSiguiente() == ptrV){
            ant = act;
        }
        act = act->getSiguiente();
    }

    nArcos -= vaciarListaArcos(ptrV->getListaAdy());

    if(ptrV == primero){
        primero = ptrV->getSiguiente(); 
    }
    else if(ant){
        ant->setSiguiente(ptrV->getSiguiente()); 
    }

    delete ptrV;
    nVertices--;
}

template <class Element>
void GrafoDir<Element>::modificarPesoArco(const Element& v,const Element& w,float p){
    NodoVertice<Element> *ptrV = buscarVertice(v), *ptrW = buscarVertice(w);
    if(!ptrV || !ptrW || p < 0){
        return;
    }
    NodoArco<Element> *arcoAct = buscarArco(ptrV,ptrW);
    if(arcoAct){
        arcoAct->setPeso(p);
        if(ptrV != ptrW){
            buscarArco(ptrW,ptrV)->setPeso(p);
        }
    }
}

template <class Element>
int GrafoDir<Element>::getNVertices(){
    return nVertices;
}

template <class Element>
int GrafoDir<Element>::getNArcos(){
    return nArcos;
}

template <class Element>
void GrafoDir<Element>::vaciar(){
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