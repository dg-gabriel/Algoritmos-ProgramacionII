#include <iostream>
#include <string>
#include <sstream>
#include "cola.hpp"

using namespace std;

typedef struct{
    int bitcoin;
    string nombre;
} Cliente;

void leerEntrada(Cola<Cliente> &clientes){
    string linea;
    while(getline(cin,linea)){
        if(linea == "FIN"){
            break;
        }
        int len = linea.length();
        for(int i=0;i<len;i++){
            char c = linea[i];
            if(c == ','){
                linea[i] = ' ';
            }
        }
        stringstream ss(linea);
        string name;
        int bit;
        while(ss >> name >> bit){
            Cliente client;
            client.nombre = name;
            client.bitcoin = bit;
            clientes.encolar(client);
        }
    }
}

void atenderClientes(Cola<Cliente> &clientes,Cola<string> &atendidos){
    Cliente actual;
    while(!clientes.esVacia()){
        if(clientes.getLength() == 1){
            actual = clientes.getHead();
            clientes.desencolar();
            atendidos.encolar(actual.nombre);
        }
        else{
            actual = clientes.getHead();
            clientes.desencolar();
            if(actual.bitcoin >= clientes.getHead().bitcoin){
                atendidos.encolar(actual.nombre);
            }
            else{
                clientes.encolar(actual);
                atendidos.encolar(clientes.getHead().nombre);
                clientes.desencolar();
            }
        }
    }
}

int main(){
    Cola<Cliente> fila;
    Cola<string> atendidos;
    int nCasos;

    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        leerEntrada(fila);
        atenderClientes(fila,atendidos);
        
        while(!atendidos.esVacia()){
            cout << atendidos.getHead() << " " << "<-";
            atendidos.desencolar();                         //falto desencolar
        }
        cout << endl;
    }
    
}