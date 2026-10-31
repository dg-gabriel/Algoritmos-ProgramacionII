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

        NodoVertice<Element>* buscarVertice(Element v);                                 // O(n)
        NodoArco<Element>* buscarArco(NodoVertice<Element>* v,NodoVertice<Element>* w); // O(arcos(v))
        void insertarArcoAux(NodoVertice<Element>* v,NodoVertice<Element>* w,float p);  // O(1), auxiliar de insercion
        bool eliminarArcoAux(NodoVertice<Element>* v,NodoVertice<Element>* w);          // O(arcos(o)), retorna true si exisita el arco                            
        int vaciarListaArcos(NodoArco<Element>* lista);                                 // vacia la lista de ady y retorna cuantos borro
        void copiarGrafo(const GrafoNoDir<Element>& target);                            // auxiliar para copiar un grafo
    public:
        GrafoNoDir();                                                           // O(1), constructor
        GrafoNoDir(const GrafoNoDir<Element>& target);                          // O(n+m), constructor copia
        ~GrafoNoDir();                                                          // O(n+m), destructor
        GrafoNoDir<Element>& operator=(const GrafoNoDir<Element>& target);      // O(n+m), sobrecarga del op. de asignacion
        void insertarVertice(Element v);                                        // O(1), inserta nuevo vertice al principio
        void insertarArco(Element v,Element w,float p);                         // O(n), inserta nuevo arco al inicio de ambas listas de ady
        list<Element> getVecinos(Element v);                                    // O(n+arcos(v)), retorna una lista de todos quienes inciden en v
        bool existeVertice(Element v);                                          // O(n), true si v esta en el grafo, false si no
        bool existeArco(Element v,Element w);                                   // O(n+k), true si hay un arco de v a w, false si no
        float getCostoArco(Element v,Element w);                                // O(n+k), retorna el costo del arco
        list<list<Element> > getArcos();                                        // O(n+m), retorna una lista de todas las adyacencias [[v1,v2],[v2,v3]]
        list<Element> getVertices();                                            // O(n), retorna la lista de todos los vertices
        bool esVacio();                                                         // O(1), ya sabes que hace esto
        void eliminarArco(Element v,Element w);                                 // O(n+k), elimina el arco entre v y w
        void eliminarVertice(Element v);                                        // O(n+m), elimina el vertice v y toda incidencia que haya en el
        void modificarPesoArco(Element v,Element w,float p);                    // O(n+k)
        int getNVertices();                                                     // O(1)
        int getNArcos();                                                        // O(1)
        list<Element> bfs(Element v);                                           // O(n+m), busqueda en anchura
        list<Element> dfs(Element v);                                           // O(n+m), busqueda en profundidad
        void vaciar();                                                          // O(n+m)
};

template <class Element>
NodoVertice<Element>* GrafoNoDir<Element>::buscarVertice(Element v){
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
void GrafoNoDir<Element>::insertarVertice(Element v){
    NodoVertice<Element>* nuevo = new NodoVertice<Element>(v,primero,NULL);
    primero = nuevo;
    nVertices++;
}

template <class Element>
void GrafoNoDir<Element>::insertarArco(Element v,Element w,float p){
    NodoVertice<Element> *ptrV,*ptrW;
    ptrV = buscarVertice(v);
    ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return;
    }
    if(ptrV == ptrW){
        insertarArcoAux(ptrV,ptrW,p);
    }
    else{
        insertarArcoAux(ptrV,ptrW,p);
        insertarArcoAux(ptrW,ptrV,p)
    }
    nArcos++;
}

template <class Element>
list<Element> GrafoNoDir<Element>::getVecinos(Element v){
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
bool GrafoNoDir<Element>::existeVertice(Element v){
    return buscarVertice(v) != NULL;
}

template <class Element>
bool GrafoNoDir<Element>::existeArco(Element v,Element w){
    NodoVertice<Element> *ptrV = buscarVertice(v),*ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return false
    }
    return buscarArco(ptrV,ptrW) != NULL;
}

#endif