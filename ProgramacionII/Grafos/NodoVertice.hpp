#ifndef NODOVERTICE_HPP
#define NODOVERTICE_HPP

#include <iostream>
template <class Element> class NodoArco;

template <class Element>
class NodoVertice{
    private:
        Element info;
        NodoVertice<Element>* sig;
        NodoArco<Element>* listaAdy;
    public:
        NodoVertice(Element e,NodoVertice<Element>* s,NodoArco<Element>* l);
        Element getInfo();
        NodoVertice<Element>* getSiguiente();
        NodoArco<Element>* getListaAdy();
        void setInfo(Element e);
        void setSiguiente(NodoVertice<Element>* sig);
        void setListaAdy(NodoArco<Element>* lista);
};

template <class Element>
NodoVertice<Element>::NodoVertice(Element e,NodoVertice<Element>* s,NodoArco<Element>* l){
    info = e;
    sig = s;
    listaAdy = l;
}

template <class Element>
Element NodoVertice<Element>::getInfo(){
    return info;
}

template <class Element>
NodoVertice<Element>* NodoVertice<Element>::getSiguiente(){
    return sig;
}

template <class Element>
NodoArco<Element>* NodoVertice<Element>::getListaAdy(){
    return listaAdy;
}

template <class Element>
void NodoVertice<Element>::setInfo(Element e){
    info = e;
}

template <class Element>
void NodoVertice<Element>::setSiguiente(NodoVertice<Element>* s){
    sig = s;
}

template <class Element>
void NodoVertice<Element>::setListaAdy(NodoArco<Element>* l){
    listaAdy = l;
}

#endif