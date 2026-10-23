#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

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

void jugarRonda(Lista<string> &players,Lista<string> &eliminados,int &index,int k){
    index = (index - 1 + (k - 1)) % players.getLength() + 1;
    eliminados.insertar(players.consultarPos(index),eliminados.getLength()+1);
    players.eliminar(index); 
    // Lo idoneo hubiera sido usar una cola para evitar el O(n)
}


int main(){
    int nCasos;
    cin >> nCasos;
    cin.ignore();

    for(int i=1;i<=nCasos;i++){
        int index = 1,k;
        Lista<string> players,eliminados;
        leerEntrada(players,k);
        while(players.getLength() > 1){
            jugarRonda(players,eliminados,index,k);
        }
        cout << players.consultarPos(1) << endl;
        int L = eliminados.getLength();
        for(int j=1;j<=L;j++){
            cout << eliminados.consultarPos(1) << " ";
            eliminados.eliminar(1);
        }
        cout << endl;
    }
}