#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

typedef struct{
    string name;
    int idOriginal;
} Invitado;

void leerEntrada(Lista<Invitado> *invitados,int *k,int *q,int *p){

    string entrada,junk,nombre;
    cin >> *k >> *p >> *q;
    cin.ignore();
    getline(cin,entrada);
    stringstream ss(entrada);

    while(getline(ss,junk,'"')){
        if(getline(ss,nombre,'"')){
            Invitado inv;
            inv.name = nombre;
            inv.idOriginal = invitados->getLength()+1;
            invitados->insertar(inv,inv.idOriginal);
        }
    }
}

void realizarVuelta(Lista<Invitado> *invitados,int &index,int pasos,int &sentido,int *idEliminado){

    int L = invitados->getLength();

    if(sentido == 1){
        index = (index - 1 + (pasos - 1)) % L + 1;
    }
    else{
        index = ((index - 1 - (pasos-1)) % L + L) % L + 1;  
        //i could've NEVER figured this shit out on my own bruh
    }

    *idEliminado = invitados->consultarPos(index).idOriginal;
    invitados->eliminar(index);

    sentido = sentido * (-1);

    if(sentido == 1){
        if(index > invitados->getLength()) {
            index = 1;
        }
    }
    else{
        index = index -1;
        if(index == 0) {
            index = invitados->getLength();
        }
    }
}

int main(){
    int k,q,p,n,pasos;
    
    cin >> n;
    cin.ignore();

    for(int i=0;i<n;i++){
        Lista<Invitado> invitados;
        int sentido = 1;
        int index = 1;
        leerEntrada(&invitados,&k,&q,&p);
        pasos = k;
        while(invitados.getLength() > 1){
            int idElim;
            realizarVuelta(&invitados,index,pasos,sentido,&idElim);
            if(idElim % 2 == 0){
                pasos = p;
            }
            else{
                pasos = q;
            }
        }
        cout << invitados.consultarPos(1).name << endl;
    }
    return 0;
}