#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
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

void jugarRonda(Lista<string> &players,Pila<string> &inscripciones,int &index,int k){
    index = (index - 1 + (k - 1)) % players.getLength() + 1;
    inscripciones.apilar(players.consultarPos(index));
    players.eliminar(index);
}

int main(){

    int nCasos;
    cin >> nCasos;
    cin.ignore();

    for(int i=1;i<=nCasos;i++){
        Lista<string> caballeros;
        Pila<string> inscripciones;
        int index = 1,k;
        leerEntrada(caballeros,k);
        while(caballeros.getLength() > 1){
            jugarRonda(caballeros,inscripciones,index,k);
        }
        cout << caballeros.consultarPos(1) << endl;
        while(!inscripciones.esVacia()){
            cout << inscripciones.getTop() << " ";
            inscripciones.desapilar();
        }
        cout << endl;
    }
}