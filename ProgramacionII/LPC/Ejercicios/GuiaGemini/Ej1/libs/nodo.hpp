#ifndef NODO_HPP
#define NODO_HPP

#include <iostream>

template <class Element>
class Nodo{
    private:
        Element info;
        Nodo<Element>* prox;

    public:
        Nodo(Element v,Nodo<Element>* p = NULL);   //O(1), constructor
        Element getInfo();                  //O(1), get
        Nodo<Element>* getProx();           //O(1), get
        void setInfo(Element v);            //O(1), set 
        void setProx(Nodo<Element>* p);     //O(1), set

};

template <class Element>
Nodo<Element>::Nodo(Element v,Nodo<Element>* p){
    info = v;
    prox = p;
}

template <class Element>
Element Nodo<Element>::getInfo(){
    return info;
}

template <class Element>
Nodo<Element>* Nodo<Element>::getProx(){
    return prox;
}

template <class Element>
void Nodo<Element>::setInfo(Element v){
    info = v;
}

template <class Element>
void Nodo<Element>::setProx(Nodo<Element>* p){
    prox = p;
}

#endif