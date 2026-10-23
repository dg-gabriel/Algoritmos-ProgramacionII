#ifndef NODOBIN_HPP
#define NODOBIN_HPP

#include <iostream>

template <class Element>
class NodoBin{
    private:
        Element info;
        NodoBin<Element> *hijoIzq,*hijoDer;
    public:
        NodoBin(Element e,NodoBin<Element> *i = NULL,NodoBin<Element> *d = NULL);   //O(1), constructor
        Element getInfo();                                                          // O(1), get
        NodoBin<Element>* getHijoIzq();                                             // O(1), get
        NodoBin<Element>* getHijoDer();                                             // O(1), get
        void setInfo(Element e);                                                    // O(1), set
        void setHijoIzq(NodoBin<Element>* i);                                       // O(1), set
        void setHijoDer(NodoBin<Element>* d);                                       // O(1), set
};

template <class Element>
NodoBin<Element>::NodoBin(Element e,NodoBin<Element> *i,NodoBin<Element> *d){
    info = e;
    hijoIzq = i;
    hijoDer = d;
}

template <class Element>
Element NodoBin<Element>::getInfo(){
    return info;
}

template <class Element>
NodoBin<Element>* NodoBin<Element>::getHijoIzq(){
    return hijoIzq;
}

template <class Element>
NodoBin<Element>* NodoBin<Element>::getHijoDer(){
    return hijoDer;
}

template <class Element>
void NodoBin<Element>::setInfo(Element e){
    info = e;
}

template <class Element>
void NodoBin<Element>::setHijoIzq(NodoBin<Element>* i){
    hijoIzq = i;
}

template <class Element>
void NodoBin<Element>::setHijoDer(NodoBin<Element>* d){
    hijoDer = d;
}

#endif