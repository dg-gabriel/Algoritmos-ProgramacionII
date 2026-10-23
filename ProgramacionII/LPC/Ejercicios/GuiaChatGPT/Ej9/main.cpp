#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

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

int calcularIndex(int edadElim,int index,int L){
    if(edadElim >= 60){
        index--;
        if(index == 1){
            //PORQUE 1 TIENE QUE SER 0 IMBECIL
            index = L;
        }
    }
    return index;
}

void jugarRonda(Lista<Guardian> &players,int &k,int &index){
    index = (index - 1 + (k - 1)) % players.getLength() + 1;
    Guardian eliminado = players.consultarPos(index);
    players.eliminar(index);
    cambioK(eliminado.rank,k);
    // llamaste a cambioK como procedimiento en vez de funcion
    index = calcularIndex(eliminado.age,index,players.getLength());
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        Lista<Guardian> guardians;
        int k,index = 1;
        leerEntrada(guardians,k);
        while(guardians.getLength() > 1){
            jugarRonda(guardians,k,index);
        }
        cout << guardians.consultarPos(1).name << endl;
    }
    
    
}