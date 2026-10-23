#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "pila.hpp"
#include "cola.hpp"

using namespace std;

typedef struct{
    string name,clase;
    int lvl;
} Candidato;

void leerEntrada(Lista<Candidato> &players,int &k){
    string line;
    cin >> k;
    cin.ignore();
    getline(cin,line);
    //cout << "LINEA:" << line << endl;
    int parseLen = line.length();
    for(int i=0;i<parseLen;i++){
        char c = line[i];
        if(c == '['){
            line.erase(i,1);
            i--;
        }
        if(c == ']'){
            line.erase(i,1);
            i--;
        }
        if(c == ':'){
            line[i] = ' ';
        }
        if(c == '-'){
            line[i] = ' ';
        }
    }
    //cout << "LINEA POST PARSE:" << line << endl;
    stringstream ss(line);
    Candidato nuevo;
    while(ss >> nuevo.name >> nuevo.clase >> nuevo.lvl){
        //cout << nuevo.name << " " << nuevo.clase << " " << nuevo.lvl << endl;
        players.insertar(nuevo,players.getLength()+1);
    }

}

string obtenerMayor(Cola<Candidato> &engranaje){
    int mayorLvl = -1;
    string ganador;
    while(!engranaje.esVacia()){
        if(engranaje.getHead().lvl > mayorLvl){
            ganador = engranaje.getHead().name;
        }
        engranaje.desencolar();
    }
    return ganador;
}

void jugarRonda(Lista<Candidato> &players,Cola<Candidato> &engranaje,Pila<string> &dignos,int &k,int &index,int &sentido){
    int L = players.getLength();
    if(sentido == 1){
        index = (index - 1 + k) % L + 1;
    }
    else{
        index = ((index - 1 - k) % L + L) % L + 1;
    }
    Candidato eliminado = players.consultarPos(index);
    players.eliminar(index);
    if(eliminado.clase == "Guerrero"){
        sentido *= (-1);
    }
    if(eliminado.clase == "Mago"){
        k = (eliminado.lvl % 7) + 2;
    }
    if(eliminado.clase == "Picaro"){
        k += 3;
    }
    engranaje.encolar(eliminado);
    if(engranaje.getLength() == 3){
        dignos.apilar(obtenerMayor(engranaje));
    }
}

void imprimirSalida(string ganador,Cola<Candidato> &engr,Pila<string> &dig){
    cout << "Sobreviviente: [" << ganador << "]" << endl << "Dignos: ";
    if(dig.esVacia()){
        cout << "VACIO";
    }
    while(!dig.esVacia()){
        cout << dig.getTop();
        if(dig.getLength() > 1){
            cout << " ";
        }
        dig.desapilar();
    }
    cout << endl << "Engranaje: ";
    if(engr.esVacia()){
        cout << "VACIO";
    }
    while(!engr.esVacia()){
        cout << engr.getHead().name;
        if(engr.getLength() > 1){
            cout << " ";
        }
        engr.desencolar();
    }
    cout << endl;
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        Lista<Candidato> players;
        Cola<Candidato> engranaje;
        Pila<string> dignos;
        int k,index = 1,sentido = 1;
        leerEntrada(players,k);
        while(players.getLength() > 1){
            jugarRonda(players,engranaje,dignos,k,index,sentido);
        }
        imprimirSalida(players.consultarPos(1).name,engranaje,dignos);
    }
}