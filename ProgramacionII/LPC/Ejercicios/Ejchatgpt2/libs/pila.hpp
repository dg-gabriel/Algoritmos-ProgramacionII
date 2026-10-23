#ifndef PILA_HPP
#define PILA_HPP

#include <iostream>
#include "nodo.hpp"

template <class Element>
class Pila{
    private:
        Nodo<Element>* top;
        Nodo<Element>* bottom;
        int length;

    public:
        Pila();                                                 //O(1), constructor 
        Pila(const Pila<Element>& target);                      //O(n), constructor copia
        Pila<Element>& operator=(const Pila<Element>& target);  //O(n), sobrecarga del operador de asignacion
        ~Pila();                                                //O(n), destructor
        Element getTop();                                       //O(1), retorna el elem al tope
        Element getBottom();                                    //O(1), retorna el elem al fondo
        int getLength();                                        //O(1), retorna tamano de la pila
        void apilar(Element elem);                              //O(1), anade un nuevo tope
        void desapilar();                                       //O(1), quita el tope sin retornar
        Pila<Element> copia();                                  //O(n), crea una copia de la pila
        bool esVacia();                                         //O(1), true si es vacia, false si no
        void vaciar();                                          //O(n), elimina todos los elementos
};

template <class Element>
Pila<Element>::Pila(){
    top = NULL;
    bottom = NULL;
    length = 0;
}

template <class Element>
Pila<Element>::Pila(const Pila<Element>& target){

    top = NULL;
    bottom = NULL;
    length = 0;

    *this = target;
}

template <class Element>
Pila<Element>& Pila<Element>::operator=(const Pila<Element>& target){

    if(this == &target){
        return *this;
    }

    vaciar();

    Nodo<Element>* p = target.top;

    while(p != NULL){
        Nodo<Element>* nuevo = new Nodo<Element>(p->getInfo(),NULL);

        if(length == 0){
            top = nuevo;
            bottom = nuevo;
        }
        else{
            bottom->setProx(nuevo);
            bottom = nuevo;
        }

        length++;
        p = p->getProx();
    }

    return *this;
}

template <class Element>
Pila<Element>::~Pila(){
    vaciar();
}

template <class Element>
Element Pila<Element>::getTop(){
    if(esVacia()) return Element();
    return top->getInfo();
}

template <class Element>
Element Pila<Element>::getBottom(){
    if(esVacia()) return Element();
    return bottom->getInfo();
}

template <class Element>
int Pila<Element>::getLength(){
    return length;
}

template <class Element>
void Pila<Element>::apilar(Element elem){

    Nodo<Element>* p = new Nodo<Element>(elem,NULL);
    if(esVacia()){
        top = p;
        bottom = p;
    }
    else{
        p->setProx(top);
        top = p;
    }
    length++;
}

template <class Element>
void Pila<Element>::desapilar(){

    if(esVacia()){
        // no hay nada que desapilar
        return;
    }

    Nodo<Element>* aux = top;
    top = top->getProx();
    delete(aux);
    length--;

    if(top == NULL){
        bottom = NULL;
    }
}

template <class Element>
Pila<Element> Pila<Element>::copia(){
    return Pila<Element>(*this);
}

template <class Element>
bool Pila<Element>::esVacia(){
    return top == NULL;
}

template <class Element>
void Pila<Element>::vaciar(){
    while(!esVacia()){
        desapilar();
    }
}

#endif