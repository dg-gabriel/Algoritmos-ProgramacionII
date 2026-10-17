#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
#include "nodo.hpp"

template <class Element>
class Lista{
    private:
        Nodo<Element>* first;
        Nodo<Element>* last;
        int length;

    public:
        Lista();                                                    //O(1), constructor
        Lista(const Lista<Element>& target);                        //O(n), constructor copia
        ~Lista();                                                   //O(n), destructor
        Lista<Element>& operator=(const Lista<Element>& target);    //O(n), sobrecarga del operador de asignacion
        int getLength();                                            //O(1), getter
        void insertar(Element elem,int pos);                        //O(1) si pos = 1 o pos = length,O(n) resto de casos, insertar elem en la posicion pos
        void eliminar(int pos);                                     //O(1) si pos = 1,O(n) resto de casos, eliminar el elem en la posicion pos
        void vaciar();                                              //O(n), vaciar la lista
        bool existeElemento(Element elem);                          //O(n), recorre hasta encontrar elem, true si lo encuentra, false si no
        Lista<Element> concatenar(Lista<Element> L2);               //O(n+m), une a L1 con L2
        Element consultarPos(int pos);                              //O(1) si pos = 1 o pos = length,O(n) resto de casos, devuelve lo que hay en la posicion pos
        void modificar(int pos,Element elem);                       // ^^^, cambia el elemento en la posicion pos por elem
        void invertir();                                            //O(n), pone la lista al reves
        int buscarElemento(Element elem);                           //O(n), devuelve la posicion de elem si lo encuentra
        bool esVacia();                                             //O(1), devuelve true si es vacia, false si no
        Lista<Element> copia();                                     //O(n), crea y retorna una copia de la lista
        void eliminarElemento(Element elem);                        //O(1) si pos = 1,O(n) resto de casos, elimina la primera instancia que encuentre de elemento elem
};

template <class Element>
Lista<Element>::Lista(){
    first = NULL;
    last = NULL;
    length = 0;
}

template <class Element>
Lista<Element>::Lista(const Lista<Element>& target){

    first = NULL;
    last = NULL;
    length = 0;

    if(target.length == 0){
        return;
    }

    Nodo<Element>* p = target.first;;

    while(p != NULL){
        Element carga = p->getInfo();

        insertar(carga,length+1);
        p = p->getProx();
    }
}

template <class Element>
Lista<Element>::~Lista(){
    vaciar();
}

template <class Element>
int Lista<Element>::getLength(){
    return length;
}

template <class Element>
Lista<Element>& Lista<Element>::operator=(const Lista<Element>& target){

    if(this == &target){
        return *this;
    }

    vaciar();

    Nodo<Element>* p = target.first;

    while(p != NULL){
        insertar(p->getInfo(), length + 1);
        p = p->getProx();
    }

    return *this;
}

template <class Element>
void Lista<Element>::insertar(Element elem,int pos){

    if(pos < 1 || pos > length+1){
        //error fatal, posicion fuera de limite
        return;
    }

    Nodo<Element>* nuevo;

    if(length == 0){
        nuevo = new Nodo<Element>(elem,0);
        first = nuevo; 
        last = nuevo;
    }
    else if(pos == 1){
            nuevo = new Nodo<Element>(elem,first);
            first = nuevo;
        }
        else if(pos == length + 1){
                nuevo = new Nodo<Element>(elem,NULL);
                last->setProx(nuevo);
                last = nuevo;
            }
            else{
                Nodo<Element>* p;
                p = first;
                for(int i=1;i<pos-1;i++){
                    p = p->getProx();
                }
                nuevo = new Nodo<Element>(elem,p->getProx());
                p->setProx(nuevo);
            }
    length++;
}

template <class Element>
void Lista<Element>::eliminar(int pos){

    if(pos < 1 || pos > length){
        //error fatal, posicion fuera de limite
        return;
    }

    Nodo<Element> *act,*ant;

    if(pos == 1){
        act = first;
        first = first->getProx();
        delete act;
                
        if(first == NULL){
            last = NULL;
        }
        length--;
        return;
    }
    ant = first;
    act = first->getProx();

    for(int i=2;i<pos;i++){
        ant = ant->getProx();   
        act = act->getProx();
    }
    ant->setProx(act->getProx());

    if(act == last){
        last = ant;
    }

    delete act;
    length--;

}

template <class Element>
void Lista<Element>::vaciar(){

    Nodo<Element>* aux;
    while(first != NULL){
        aux = first;
        first = first->getProx();
        delete(aux);
    }
    length = 0;
    last = NULL;
}

template <class Element>
bool Lista<Element>::existeElemento(Element elem){

    Nodo<Element>* p;
    p = first;

    while(p != NULL){
        if(p->getInfo() == elem){
            return true;
        }
        p = p->getProx();
    }
    return false;
}

template <class Element>
Lista<Element> Lista<Element>::concatenar(Lista<Element> L2){

    Lista<Element> L3(*this);
    Nodo<Element>* p = L2.first;

    while(p != NULL){
        L3.insertar(p->getInfo(),L3.getLength()+1);
        p = p->getProx();
    }

    return L3;
}

template <class Element>
Element Lista<Element>::consultarPos(int pos){
    if(pos < 1 || pos > length){
        // posicion fuera de rango
        return Element();
    }
    if(pos == 1){
        return first->getInfo();
    }
    if(pos == length){
        return last->getInfo();
    }

    Nodo<Element>* p = first;
    for(int i=1;i<pos;i++){
        p = p->getProx();
    }
    return p->getInfo();
}

template <class Element>
void Lista<Element>::modificar(int pos,Element elem){
    if(pos < 1 || pos > length){
        // posicion fuera de rango
        return;
    }
    if(pos == 1){
        first->setInfo(elem);
        return;
    }
    if(pos == length){
        last->setInfo(elem);
        return;
    }

    Nodo<Element>* p = first;
    for(int i=1;i<pos;i++){
        p = p->getProx();
    }
    p->setInfo(elem);
}

template <class Element>
void Lista<Element>::invertir(){

    if(length <= 1){
        // no hay nada que invertir
        return;
    }
    
    Nodo<Element> *ant,*act,*sig;
    ant = NULL;
    act = first;
    sig = NULL;

    while(act != NULL){
        sig = act->getProx();
        act->setProx(ant);
        ant = act;
        act = sig;
    }

    last = first;
    first = ant;
}

template <class Element>
int Lista<Element>::buscarElemento(Element elem){

    Nodo<Element>* p = first;
    int pos = 1;
    while(p != NULL){
        if(p->getInfo() == elem){
            return pos;
        }
        p = p->getProx();
        pos++;
    }
    return 0;
}

template <class Element>
bool Lista<Element>::esVacia(){
    return first == NULL;
}

template <class Element>
Lista<Element> Lista<Element>::copia(){
    return Lista<Element>(*this);
}

template <class Element>
void Lista<Element>::eliminarElemento(Element elem){
    int pos = buscarElemento(elem);
    if(pos){
        eliminar(pos);
    }
    return;
}

#endif