#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "pila.hpp"
#include "cola.hpp"

using namespace std;

typedef struct{
    string name,faccion;
    int poder,fichas;
} Emisario;

void leerEntrada(Lista<Emisario> &players,int &k){
    int n;
    string line,name;
    cin >> k;
    cin >> n;
    cin.ignore(1000,'\n');
    for(int i=0;i<n;i++){
        //cout << "Valor de i: " << i << endl,
        getline(cin,line);
        //cout << "LINEA: " << line << endl;
        for(int j=0;j<line.length();j++){
            char c = line[j];
            if(c == ','){
                line[j] = ' ';
            }
        }
        //cout << "LINEA POST PARSE: " << line << endl;
        stringstream ss(line);
        Emisario actual;

        ss >> actual.name >> actual.faccion >> actual.poder >> actual.fichas;
        //cout << actual.name << " " << actual.faccion << " " << actual.poder << " " << actual.fichas << endl;
        players.insertar(actual,players.getLength()+1);
    }
}

void jugarRonda(Lista<Emisario> &players,Cola<Emisario> &purgatorio,Pila<string> &ascendidos,int &sentido,int &index,int &k){
    // Pasaste k por valor en vez de referencia, no se conservan los cambios
    // Tambien pasaste Ascendidos por valor en vez de referencia tonto
    int L = players.getLength();
    if(sentido == 1){
        index = (index - 1 + k) % L; // falto el "+ 1"
    }
    else{
        index = ((index - 1 - k) % L + L) % L + 1;
    }
    Emisario eliminado = players.consultarPos(index);
    players.eliminar(index);
    if(eliminado.faccion == "Ignis"){
        sentido *= (-1);
    }
    if(eliminado.faccion == "Aqua"){
        k += eliminado.fichas;
    }
    if(eliminado.faccion == "Terra"){
        k = k/2;
        if(k < 2){
            k = 2;
        }
    }
    purgatorio.encolar(eliminado);
    if(purgatorio.getLength() == 4){
        while(!purgatorio.esVacia()){
            if(purgatorio.getHead().poder > 50){
                ascendidos.apilar(purgatorio.getHead().name);
            }
            purgatorio.desencolar();
        }
    }

}

void imprimirSalida(string winner,Cola<Emisario> &purg,Pila<string> &asc){
    cout << "Canciller: " << winner << endl;
    cout << "Ascendidos: ";
    if(asc.esVacia()){
        cout << "VACIO";
    }
    while(!asc.esVacia()){
        cout << asc.getTop();
        if(asc.getLength() > 1){
            cout << " ";
        }
        asc.desapilar();
    }
    cout << endl;
    cout << "Purgatorio: ";
    if(purg.esVacia()){
        cout << "VACIO";
    }
    while(!purg.esVacia()){
        cout << purg.getHead().name;
        if(purg.getLength() > 1){
            cout << " ";
        }
        purg.desencolar();
    }
    cout << endl;
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        Lista<Emisario> players;
        Cola<Emisario> purgatorio;
        Pila<string> ascendidos;
        int k,sentido = 1,index = 1;
        leerEntrada(players,k);
        while(players.getLength() > 1){
            jugarRonda(players,purgatorio,ascendidos,sentido,index,k);
        }
        imprimirSalida(players.consultarPos(1).name,purgatorio,ascendidos);
    }
}