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

#endif