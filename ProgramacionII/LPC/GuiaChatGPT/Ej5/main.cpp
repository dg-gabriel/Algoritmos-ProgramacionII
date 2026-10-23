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

void jugarRonda(Lista<string> &players,int k,int &sentido,int &index){
    int L = players.getLength();
    if(sentido == 1){
        index = (index - 1 + (k - 1)) % L + 1;
    }
    else{
        index = ((index - 1 - (k-1)) % L + L) % L + 1;
        // cuando el sentido es contrario el siguiente debe asignarsele al izquierdo (-1) no al derecho
    }
    string eliminado = players.consultarPos(index);
    players.eliminar(index);
    if(eliminado.length() % 2 == 0){
        sentido = sentido * (-1);
    }
}

int main(){
    int nCasos;
    cin >> nCasos;
    cin.ignore();

    for(int i=1;i<=nCasos;i++){
        Lista<string> guardianes;
        int k;
        int sentido = 1,index = 1;
        leerEntrada(guardianes,k);
        while(guardianes.getLength() > 1){
            jugarRonda(guardianes,k,sentido,index);
        }
        cout << guardianes.consultarPos(1) << endl;
    }
}