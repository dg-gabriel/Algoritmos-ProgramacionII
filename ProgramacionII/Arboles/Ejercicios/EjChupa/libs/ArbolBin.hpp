#ifndef ARBOLBIN_HPP
#define ARBOLBIN_HPP

#include <iostream>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include "NodoBin.hpp"

using namespace std;

template <class Element>
class ArbolBin{
    private:
        NodoBin<Element> *raiz;
        int peso;

        NodoBin<Element>* copiarNodos(NodoBin<Element> *ptr);                  // O(n), auxiliar para const. copia
        int contarNodos(NodoBin<Element> *ptr);                                // O(n), auxiliar para calcular peso
        int alturaAux(NodoBin<Element> *ptr);                                  // O(n), auxiliar para calcular altura
        void destruirNodos(NodoBin<Element> *ptr);                             // O(n), auxiliar para vaciar
        void preOrdenAux(NodoBin<Element> *ptr,list<Element>& lista);          // auxiliar para recorrido preorden
        void inOrdenAux(NodoBin<Element> *ptr,list<Element>& lista);           // auxiliar para recorrido inorden
        void postOrdenAux(NodoBin<Element> *ptr,list<Element>& lista);         // auxiliar para recorrido postorden
        // auxiliares para construir el arbol a partir de recorridos
        NodoBin<Element>* construirPreInAux(list<Element>& preOrden,           
                            list<Element>& inOrden,bool tieneLimite,           
                            Element limite,int& contadorPeso);                 
        NodoBin<Element>* construirPostInAux(list<Element>& postOrden,
                            list<Element>& inOrden,bool tieneLimite,
                            Element limite,int& contadorPeso);
        // auxiliar para imprimir el arbol para debuggeo
        void imprimirArbolAux(NodoBin<Element> *nodo,string prefijo,bool esUltimo);
        // auxiliares para mapear el arbol
        void mapearNivelesAux(NodoBin<Element>* ptr, int nivelActual, map<Element, int>& mapa);
        void mapearPadresAux(NodoBin<Element>* ptr, map<Element, Element>& mapa);
        void mapearHijosAux(NodoBin<Element>* ptr, map<Element, list<Element> >& mapa);

    public:
        ArbolBin();                                                             // O(1), constructor
        ArbolBin(const ArbolBin<Element>& target);                              // O(n), constructor copia
        ~ArbolBin();                                                            // O(n), destructor
        ArbolBin<Element>& operator=(const ArbolBin<Element>& target);          // O(n), sobrecarga del op. de asignacion
        void construir(Element e,ArbolBin<Element> &a1,ArbolBin<Element> &a2);  // O(n), constructor de ensamblaje
        void copiar(ArbolBin<Element> &target);                                 // O(n), copia la instancia al target
        bool esNulo();                                                          // O(1), true si es vacio, false si no
        Element getRaiz();                                                      // O(1), retorna la raiz
        int getPeso();                                                          // O(1), retorna el peso
        int getAltura();                                                        // O(n), retorna la altura (vacio = -1, hoja = 0)
        ArbolBin<Element> getHijoIzq();                                         // O(n), retorna el hijo izquierdo como sub-arbol
        ArbolBin<Element> getHijoDer();                                         // O(n), retorna el hijo derecho como sub-arbol
        list<Element> preOrden();                                               // O(n), retorna una lista en recorrido preOrden
        list<Element> inOrden();                                                // O(n), retorna una lista en recorrido inOrden
        list<Element> postOrden();                                              // O(n), retorna una lista en recorrido postOrden
        void llenarPreIn(list<Element> preOrden,list<Element> inOrden);         // O(n) ambos, reconstruyen el arbol a partir de
        void llenarPostIn(list<Element> postOrden,list<Element> inOrden);       // dos recorridos almacenados en lista: inorden, pre/post orden
        void imprimirArbol();                                                   // O(n), imprime visualmente el arbol para depurar
        void mapearNiveles(map<Element, int>& mapa);                            // O(n), llena un mapa con el nivel de cada nodo
        void mapearPadres(map<Element, Element>& mapa);                         // O(n), llena un mapa con el padre de cada nodo
        void mapearHijos(map<Element, list<Element> >& mapa);                   // O(n), llena un mapa con los hijos de cada nodo (trivial en binarios)
        void vaciar();                                                          // O(n), vacia el arbol
};

template <class Element>
NodoBin<Element>* ArbolBin<Element>::copiarNodos(NodoBin<Element> *ptr){
    if(!ptr){
        return NULL;
    }
    else{
        NodoBin<Element>* nuevoN = new
        NodoBin<Element>(ptr->getInfo(),copiarNodos(ptr->getHijoIzq()),copiarNodos(ptr->getHijoDer()));
        return nuevoN;
    }
}

template <class Element>
int ArbolBin<Element>::contarNodos(NodoBin<Element> *ptr){
    if(!ptr){
        return 0;
    }
    return 1 + contarNodos(ptr->getHijoIzq()) + contarNodos(ptr->getHijoDer());
}

