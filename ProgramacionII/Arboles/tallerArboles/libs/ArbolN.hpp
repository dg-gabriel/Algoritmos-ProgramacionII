#ifndef ARBOLN_HPP
#define ARBOLN_HPP

#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <map>
#include <algorithm>
#include "NodoN.hpp"

using namespace std;

template <class Element>
class ArbolN{
    private:
        NodoN<Element> *raiz;
        int peso;

        NodoN<Element>* copiarNodos(NodoN<Element>* ptr);                       // O(n), aux para constr. copia
        int contarNodos(NodoN<Element> *ptr);                                   // O(n), aux para obtener peso
        int alturaAux(NodoN<Element> *ptr);                                     // O(n), aux para obtener altura
        void destruirNodo(NodoN<Element>* ptr);                                 // O(n), aux para vaciar
        void preOrdenAux(NodoN<Element> *ptr,list<Element>& lista);             // auxiliares para recorridos 
        void inOrdenAux(NodoN<Element> *ptr,list<Element>& lista);
        void postOrdenAux(NodoN<Element> *ptr,list<Element>& lista);
        // auxiliar para imprimir el arbol
        void imprimirArbolAux(NodoN<Element> *ptr,string prefijo,bool esUltimo);
         // auxiliares para mapeo
        void mapearNivelesAux(NodoN<Element>* ptr, int nivelActual, map<Element, int>& mapa);
        void mapearPadresAux(NodoN<Element>* ptr, map<Element, Element>& mapa);
        void mapearHijosAux(NodoN<Element>* ptr, map<Element, list<Element> >& mapa);

    public:
        ArbolN();                                                               // O(1), constructor
        ArbolN(const ArbolN<Element> &target);                                  // O(n), constructor copia
        ~ArbolN();                                                              // O(n), destructor
        ArbolN<Element>& operator=(const ArbolN<Element>& target);              // O(n), sobrecarga del operador de asignacion
        void construir(Element e,list<ArbolN<Element> > hijos);                 // O(n), constructor de ensamble
        bool esNulo();                                                          // O(1), true si es vacio
        Element getRaiz();                                                      // O(1), devuelve el elemento raiz
        int getPeso();                                                          // O(1), devuelve el peso
        int getAltura();                                                        // O(n), devuelve la altura (vacio = -1, hoja = 0)
        list<ArbolN<Element> > getHijos();                                      // O(n), devuelve una lista de los hijos
        void insertarSubArbol(const ArbolN<Element>& arbol);                    // O(n), añade un subArbol al arbol existente
        void eliminarSubArbol(int pos);                                         // O(n), elimina el nodo en la pos n y sus descendientes
        ArbolN<Element> copiar();                                               // O(n), retorna una copia del arbol
        list<Element> preOrden();                                               // O(n), recorrido en preorden
        list<Element> inOrden();                                                // O(n), recorrido en inorden
        list<Element> postOrden();                                              // O(n), recorrido en postorden
        list<list<Element> > recorridoPorNiveles();                             // O(n), retorna una lista de listas, donde cada posicion es un nivel del arbol
        void imprimirArbol();                                                   // O(n), visualizacion del arbol para depurar
        void mapearNiveles(map<Element, int>& mapa);                            // O(n), llena un mapa con el nivel de cada nodo
        void mapearPadres(map<Element, Element>& mapa);                         // O(n), llena un mapa con el padre de cada nodo
        void mapearHijos(map<Element, list<Element> >& mapa);                   // O(n), llena un mapa con los hijos de cada nodo
        void llenarPadresHijos(list<Element> padres, list<Element> hijos);      // O(nlogn), llenado desde una columna (lista) de padres y una de hijos
        void vaciar();                                                          // O(n), llama a destruirNodo para limpiar el arbol
};

template <class Element>
NodoN<Element>* ArbolN<Element>::copiarNodos(NodoN<Element>* ptr){
    if(!ptr){
        return NULL;
    }

    NodoN<Element>* primero = NULL;
    NodoN<Element>* ultimo = NULL;
    NodoN<Element>* actual = ptr;

    while(actual != NULL){
        NodoN<Element>* nuevo = new NodoN<Element>(actual->getInfo(),copiarNodos(actual->getHijoIzq()),NULL);

        if(primero == NULL){
            primero = nuevo;
        }
        else{
            ultimo->setHermanoDer(nuevo);
        }
        ultimo = nuevo;
        actual = actual->getHermanoDer();
    }

    return primero;
}

