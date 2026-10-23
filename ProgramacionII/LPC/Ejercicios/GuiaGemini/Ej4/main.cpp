#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "pila.hpp"
#include "cola.hpp"

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

void jugarRonda(Lista<string> &players,Cola<string> &warriors,Pila<string> &sages,int &index,int k){
    index = (index - 1 + (k - 1)) % players.getLength() + 1;
    string eliminado = players.consultarPos(index);
    if(eliminado.length() % 2 == 0){
        sages.apilar(eliminado);
    }
    if(eliminado.length() % 2 != 0 && eliminado.length() > 4){
        warriors.encolar(eliminado);
    }
    else{
        // get rekt
    }
    players.eliminar(index);
}

void imprimirRes(string winner,Cola<string> &warriors,Pila<string> &sages){
    cout << winner << endl;
    if(sages.esVacia()){
        cout << "VACIO";
    }
    while(!sages.esVacia()){
        cout << sages.getTop();
        if(sages.getLength() > 1){
            cout << " ";
        }
        sages.desapilar();
    }
    cout << endl;
    if(warriors.esVacia()){
        cout << "VACIO";
    }
    while(!warriors.esVacia()){
        cout << warriors.getHead();
        if(warriors.getLength() > 1){
            cout << " ";
        }
        warriors.desencolar();
    }
    cout << endl;
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        Lista<string> players;
        Cola<string> warriors;
        Pila<string> sages;
        int k,index = 1;
        leerEntrada(players,k);
        while(players.getLength() > 1){
            jugarRonda(players,warriors,sages,index,k);
        }
        imprimirRes(players.consultarPos(1),warriors,sages);

    }
}