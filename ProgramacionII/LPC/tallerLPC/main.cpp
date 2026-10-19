#include <iostream>
#include <sstream>
#include <string>
#include "lista.hpp"
#include "pila.hpp"
#include "cola.hpp"

using namespace std;

void procesar(Cola<string> &ciud,Pila<string> &arch,int k){
    // apilar k ciudadanos en el archivo, si k es mayor al tamaño de la cola
    // se apilan los disponibles
    while(k > 0 && !ciud.esVacia()){
        arch.apilar(ciud.getHead());
        ciud.desencolar();
        k--;
    }
}

void atender(Pila<string> &arch,Lista<string> &salida,int k){
    // misma logica: insertar k ciudadanos en la salida, si hay menos de k ciudadanos
    // se insertan los disponibles
    while(k > 0 && !arch.esVacia()){
        salida.insertar(arch.getTop(),salida.getLength()+1);
        arch.desapilar();
        k--;
    }
}

void leerEntrada(Cola<string> &ciud,Lista<string> &salida){
    Pila<string> archivo;
    // se instancia la pila de archivos dentro de la funcion
    // porque no interesa guardar los datos una vez termine

    string comando;
    while(cin >> comando){ // mientras se lea un comando hay ciudadanos por procesar
        int k;
        if(comando == "LLEGA"){ // encolar el nuevo nombre
            string nombre;
            cin >> nombre;
            ciud.encolar(nombre);
        }
        else if(comando == "PROCESAR"){ // desencolar k ciudadnos y llevarlos al archivo
            cin >> k;
            procesar(ciud,archivo,k);
            
        }
        else if(comando == "ATENDER"){ // atender k ciudadanos y registrarlos como atendidos
            cin >> k;
            atender(archivo,salida,k);
            
        }
        
    }
}

void imprimirSalida(Lista<string> salida){
    // se pasa copia de la lista para recorrer destructivamente
    // e imprimir
    while(!salida.esVacia()){
        cout << salida.consultarPos(1);
        if(salida.getLength() > 1){
            cout << " ";
        }
        salida.eliminar(1);
    }
    cout << endl;
}

int main(){
    Cola<string> ciudadanos;
    Lista<string> atendidos;
    leerEntrada(ciudadanos,atendidos);
    imprimirSalida(atendidos);
}