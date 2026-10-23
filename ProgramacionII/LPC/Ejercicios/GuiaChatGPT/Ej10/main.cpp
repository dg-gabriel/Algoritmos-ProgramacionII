#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "pila.hpp"
#include "cola.hpp"

using namespace std;

typedef struct{
    string name,rank;
    int age;
} Guardian;

void leerEntrada(Lista<Guardian> &players,int &k){
    int nGuard;
    string line;
    cin >> k;
    cin >> nGuard;
    cin.ignore();

    for(int i=0;i<nGuard;i++){
        getline(cin,line);
        for(int j=0;j<line.length();j++){
            char c = line[j];
            if(c == ','){
                line[j] = ' ';
            }
        }
        stringstream ss(line);
        string name,rank;
        int age;
        while(ss >> name >> rank >> age){
            Guardian newGuard;
            newGuard.name = name;
            newGuard.rank = rank;
            newGuard.age = age;
            players.insertar(newGuard,players.getLength()+1);
        }
    }
}

int cambioK(string rango,int k){
    if(rango == "Maestro"){
        return k + 1;
    }
    if(rango == "Aprendiz"){
        k--;
        if(k < 2){
            k = 2;
        }
        return k;
    }
    return k;
}

int cambioSentido(string nombre,int sentido){
    if(nombre.length() % 2 == 0){
        sentido = sentido * (-1);
    }
    return sentido;
}

void jugarRonda(Lista<Guardian> &players,Cola<string> &sala,Pila<string> &registro,int &k,int &index,int &sentido){
    if(sentido == 1){
        index = (index - 1 + (k - 1)) % players.getLength() + 1;
    }
    else{
        int L = players.getLength();
        index = ((index - k) % L + L) % L + 1;
        //falto restarle UNO
    }
    Guardian eliminado = players.consultarPos(index);
    players.eliminar(index);
    k = cambioK(eliminado.rank,k);
    sentido = cambioSentido(eliminado.name,sentido);
    sala.encolar(eliminado.name);
    if(sala.getLength() == 5){
        while(!sala.esVacia()){
            registro.apilar(sala.getHead());
            sala.desencolar();
        }
    }
}

int main(){
    int nCasos;
    cin >> nCasos;

    for(int i=0;i<nCasos;i++){
        int k,index = 1,sentido = 1;
        Lista<Guardian> guardianes;
        Cola<string> salaEspera;
        Pila<string> registro;
        leerEntrada(guardianes,k);
        while(guardianes.getLength() > 1){
            jugarRonda(guardianes,salaEspera,registro,k,index,sentido);
        }
        cout << guardianes.consultarPos(1).name << endl;
        if(salaEspera.esVacia()){
            cout << "VACIO";
        }
        else{
            while(!salaEspera.esVacia()){
                cout << salaEspera.getHead();
                salaEspera.desencolar();
                if(!salaEspera.esVacia()){
                    cout << " ";
                }
            }
        }
        cout << endl;
        if(registro.esVacia()){
            cout << "VACIO";
        }
        else{
            while(!registro.esVacia()){
                cout << registro.getTop();
                registro.desapilar();
                if(!registro.esVacia()){
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

