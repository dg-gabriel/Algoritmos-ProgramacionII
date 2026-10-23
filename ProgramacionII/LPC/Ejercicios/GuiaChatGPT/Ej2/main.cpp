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

void jugarRonda(Lista<string> &players,int &index,int &k){
    index = (index - 1 + (k - 1)) % players.getLength() + 1;
    string eliminado = players.consultarPos(index);
    if(eliminado.length() % 2 == 0){
        k++;
    }
    else{
        k--;
        if(k < 2){
            k = 2;
        }
    }
    players.eliminar(index);
}

int main(){
    Lista<string> players; // NO VACIASTE LA LISTA Y SIEMPRE SE UTILIZA LA MISMA
    int k,nCasos;
    
    cin >> nCasos;
    cin.ignore();

    for(int i=1;i<=nCasos;i++){
        leerEntrada(players,k);
        int index = 1;
        while(players.getLength() > 1){
            jugarRonda(players,index,k);
        }
        cout << players.consultarPos(1) << endl;
    }
}