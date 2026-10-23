#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

void leerEntrada(Lista<string> &guardianes,int &k){
    string entry,name;
    cin >> k;
    cin.ignore();

    getline(cin,entry);
    stringstream ss(entry);
    while(ss >> name){
        guardianes.insertar(name,guardianes.getLength()+1);
    }
}

bool inicialEsVocal(string nombre){
    char a = nombre[0];
    a = tolower(a);
    if(a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u'){
        return true;
    }
    return false;
}

string obtenerProtector(Lista<string> &guardianes,int k,int index){
    string actual;
    int sentido = 1;
    while(guardianes.getLength() > 1){
        int L = guardianes.getLength();
        if(sentido == 1){
            index = (index - 1 + (k - 1)) % L + 1;
        }
        else{
            index = ((index - 1 - (k-1)) % L + L) % L + 1;  
        }
        actual = guardianes.consultarPos(index);
        if(actual.length() % 2 == 0){
            sentido = sentido * (-1);
        }
        if(inicialEsVocal(actual)){
            k++;
        }
        else{
            if(k > 2){
                k--;
            }
            else{
                k = 2;
            }
        }
        guardianes.eliminar(index);
    }
    return guardianes.consultarPos(1);
}

int main(){
    int n;
    cin >> n;

    for(int i=1;i<=n;i++){
        int k;
        Lista<string> guardianes;
        leerEntrada(guardianes,k);
        string guardian = obtenerProtector(guardianes,k,1);
        cout << guardian << endl;
    }

}