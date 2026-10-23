#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "pila.hpp"

using namespace std;

void leerEntrada(Lista<string> &players,Pila<int> &cristales){
    string line,name;
    int num;
    getline(cin,line);
    stringstream ss1(line);
    while(ss1 >> name){
        //cout << "DEBUG: name: " << name << endl;
        players.insertar(name,players.getLength()+1);
    }
    getline(cin,line);
    stringstream ss2(line);
    while(ss2 >> num){
        //cout << "DEBUG: cristalnum: " << num << endl;
        cristales.apilar(num);
    }
    
}

void jugarRonda(Lista<string> &players,Pila<int> &cristales,int &index){
    int k = cristales.getTop();
    int L = players.getLength();
    cristales.desapilar();
    //cout << "CRISTAL ACTUAL: " << k << endl;
    if(k >= 1){
        // calcular posicion en sentido horario
        index = (index - 1 + (k - 1)) % L + 1;
    }
    else{
        k = k * (-1);
        // calcular posicion en sentido antihorario
        index = ((index - k) % L + L) % L + 1;
        index--;
        if(index == 0){
            index = L;
        }
        
    }
    //cout << "ELIMINADO: " << players.consultarPos(index) << endl;
    players.eliminar(index);

}

int main(){
    int nCasos;
    cin >> nCasos;
    cin.ignore();
    for(int i=0;i<nCasos;i++){
        Lista<string> players;
        Pila<int> cristals;
        int index = 1;
        leerEntrada(players,cristals);
        while(players.getLength() > 1){
            jugarRonda(players,cristals,index);
        }
        cout << players.consultarPos(1) << endl;
    }
}