template <class Element>
int ArbolN<Element>::contarNodos(NodoN<Element> *ptr){
    int total = 0;
    NodoN<Element>* actual = ptr;
    
    while(actual != NULL){
        total += 1 + contarNodos(actual->getHijoIzq());
        actual = actual->getHermanoDer();
    }
    return total;
}

template <class Element>
int ArbolN<Element>::alturaAux(NodoN<Element> *ptr){
    if(!ptr){
        return -1;
    }
    int maxAltHijo = -1;
    NodoN<Element>* hijo = ptr->getHijoIzq();
    while(hijo != NULL){
        maxAltHijo = max(maxAltHijo, alturaAux(hijo));
        hijo = hijo->getHermanoDer();
    }
    return 1 + maxAltHijo;
}

template <class Element>
void ArbolN<Element>::destruirNodo(NodoN<Element>* ptr){
    NodoN<Element>* actual = ptr;
    

    while(actual != NULL){
        NodoN<Element>* sigHermano = actual->getHermanoDer();
        destruirNodo(actual->getHijoIzq()); 
        delete actual;                      
        actual = sigHermano;
    }
}

template <class Element>
void ArbolN<Element>::preOrdenAux(NodoN<Element>* ptr,list<Element>& lista) {
    if (ptr != NULL) {
        lista.push_back(ptr->getInfo());

        NodoN<Element>* aux = ptr->getHijoIzq();
        while (aux != NULL) {
            preOrdenAux(aux, lista);
            aux = aux->getHermanoDer();
        }
    }
}

template <class Element>
void ArbolN<Element>::inOrdenAux(NodoN<Element>* ptr,list<Element>& lista) {
    if (ptr != NULL) {
        inOrdenAux(ptr->getHijoIzq(), lista);

        lista.push_back(ptr->getInfo());

        if (ptr->getHijoIzq() != NULL) {
            NodoN<Element>* aux = ptr->getHijoIzq()->getHermanoDer();
            while (aux != NULL) {
                inOrdenAux(aux, lista);
                aux = aux->getHermanoDer();
            }
        }
    }
}

template <class Element>
void ArbolN<Element>::postOrdenAux(NodoN<Element>* ptr, list<Element>& lista) {
    if (ptr != NULL) {
        NodoN<Element>* aux = ptr->getHijoIzq();
        while (aux != NULL) {
            postOrdenAux(aux, lista);
            aux = aux->getHermanoDer();
        }

        lista.push_back(ptr->getInfo());
    }
}

template <class Element>
void ArbolN<Element>::imprimirArbolAux(NodoN<Element>* nodo,string prefijo,bool esUltimo){
    if(nodo == NULL){
        return;
    }

    cout << prefijo;

    if(esUltimo){
        cout << "\\-- ";
    }
    else{
        cout << "|-- ";
    }

    cout << nodo->getInfo() << endl;

    string nuevoPrefijo = prefijo;

    if(esUltimo){
        nuevoPrefijo += "    ";
    }
    else{
        nuevoPrefijo += "|   ";
    }

    NodoN<Element>* hijo = nodo->getHijoIzq();

    while(hijo != NULL){
        imprimirArbolAux(
            hijo,
            nuevoPrefijo,
            hijo->getHermanoDer() == NULL
        );

        hijo = hijo->getHermanoDer();
    }
}

template <class Element>
void ArbolN<Element>::mapearNivelesAux(NodoN<Element>* ptr, int nivelActual, map<Element, int>& mapa){
    if(!ptr){
        return;
    }
    mapa[ptr->getInfo()] = nivelActual;
    
    NodoN<Element>* hijo = ptr->getHijoIzq();
    while(hijo != NULL){
        mapearNivelesAux(hijo, nivelActual + 1, mapa);
        hijo = hijo->getHermanoDer();
    }
}

template <class Element>
void ArbolN<Element>::mapearPadresAux(NodoN<Element>* ptr, map<Element, Element>& mapa){
    if(!ptr){
        return;
    }
    
    NodoN<Element>* hijo = ptr->getHijoIzq();
    while(hijo != NULL){
        mapa[hijo->getInfo()] = ptr->getInfo();
        mapearPadresAux(hijo, mapa);
        hijo = hijo->getHermanoDer();
    }
}

