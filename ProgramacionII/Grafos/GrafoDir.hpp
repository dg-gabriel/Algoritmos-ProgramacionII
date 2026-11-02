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
        
    public:
        GrafoDir();                                                             // O(1), constructor
        GrafoDir(const GrafoDir<Element>& target);                              // O(n+m), constructor copia
        ~GrafoDir();                                                            // O(n+m), destructor
        GrafoDir<Element>& operator=(const GrafoDir<Element>& target);          // O(n+m), sobrecarga del op. de asignacion
        void insertarVertice(Element v);                                        // O(1), inserta nuevo vertice al principio
        void insertarArco(Element v,Element w,float p);                         // O(n), inserta nuevo arco al inicio de la lista de ady
        list<Element> getSucesores(Element v);                                  // O(n+k) k <= m, retorna una lista de quienes van despues de v (Grafo Dirigido)
        list<Element> getPredecesores(Element v);                               // O(n+k) k <= m, retorna una lista de quienes van antes de v (Grafo Dirigido)
        list<Element> getVecinos(Element v);                                    // O(n+m), retorna una lista de todos quienes inciden en v
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
        void vaciar();                                                          // O(n+m)
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
void GrafoDir<Element>::insertarVertice(Element v){
    NodoVertice<Element> nuevo = new NodoVertice<Element>(v,primero,NULL);
    primero = nuevo;
    nVertices++;
}

template <class Element>
void GrafoDir<Element>::insertarArco(Element v,Element w,float p){
    NodoVertice<Element> *ptrV,*ptrW;
    ptrV = buscarVertice(v);
    ptrW = buscarVertice(w);
    if(!ptrV || !ptrW){
        return;
    }
    insertarArcoAux(ptrV,ptrW,p);
    nArcos++;
}



#endif