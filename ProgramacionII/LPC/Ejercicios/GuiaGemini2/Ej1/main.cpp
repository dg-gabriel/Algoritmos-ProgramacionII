#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"
#include "pila.hpp"
#include "cola.hpp"

using namespace std;

typedef struct{
    string name;
    int energy;
} Particula;

// no era necesario una lista de colas porque el tamano siempre es 2
void leerEntrada(Lista<Cola<Particula > > &players){
    string line;
    getline(cin,line);
    int lineLen = line.length();
    //cout << "LINE:" << line << endl;
    for(int i=0;i<lineLen;i++){
        char c = line[i];
        if(c == '<' || c == '>' || c == ':' || c == '-' || c == '|'){
            line[i] = ' ';
            // al ignorar el | te saltas el separador y alteras el orden
        }
    }
    stringstream ss(line);
    Particula nueva;
    while(ss >> nueva.name >> nueva.energy){
        //cout << "NOMBRE ACT: " << nueva.name << " ENERGIA ACT: " << nueva.energy << endl;
        Cola<Particula> auxCol;
        auxCol.encolar(nueva);
        ss >> nueva.name >> nueva.energy;
        //cout << "NOMBRE ACT: " << nueva.name << " ENERGIA ACT: " << nueva.energy << endl;
        auxCol.encolar(nueva);
        players.insertar(auxCol,players.getLength()+1);
    }
}

void realizarEliminacion(Lista<Cola<Particula > > &particles){
    Pila<Particula> cementerio;
    Cola<Particula> alpha,beta;
    alpha = particles.consultarPos(1);
    beta = particles.consultarPos(2);
    while(!alpha.esVacia() && !beta.esVacia()){
        Particula a,b;
        a = alpha.getHead();
        alpha.desencolar();
        b = beta.getHead();
        beta.desencolar();
        //cout << "A: " << a.name << " A energy: " << a.energy << " B: " << b.name << " B energy: " << b.energy << endl;
        if(a.energy > b.energy){
            //cout << "A: " << a.name << " B eliminado: " << b.name << endl;
            a.energy -= b.energy;
            alpha.encolar(a);
            cementerio.apilar(b);
        }
        else if(a.energy < b.energy){
            //cout << "A eliminado: " << a.name << " B: " << b.name << endl;
            b.energy -= a.energy;
            beta.encolar(b);
            cementerio.apilar(a);
        }
        else{
            cementerio.apilar(a);
            cementerio.apilar(b);
        }

    }
    if(!alpha.esVacia()){
        cout << "Ganador: Alpha" << endl;
        while(!alpha.esVacia()){
            cout << alpha.getHead().name << "(" << alpha.getHead().energy << ")";
            if(alpha.getLength() > 1){
                cout << " ";
            }
            alpha.desencolar();
        }
        cout << endl;
    }
    if(!beta.esVacia()){
        cout << "Ganador: Beta" << endl;
        while(!beta.esVacia()){
            cout << beta.getHead().name << "(" << beta.getHead().energy << ")";
            if(beta.getLength() > 1){
                cout << " ";
            }
            beta.desencolar();
        }
        cout << endl;
    }
    cout << "Tamano del Cementerio: " << cementerio.getLength() << " Ultima particula destruida: " << cementerio.getTop().name << endl;;
}

int main(){
    int nCasos;
    cin >> nCasos;
    cin.ignore();
    for(int i=0;i<nCasos;i++){
        Lista<Cola<Particula > > particles;
        leerEntrada(particles);
        realizarEliminacion(particles);
    }

}
