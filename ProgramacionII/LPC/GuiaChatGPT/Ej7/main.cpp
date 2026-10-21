#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

typedef struct{
    string name;
    int nivel,antig;
} Guardian;

void leerEntrada(Lista<Guardian> &players,int &k){
    int nroGuard;
    cin >> k;
    cin >> nroGuard;
    cin.ignore();
    // cin.ignore no es necesario si se usa puro cin

    for(int i=0;i<nroGuard;i++){
        Guardian actual;
        cin >> actual.name >> actual.nivel >> actual.antig;
        players.insertar(actual,players.getLength()+1);
    }
}

void jugarRonda(Lista<Guardian> &players,int &k,int &index){
    index = (index - 1 + (k - 1)) % players.getLength() + 1;
    Guardian eliminado = players.consultarPos(index);
    players.eliminar(index);
    if(eliminado.nivel >= 50){
        k++;
    }
    else{
        k--;
        if(k < 2){
            k = 2;
        }
    }
    if(eliminado.antig > 20){
        index = ((index - 2) + players.getLength()) % players.getLength() + 1; 
        // recalcular el indice descuadra todo el orden de juego solo hay que restar 1 y proteger con condicional
    }
}

int main(){
    int nCasos;

    cin >> nCasos;
    
    for(int i=0;i<nCasos;i++){
        Lista<Guardian> guardianes;
        int k,index = 1;
        leerEntrada(guardianes,k);
        while(guardianes.getLength() > 1){
            jugarRonda(guardianes,k,index);
        }
        cout << guardianes.consultarPos(1).name << endl;
    }
}