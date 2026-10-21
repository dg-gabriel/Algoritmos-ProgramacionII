#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

void leerEntrada(Lista<string> &knights,int &k){
    string line,name;
    cin >> k;
    cin.ignore();
    getline(cin,line);
    stringstream ss(line);
    while(ss >> name){
        knights.insertar(name,knights.getLength()+1);
    }
}

void elegirCaballero(Lista<string> &knights,int k,int index){ // index debio ser pasado por referencia
    index = (index - 1 + (k - 1)) % knights.getLength() + 1;
    knights.eliminar(index);
}

int main(){
    Lista<string> caballeros;
    int nCasos,k,index;
    index = 1;                      // index no se resetea para cada caso
    cin >> nCasos;
    for(int i=1;i<=nCasos;i++){
        leerEntrada(caballeros,k);
        while(caballeros.getLength() > 1){
            elegirCaballero(caballeros,k,index);
        }
        cout << caballeros.consultarPos(1) << endl;
        caballeros.vaciar();
    } 
}