template <class Element>
int ArbolBin<Element>::alturaAux(NodoBin<Element> *ptr){
    if(!ptr){
        return -1;
    }
    return 1 + max(alturaAux(ptr->getHijoIzq()), alturaAux(ptr->getHijoDer()));
}

template <class Element>
void ArbolBin<Element>::destruirNodos(NodoBin<Element> *ptr){
    if(!ptr){
        return;
    }
    else{
        destruirNodos(ptr->getHijoIzq());
        destruirNodos(ptr->getHijoDer());
        delete ptr;
    }
}

template <class Element>
void ArbolBin<Element>::preOrdenAux(NodoBin<Element> *ptr,list<Element>& lista){
    if(ptr != NULL){
        lista.push_back(ptr->getInfo());
        preOrdenAux(ptr->getHijoIzq(), lista);
        preOrdenAux(ptr->getHijoDer(), lista);
    }
}

template <class Element>
void ArbolBin<Element>::inOrdenAux(NodoBin<Element>* ptr,list<Element>& lista) {
    if(ptr != NULL){
        inOrdenAux(ptr->getHijoIzq(), lista);
        lista.push_back(ptr->getInfo());
        inOrdenAux(ptr->getHijoDer(), lista);
    }
}

template <class Element>
void ArbolBin<Element>::postOrdenAux(NodoBin<Element>* ptr,list<Element>& lista) {
    if(ptr != NULL){
        postOrdenAux(ptr->getHijoIzq(), lista);
        postOrdenAux(ptr->getHijoDer(), lista);
        lista.push_back(ptr->getInfo());
    }
}

template <class Element>
NodoBin<Element>* ArbolBin<Element>::construirPreInAux(list<Element>& preOrden,list<Element>& inOrden, bool tieneLimite, Element limite,int& contadorPeso){
    if(preOrden.empty() || inOrden.empty()){
        return NULL;
    }

    if(tieneLimite && inOrden.front() == limite){
        return NULL;
    }

    Element datoRaiz = preOrden.front();
    preOrden.pop_front();

    NodoBin<Element>* nuevoNodo = new NodoBin<Element>(datoRaiz, NULL, NULL);
    contadorPeso++;

    nuevoNodo->setHijoIzq(construirPreInAux(preOrden, inOrden, true, datoRaiz, contadorPeso));
    inOrden.pop_front();
    nuevoNodo->setHijoDer(construirPreInAux(preOrden, inOrden,tieneLimite, limite, contadorPeso));

    return nuevoNodo;
}

template <class Element>
NodoBin<Element>* ArbolBin<Element>::construirPostInAux(list<Element>& postOrden,list<Element>& inOrden, bool tieneLimite, Element limite,int& contadorPeso){
    if(postOrden.empty() || inOrden.empty()){
        return NULL;
    }

    if(tieneLimite && inOrden.back() == limite){
        return NULL;
    }

    Element datoRaiz = postOrden.back();
    postOrden.pop_back();

    NodoBin<Element>* nuevoNodo = new NodoBin<Element>(datoRaiz, NULL, NULL);
    contadorPeso++;

    nuevoNodo->setHijoDer(construirPostInAux(postOrden, inOrden, true,datoRaiz, contadorPeso));
    inOrden.pop_back();
    nuevoNodo->setHijoIzq(construirPostInAux(postOrden, inOrden, tieneLimite, limite, contadorPeso));

    return nuevoNodo;
}

template <class Element>
void ArbolBin<Element>::imprimirArbolAux(NodoBin<Element>* nodo,string prefijo,bool esUltimo){
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

    imprimirArbolAux(nodo->getHijoIzq(),nuevoPrefijo,nodo->getHijoDer() == NULL);
    imprimirArbolAux(nodo->getHijoDer(),nuevoPrefijo,true);
}

template <class Element>
void ArbolBin<Element>::mapearNivelesAux(NodoBin<Element>* ptr, int nivelActual, map<Element, int>& mapa){
    if(!ptr){
        return;
    }
    mapa[ptr->getInfo()] = nivelActual;
    mapearNivelesAux(ptr->getHijoIzq(), nivelActual + 1, mapa);
    mapearNivelesAux(ptr->getHijoDer(), nivelActual + 1, mapa);
}

template <class Element>
void ArbolBin<Element>::mapearPadresAux(NodoBin<Element>* ptr, map<Element, Element>& mapa){
    if(!ptr){
        return;
    }
    if(ptr->getHijoIzq() != NULL){
        mapa[ptr->getHijoIzq()->getInfo()] = ptr->getInfo();
        mapearPadresAux(ptr->getHijoIzq(), mapa);
    }
    if(ptr->getHijoDer() != NULL){
        mapa[ptr->getHijoDer()->getInfo()] = ptr->getInfo();
        mapearPadresAux(ptr->getHijoDer(), mapa);
    }
}

