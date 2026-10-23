#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "pila.hpp"

using namespace std;

void leerEntrada(Lista<string> &navegacion,Pila<string> &historial){
    string line;
    getline(cin,line);
    //cout << "LINE:" << line << endl;
    for(int i=0;i<line.length();i++){
        char c = line[i];
        if(c == '*' || c == '&' || c == '{' || c == '}' || c == ','){
            line[i] = ' ';
        }
    }
    //cout << "LINE POST PARSE:" << line << endl;
    stringstream ss(line);
    string command,text;
    while(ss >> command){
        if(command == "ADD"){
            ss >> text;
            navegacion.insertar(text,navegacion.getLength()+1);
            if(!historial.esVacia()){
                historial.vaciar();
            }
        }
        if(command == "UNDO"){
            // falto verificar si habia algo en las estructuras
            historial.apilar(navegacion.consultarPos(navegacion.getLength()));
            navegacion.eliminar(navegacion.getLength());
        }
        if(command == "REDO"){
            if(!historial.esVacia()){
                navegacion.insertar(historial.getTop(),navegacion.getLength()+1);
                historial.desapilar();
            }
        }
    }
}

void imprimirSalida(Lista<string> &navegacion){
    if(navegacion.esVacia()){
        cout << "Log Vacio" << endl;
    }
    else{
        while(!navegacion.esVacia()){
            cout << navegacion.consultarPos(1);
            if(navegacion.getLength() > 1){
                cout << " -> ";
            }
            navegacion.eliminar(1);
        }
    }
}

int main(){
    Lista<string> navegador;
    Pila<string> historial;
    leerEntrada(navegador,historial);
    imprimirSalida(navegador);
}