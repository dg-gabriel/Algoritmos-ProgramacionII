#ifndef NODOARCO_HPP
#define NODOARCO_HPP

#include <iostream>
#include "NodoVertice.hpp"

template <class Element>
class NodoArco{
    private:
        NodoVertice<Element>* info;
        NodoArco<Element>* sig
        float peso;
    public
        NodoArco(NodoVertice<Element>* info,NodoArco<Element>* sig,float peso);

};

#endif