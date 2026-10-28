#ifndef NODOARCO_HPP
#define NODOARCO_HPP

#include <iostream>
template <class Element> class NodoVertice;

template <class Element>
class NodoArco{
    private:
        NodoVertice<Element>* destino;
        NodoArco<Element>* sig;
        float peso;
    public:
        NodoArco(NodoVertice<Element>* d,NodoArco<Element>* s,float p);
        NodoVertice<Element>* getDestino();
        NodoArco<Element>* getSiguiente();
        float getPeso();
        void setDestino(NodoVertice<Element>* d);
        void setSiguiente(NodoArco<Element>* s);
        void setPeso(float p);
};

template <class Element>
NodoArco<Element>::NodoArco(NodoVertice<Element>* d,NodoArco<Element>* s,float p){
    destino = d;
    sig = s;
    peso = p;
}

template <class Element>
NodoVertice<Element>* NodoArco<Element>::getDestino(){
    return destino;
}

template <class Element>
NodoArco<Element>* NodoArco<Element>::getSiguiente(){
    return sig;
}

template <class Element>
float NodoArco<Element>::getPeso(){
    return peso;
}

template <class Element>
void NodoArco<Element>::setDestino(NodoVertice<Element>* d){
    destino = d;
}

template <class Element>
void NodoArco<Element>::setSiguiente(NodoArco<Element>* s){
    sig = s;
}

template <class Element>
void NodoArco<Element>::setPeso(float p){
    peso = p;
}

#endif