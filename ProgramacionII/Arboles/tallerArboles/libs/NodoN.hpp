#ifndef NODON_HPP
#define NODON_HPP

#include <iostream>

template <class Element>
class NodoN{
    private:
        Element info;
        NodoN *hijoIzq,*hermanoDer;
    public:
        NodoN(Element i,NodoN<Element> *h = NULL,NodoN<Element> *d = NULL );  // O(1), constructor
        Element getInfo();                                                    // O(1), get
        NodoN<Element>* getHijoIzq();                                         // O(1), get
        NodoN<Element>* getHermanoDer();                                      // O(1), get
        void setInfo(Element i);                                              // O(1), set
        void setHijoIzq(NodoN<Element> *h);                                   // O(1), set
        void setHermanoDer(NodoN<Element> *d);                                // O(1), set

};

template <class Element>
NodoN<Element>::NodoN(Element i,NodoN<Element> *h,NodoN<Element> *d){
    info = i;
    hijoIzq = h;
    hermanoDer = d;
}

template <class Element>
Element NodoN<Element>::getInfo(){
    return info;
}

template <class Element>
NodoN<Element>* NodoN<Element>::getHijoIzq(){
    return hijoIzq;
}

template <class Element>
NodoN<Element>* NodoN<Element>::getHermanoDer(){
    return hermanoDer;
}

template <class Element>
void NodoN<Element>::setInfo(Element i){
    info = i;
}

template <class Element>
void NodoN<Element>::setHijoIzq(NodoN<Element>* h){
    hijoIzq = h;
}

template <class Element>
void NodoN<Element>::setHermanoDer(NodoN<Element>* d){
    hermanoDer = d;
}

#endif