template <class Element>
void ArbolBin<Element>::mapearHijosAux(NodoBin<Element>* ptr, map<Element, list<Element> >& mapa){
    if(!ptr){
        return;
    }
    
    if(mapa.find(ptr->getInfo()) == mapa.end()){
        mapa[ptr->getInfo()] = list<Element>(); 
    }

    if(ptr->getHijoIzq() != NULL){
        mapa[ptr->getInfo()].push_back(ptr->getHijoIzq()->getInfo());
        mapearHijosAux(ptr->getHijoIzq(), mapa);
    }
    
    if(ptr->getHijoDer() != NULL){
        mapa[ptr->getInfo()].push_back(ptr->getHijoDer()->getInfo());
        mapearHijosAux(ptr->getHijoDer(), mapa);
    }
}

template <class Element>
ArbolBin<Element>::ArbolBin(){
    raiz = NULL;
    peso = 0;
}

template <class Element>
ArbolBin<Element>::ArbolBin(const ArbolBin<Element> &target){
    raiz = copiarNodos(target.raiz);
    peso = target.peso;
}

template <class Element>
ArbolBin<Element>::~ArbolBin(){
    vaciar();
}

template <class Element>
ArbolBin<Element>& ArbolBin<Element>::operator=(const ArbolBin<Element>& target){
    if(this == &target){
        return *this;
    }
    vaciar();
    raiz = copiarNodos(target.raiz);
    peso = target.peso;
    return *this;
}

template <class Element>
void ArbolBin<Element>::construir(Element e, ArbolBin<Element> &a1, ArbolBin<Element> &a2){
    NodoBin<Element>* izq = copiarNodos(a1.raiz);
    NodoBin<Element>* der = copiarNodos(a2.raiz);
    int nuevoPeso = a1.peso + a2.peso + 1;

    vaciar();

    raiz = new NodoBin<Element>(e, izq, der);
    peso = nuevoPeso;
}

template <class Element>
void ArbolBin<Element>::copiar(ArbolBin<Element> &target){
    target = *this;
}

template <class Element>
bool ArbolBin<Element>::esNulo(){
    return raiz == NULL;
}

template <class Element>
Element ArbolBin<Element>::getRaiz(){
    return raiz->getInfo();
}

template <class Element>
int ArbolBin<Element>::getPeso(){
    return peso;
}

template <class Element>
int ArbolBin<Element>::getAltura(){
    return alturaAux(raiz);
}

template <class Element>
ArbolBin<Element> ArbolBin<Element>::getHijoIzq(){
    ArbolBin<Element> subArbol;

    if(raiz){
        subArbol.raiz = copiarNodos(raiz->getHijoIzq());
        subArbol.peso = contarNodos(subArbol.raiz);
    }

    return subArbol;
}

template <class Element>
ArbolBin<Element> ArbolBin<Element>::getHijoDer(){
    ArbolBin<Element> subArbol;

    if(raiz){
        subArbol.raiz = copiarNodos(raiz->getHijoDer());
        subArbol.peso = contarNodos(subArbol.raiz);
    }

    return subArbol;
}

template <class Element>
list<Element> ArbolBin<Element>::preOrden(){
    list<Element> resultado;
    preOrdenAux(raiz, resultado);
    return resultado;
}

template <class Element>
list<Element> ArbolBin<Element>::inOrden(){
    list<Element> resultado;
    inOrdenAux(raiz, resultado);
    return resultado;
}

template <class Element>
list<Element> ArbolBin<Element>::postOrden(){
    list<Element> resultado;
    postOrdenAux(raiz, resultado);
    return resultado;
}

template <class Element>
void ArbolBin<Element>::llenarPreIn(list<Element> preOrden,list<Element> inOrden){
    vaciar();
    int nodosEnsamblados = 0;
    raiz = construirPreInAux(preOrden, inOrden, false, Element(), nodosEnsamblados);
    this->peso = nodosEnsamblados;
}

template <class Element>
void ArbolBin<Element>::llenarPostIn(list<Element> postOrden,list<Element> inOrden){
    vaciar();
    int nodosEnsamblados = 0;
    raiz = construirPostInAux(postOrden, inOrden, false, Element(), nodosEnsamblados);
    this->peso = nodosEnsamblados;
}

template <class Element>
void ArbolBin<Element>::imprimirArbol(){
    if(raiz == NULL){
        cout << "(vacio)" << endl;
        return;
    }

    cout << raiz->getInfo() << endl;

    imprimirArbolAux(raiz->getHijoIzq(),"",raiz->getHijoDer() == NULL);
    imprimirArbolAux(raiz->getHijoDer(),"",true);
}

template <class Element>
void ArbolBin<Element>::mapearNiveles(map<Element, int>& mapa){
    mapa.clear(); 
    mapearNivelesAux(raiz, 0, mapa); 
}

template <class Element>
void ArbolBin<Element>::mapearPadres(map<Element, Element>& mapa){
    mapa.clear();
    mapearPadresAux(raiz, mapa); 
}

template <class Element>
void ArbolBin<Element>::mapearHijos(map<Element, list<Element> >& mapa){
    mapa.clear();
    mapearHijosAux(raiz, mapa);
}

template <class Element>
void ArbolBin<Element>::vaciar(){
    destruirNodos(raiz);
    raiz = NULL;
    peso = 0;
}

#endif