#ifndef NODOVERTICE_HPP
#define NODOVERTICE_HPP

#include <iostream>
#include "NodoArco.hpp"

template <class Element>
class NodoVertice{
    private:
        Element: info;
        NodoVertice<Element>* sig;
        NodoArco<Element>* listaAdy;
    public:
        NodoVertice(Element e,NodoVertice<Element>* sig,NodoArco<Element>* listaAdy);
        Element getInfo();
        NodoVertice<Element>* getSiguiente();
        NodoArco<Element>* getListaAdyacencia();
        void setInfo(Element: e);
        void setSiguiente(NodoVertice<Element>* sig);
};

#endif