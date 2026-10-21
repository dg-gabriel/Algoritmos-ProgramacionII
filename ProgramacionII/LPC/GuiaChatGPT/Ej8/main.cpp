#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "cola.hpp"
#include "pila.hpp"

using namespace std;

void leerEntrada(Lista<string> &players,int &k){
    string line,name;
    cin >> k;
    cin.ignore();
    getline(cin,line);
    stringstream ss(line);
    while(ss >> name){
        players.insertar(name,players.getLength()+1);
    }
}

void jugarRonda(Lista<string> &players,Cola<string> &espera,Pila<string> &registro,int &index,int k){
    index = (index - 1 + (k - 1)) % players.getLength() + 1;
    string eliminado = players.consultarPos(index);
    players.eliminar(index);
    //debes encolar antes de consultar si ya hay 5 en la sala de espera de lo contrario se altera el flujo
    if(espera.getLength() == 5){
        while(!espera.esVacia()){
            registro.apilar(espera.getHead());
            espera.desencolar();
        }
    }
    espera.encolar(eliminado);
}

int main(){
    int nCasos;
    cin >> nCasos;

    for(int i=0;i<nCasos;i++){
        int k,index = 1;
        Lista<string> consejeros;
        Cola<string> salaEspera;
        Pila<string> registro;
        leerEntrada(consejeros,k);
        while(consejeros.getLength() > 1){
            jugarRonda(consejeros,salaEspera,registro,index,k);
        }
        cout << consejeros.consultarPos(1) << endl;
        if(salaEspera.esVacia()){
            cout << "VACIA";
        }
        else{
            while(!salaEspera.esVacia()){
                cout << salaEspera.getHead() << " ";
                salaEspera.desencolar();
            }
        }
        cout << endl;
        if(registro.esVacia()){
            cout << "VACIA";
        }
        else{
            while(!registro.esVacia()){
                cout << registro.getTop() << " ";
                registro.desapilar();
            }
        }
        cout << endl;
    }
}