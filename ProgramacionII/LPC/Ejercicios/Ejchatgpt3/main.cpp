#include <iostream>
#include <sstream>
#include <string>
#include "pila.hpp"
#include "cola.hpp"

using namespace std;

void ejecutarREV(Pila<string> &keyboard){
    Cola<string> aux;
    if(keyboard.getLength() <= 1){
        return;
    }
    while(!keyboard.esVacia()){
        aux.encolar(keyboard.getTop());
        keyboard.desapilar();
    }
    while(!aux.esVacia()){
        keyboard.apilar(aux.getHead());
        aux.desencolar();
    }
}

void ejecutarCOPY(Pila<string> &keyboard){
    if(keyboard.esVacia()){
        return;
    }
    string copia = keyboard.getTop();
    keyboard.apilar(copia);
}

void ejecutarDEL(Pila<string> &keyboard){
    if(keyboard.esVacia()){
        return;
    }
    keyboard.desapilar();
}

void leerEntrada(Pila<string> &keyboard){
    string line;
    while(getline(cin,line)){
        if(line == "FIN"){
            break;
        }
        stringstream ss(line);
        string word;
        while(ss >> word){
            if(word == "<REV>"){
                ejecutarREV(keyboard);
            }
            else if(word == "<DEL>"){
                ejecutarDEL(keyboard);
            }
            else if(word == "<COPY>"){
                ejecutarCOPY(keyboard);
            }
            else{
                keyboard.apilar(word);
            }
        }
    }
}

void escribirSalida(Pila<string> &keyboard){    // falto pasarla por valor
    Cola<string> aux;
    while(!keyboard.esVacia()){
        aux.encolar(keyboard.getTop());
        keyboard.desapilar();
    }
    while(!aux.esVacia()){
        keyboard.apilar(aux.getHead());
        aux.desencolar();
    }
    while(!keyboard.esVacia()){
        cout << keyboard.getTop() << " ";
        keyboard.desapilar();
    }
    cout << endl;
}

int main(){
                    // debiste declarar la pila dentro del ciclo
    int nCasos;

    cin >> nCasos;
    for(int i=1;i<=nCasos;i++){
        Pila<string> teclado;
        leerEntrada(teclado);
        escribirSalida(teclado);
    }
}