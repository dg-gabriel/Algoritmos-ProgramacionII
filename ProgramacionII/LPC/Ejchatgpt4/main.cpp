#include <iostream>
#include <string>
#include <sstream>
#include "cola.hpp"
#include "pila.hpp"

using namespace std;

typedef struct{
    string nombre;
    int nivel;
} Mago;

void leerEntrada(Cola<Mago> &magos,Pila<int> &runas){
    string line,name;
    Mago mage;
    int rune,power;
    getline(cin,line);
    stringstream ss1(line);
    while(ss1 >> rune){
        runas.apilar(rune);
    }

    getline(cin,line);
    for(int i=0;i<line.length();i++){
        char c = line[i];
        if(c == '-'){
            line[i] = ' ';
        }
    }
    stringstream ss2(line);
    while(ss2 >> name >> power){
        mage.nombre = name;
        mage.nivel = power;
        magos.encolar(mage);
    }
}

void ritualMagico(Cola<Mago> &magos,Pila<int> &runas){
    while(!magos.esVacia() && !runas.esVacia()){
        Mago actual = magos.getHead();
        magos.desencolar();
        if(actual.nivel >= runas.getTop()){
            actual.nivel += runas.getTop();
            runas.desapilar();
            magos.encolar(actual);
        }
        else{
            // pal lobby
        }
    }
    if(magos.esVacia()){
        cout << "NADIE" << endl;
    }
    else{
        while(!magos.esVacia()){
            cout << magos.getHead().nombre << " ";
            magos.desencolar();
        }
        cout << endl;
    }
}


int main(){
    int nCasos;
    cin >> nCasos;
    cin.ignore();

    for(int i=1;i<=nCasos;i++){
        Cola<Mago> magos;
        Pila<int> runas;
        leerEntrada(magos,runas);
        ritualMagico(magos,runas);
    }
    
}