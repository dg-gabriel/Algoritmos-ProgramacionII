#ifndef COLA_HPP
#define COLA_HPP

#include <iostream>
#include "nodo.hpp"

template <class Element>
class Cola{
    private:
        Nodo<Element>* head;
        Nodo<Element>* tail;
        int length;

    public:
        Cola();                                                 //O(1), constructor
        Cola(const Cola<Element>& target);                      //O(n), constructor copia
        Cola<Element>& operator=(const Cola<Element>& target);  //O(n), sobrecarga del operador de asignacion
        ~Cola();                                                //O(n), destructor
        Element getHead();                                      //O(1), retorna el elemento al inicio de la cola
        Element getTail();                                      //O(1), retorna el elemento al final de la cola
        int getLength();                                        //O(1), retorna el tamano de la cola
        void encolar(Element elem);                             //O(1), añade un elemento al final
        void desencolar();                                      //O(1), elimina al primero de la cola
        bool esVacia();                                         //O(1), true si es vacia, false si no
        void vaciar();                                          //O(n), elimina todos los elementos de la cola
        Cola<Element> copia();                                  //O(n), crea una copia de la cola
};

template <class Element>
Cola<Element>::Cola(){
    head = NULL;
    tail = NULL;
    length = 0;
}

template <class Element>
Cola<Element>::Cola(const Cola<Element>& target){

    head = NULL;
    tail = NULL;
    length = 0;

    if(target.length == 0){
        return;
    }

    Nodo<Element>* p = target.head;

    while(p != NULL){
        Element dato = p->getInfo();
        encolar(dato);
        p = p->getProx();
    }

}

template <class Element>
Cola<Element>& Cola<Element>::operator=(const Cola<Element>& target){

    if(this == &target){
        return *this;
    }

    vaciar();

    Nodo<Element>* p = target.head;

    while(p != NULL){
        encolar(p->getInfo());
        p = p->getProx();
    }

    return *this;
}

template <class Element>
Cola<Element>::~Cola(){
    vaciar();
}

template <class Element>
Element Cola<Element>::getHead(){
    if(esVacia()) return Element();
    return head->getInfo();
}

template <class Element>
Element Cola<Element>::getTail(){
    if(esVacia()) return Element();
    return tail->getInfo();
}

template <class Element>
int Cola<Element>::getLength(){
    return length;
}

template <class Element>
void Cola<Element>::encolar(Element elem){

    Nodo<Element>* p = new Nodo<Element>(elem,NULL);

    if(esVacia()){
        head = p;
        tail = p;
    }
    else{
        tail->setProx(p);
        tail = p;
    }

    length++;
}

template <class Element>
void Cola<Element>::desencolar(){

    if(esVacia()){
        // no hay nada que desencolar
        return;
    }

    Nodo<Element>* aux = head;
    head = head->getProx();
    delete(aux);
    length--;

    if(head == NULL){
        tail = NULL;
    }
}

template <class Element>
bool Cola<Element>::esVacia(){
    return head == NULL;
}

template <class Element>
void Cola<Element>::vaciar(){
    while(!esVacia()){
        desencolar();
    }
}

template <class Element>
Cola<Element> Cola<Element>::copia(){
    return Cola<Element>(*this);
}

#endif