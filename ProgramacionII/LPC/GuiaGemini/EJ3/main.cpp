#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>
#include "pila.hpp"

using namespace std;

int esVocal(char c){
    if(isupper(c)){
        c = tolower(c);
    }
    switch(c){
        case 'a':
            return 1;
            break;
        case 'e':
            return 1;
            break;
        case 'i':
            return 1;
            break;
        case 'o':
            return 1;
            break;
        case 'u':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

void leerEntrada(Pila<string> &voc,Pila<string> &con){
    string line,palabra;
    getline(cin,line);
    stringstream ss(line);
    while(ss >> palabra){
        //cout << "DEBUG: Palabra actual: " << palabra << endl;
        if(esVocal(palabra[0])){
            cout << "LA PALABRA ACTUAL VA EN VOCAL" << endl;
            voc.apilar(palabra);
        }
        else{
            //cout << "LA PALABRA ACTUAL VA EN CONSONANTE" << endl;
            if(palabra == "PURGA"){
                //cout << "LA PALABRA ES PURGA" << endl;
                if(!voc.esVacia()){
                    voc.desapilar();
                }
                if(!con.esVacia()){
                    con.desapilar();
                }
            }
            else{
                con.apilar(palabra);
            }
        }
    }
}

void imprimirSalida(Pila<string> &voc,Pila<string> &con){
    cout << "Vocales: ";
    if(voc.esVacia()){
        cout << "VACIA";
    }
    while(!voc.esVacia()){
        cout << voc.getTop();
        if(voc.getLength() > 1){
            cout << " ";
        }
        voc.desapilar();
    }
    cout << endl << "Consonantes: ";
    if(con.esVacia()){
        cout << "VACIA";
    }
    while(!con.esVacia()){
        cout << con.getTop();
        if(voc.getLength() > 1){
            cout << " ";
        }
        con.desapilar();
    }
    cout << endl;
}

int main(){
    int nCasos;
    cin >> nCasos;
    cin.ignore();

    for(int i=0;i<nCasos;i++){
        Pila<string> vocales;
        Pila<string> consonantes;
        leerEntrada(vocales,consonantes);
        imprimirSalida(vocales,consonantes);
    }
}