template <class Element>
void ArbolN<Element>::mapearHijosAux(NodoN<Element>* ptr, map<Element, list<Element> >& mapa){
    if(!ptr){
        return;
    }
    
    if(mapa.find(ptr->getInfo()) == mapa.end()){
        mapa[ptr->getInfo()] = list<Element>();
    }

    NodoN<Element>* hijo = ptr->getHijoIzq();
    while(hijo != NULL){
        mapa[ptr->getInfo()].push_back(hijo->getInfo());
        
        mapearHijosAux(hijo, mapa);
        
        hijo = hijo->getHermanoDer();
    }
}

template <class Element>
ArbolN<Element>::ArbolN(){
    raiz = NULL;
    peso = 0;
}

template <class Element>
ArbolN<Element>::ArbolN(const ArbolN<Element>& target){
    raiz = copiarNodos(target.raiz);
    peso = target.peso;
}

template <class Element>
ArbolN<Element>::~ArbolN(){
    vaciar();
}

template <class Element>
ArbolN<Element>& ArbolN<Element>::operator=(const ArbolN<Element>& target){
    if(this == &target){
        return *this;
    }
    vaciar();
    raiz = copiarNodos(target.raiz);
    peso = target.peso;
    return *this;
}

template <class Element>
void ArbolN<Element>::construir(Element e,list<ArbolN<Element> > hijos){
    vaciar();
    raiz = new NodoN<Element>(e,NULL,NULL);
    peso = 1;

    NodoN<Element>* cursor = NULL;

    for(typename std::list<ArbolN<Element> >::iterator it = hijos.begin(); it != hijos.end(); ++it){
        if(it->raiz != NULL){
            NodoN<Element>* copiaHijo = copiarNodos(it->raiz);
            peso += it->peso;

            if(cursor == NULL){
                raiz->setHijoIzq(copiaHijo);
            }
            else{
                cursor->setHermanoDer(copiaHijo);
            }
            cursor = copiaHijo;
        }
    }
}

template <class Element>
bool ArbolN<Element>::esNulo(){
    return raiz == NULL;
}

template <class Element>
Element ArbolN<Element>::getRaiz(){
    return raiz->getInfo();
}

template <class Element>
int ArbolN<Element>::getPeso(){
    return peso;
}

template <class Element>
int ArbolN<Element>::getAltura(){
    return alturaAux(raiz);
}

template <class Element>
list<ArbolN<Element> > ArbolN<Element>::getHijos(){
    list<ArbolN<Element> > listaResultado;

    if(!raiz){
        return listaResultado;
    }

    NodoN<Element>* cursor = raiz->getHijoIzq();

    while(cursor){
        ArbolN<Element> subArbol;

        subArbol.raiz = new
        NodoN<Element>(cursor->getInfo(),copiarNodos(cursor->getHijoIzq()),NULL);
        subArbol.peso = contarNodos(subArbol.raiz);

        listaResultado.push_back(subArbol);
        cursor = cursor->getHermanoDer();
    }
    return listaResultado;
}

template <class Element>
void ArbolN<Element>::insertarSubArbol(const ArbolN<Element>& arbol){
    if(!raiz || !arbol.raiz){
        return;
    }

    if(!raiz->getHijoIzq()){
        raiz->setHijoIzq(copiarNodos(arbol.raiz));
    }
    else{
        NodoN<Element>* cursor = raiz->getHijoIzq();
        while(cursor->getHermanoDer()){
            cursor = cursor->getHermanoDer();
        }
        cursor->setHermanoDer(copiarNodos(arbol.raiz));
    }
    peso += arbol.peso;
}

template <class Element>
void ArbolN<Element>::eliminarSubArbol(int pos){
    if(!raiz || pos <= 0 || !raiz->getHijoIzq()){
        return;
    }
    if(pos == 1){
        NodoN<Element>* act = raiz->getHijoIzq();
        raiz->setHijoIzq(act->getHermanoDer());
        act->setHermanoDer(NULL);
        int nodosElim = contarNodos(act);
        peso -= nodosElim;
        destruirNodo(act);
    }
    else{
        NodoN<Element>* ant = raiz->getHijoIzq();
        NodoN<Element>* act = ant->getHermanoDer();
        int i = 2;
        while(act && i < pos){
            ant = act;
            act = act->getHermanoDer();
            i++;
        }
        if(act == NULL){
            return;
        }
        ant->setHermanoDer(act->getHermanoDer());
        act->setHermanoDer(NULL);
        int nodosElim = contarNodos(act);
        peso -= nodosElim;
        destruirNodo(act);
    }
}

