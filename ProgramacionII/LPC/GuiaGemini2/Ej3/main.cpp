#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "cola.hpp"

using namespace std;

typedef struct{
    string tag;
    int PID,MB;
} Process;

void leerEntrada(Lista<Process> &procesos){
    int nroProcesos;
    cin >> nroProcesos;
    cin.ignore();
    for(int i=0;i<nroProcesos;i++){
        string line;
        getline(cin,line);
        for(int j=0;j<line.length();j++){
            char c = line[j];
            if(c == ','){
                line[j] = ' ';
            }
        }
        stringstream ss(line);
        Process nuevoP;
        while(ss >> nuevoP.PID >> nuevoP.tag >> nuevoP.MB){
            cout << nuevoP.PID << " " << nuevoP.tag << " " << nuevoP.MB << endl;
            procesos.insertar(nuevoP,procesos.getLength()+1);
        }
    }
}

float promedioMemoria(Lista<Process> procesos){
    float promedio = 0;
    int longitud = procesos.getLength();
    while(!procesos.esVacia()){
        promedio += procesos.consultarPos(1).MB;
        procesos.eliminar(1);
    }
    promedio = promedio/longitud;
    return promedio;
}

void limpiezaDeMemoria(Lista<Process> &procesos,Cola<string> &muertos){
    for(int i=1;i<=procesos.getLength();i++){
        float prom = promedioMemoria(procesos);
        Process actual = procesos.consultarPos(i);
        if(actual.MB > prom){
            procesos.eliminar(i);
            muertos.encolar(actual.tag);
            i--;
        }
    }
}

void imprimirSalida(Lista<Process> &procesos,Cola<string> &muertos){
    if(procesos.esVacia()){
        cout << "Ninguno";
    }
    else{
        cout << "Sobrevivientes: ";
        while(!procesos.esVacia()){
            cout << "[" << procesos.consultarPos(1).PID << "]";
            if(procesos.getLength() > 1){
                cout << " ";
            }
            procesos.eliminar(1);
        }
    }
    cout << endl;
    if(muertos.esVacia()){
        cout << "Ninguno";
    }
    else{
        cout << "Purgados: ";
        while(!muertos.esVacia()){
            cout << "[" << muertos.getHead() << "]";
            if(muertos.getLength() > 1){
                cout << " ";
            }
            muertos.desencolar();
        }
    }
    
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        Lista<Process> procesos;
        Cola<string> muertos;
        leerEntrada(procesos);
        limpiezaDeMemoria(procesos,muertos);
        imprimirSalida(procesos,muertos);
    }
}