template <class Element>
ArbolN<Element> ArbolN<Element>::copiar(){
    return ArbolN<Element>(*this);
}

template <class Element>
list<Element> ArbolN<Element>::preOrden(){
    list<Element> resultado;
    preOrdenAux(raiz, resultado);
    return resultado;
}

template <class Element>
list<Element> ArbolN<Element>::inOrden(){
    list<Element> resultado;
    inOrdenAux(raiz, resultado);
    return resultado;
}

template <class Element>
list<Element> ArbolN<Element>::postOrden(){
    list<Element> resultado;
    postOrdenAux(raiz, resultado);
    return resultado;
}

template <class Element>
list<list<Element> > ArbolN<Element>::recorridoPorNiveles(){
    list<list<Element> > resultado;
    if (raiz == NULL) return resultado;

    queue<NodoN<Element>*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        int len = cola.size(); 
        list<Element> nivelActual;

        for (int i = 0; i < len; i++) {
            NodoN<Element>* actual = cola.front();
            cola.pop();

            nivelActual.push_back(actual->getInfo());

            NodoN<Element>* hijo = actual->getHijoIzq();
            while (hijo != NULL) {
                cola.push(hijo);
                hijo = hijo->getHermanoDer();
            }
        }
        resultado.push_back(nivelActual); 
    }
    return resultado;
}

template <class Element>
void ArbolN<Element>::imprimirArbol(){
    if(raiz == NULL){
        cout << "(vacio)" << endl;
        return;
    }

    cout << raiz->getInfo() << endl;

    NodoN<Element>* hijo = raiz->getHijoIzq();

    while(hijo != NULL){
        imprimirArbolAux(hijo,"",hijo->getHermanoDer() == NULL);
        hijo = hijo->getHermanoDer();
    }
}

template <class Element>
void ArbolN<Element>::mapearNiveles(map<Element, int>& mapa){
    mapa.clear();
    mapearNivelesAux(raiz, 0, mapa);
}

template <class Element>
void ArbolN<Element>::mapearPadres(map<Element, Element>& mapa){
    mapa.clear();
    mapearPadresAux(raiz, mapa);
}

template <class Element>
void ArbolN<Element>::mapearHijos(map<Element, list<Element> >& mapa){
    mapa.clear();
    mapearHijosAux(raiz, mapa);
}

template <class Element>
void ArbolN<Element>::llenarPadresHijos(list<Element> padres, list<Element> hijos){
    vaciar();
    
    if(padres.empty() && hijos.empty()){
        return;
    }

    Element datoRaiz = padres.front();
    raiz = new NodoN<Element>(datoRaiz, NULL, NULL);
    peso = 1;

    if(hijos.empty()){
        return; 
    }

    map<Element, NodoN<Element>* > nodos;
    map<Element, NodoN<Element>* > ultimoHijo;

    nodos[datoRaiz] = raiz;

    while(!padres.empty() && !hijos.empty()){
        Element p = padres.front();
        Element h = hijos.front();
        padres.pop_front();
        hijos.pop_front();

        if(nodos[p] == NULL){
            nodos[p] = new NodoN<Element>(p, NULL, NULL);
            peso++;
        }
        if(nodos[h] == NULL){
            nodos[h] = new NodoN<Element>(h, NULL, NULL);
            peso++;
        }

        NodoN<Element>* nodoPadre = nodos[p];
        NodoN<Element>* nodoHijo = nodos[h];

        if(nodoPadre->getHijoIzq() == NULL){
            nodoPadre->setHijoIzq(nodoHijo);
        }
        else{
            ultimoHijo[p]->setHermanoDer(nodoHijo);
        }
        ultimoHijo[p] = nodoHijo;
    }
}

template <class Element>
void ArbolN<Element>::vaciar(){
    destruirNodo(raiz);
    raiz = NULL;
    peso = 0;
}

#endif