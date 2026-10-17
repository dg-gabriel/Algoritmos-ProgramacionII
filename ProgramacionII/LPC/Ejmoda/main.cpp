#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

typedef struct{
    string etiqueta;
    int cont;
} Instancias;

void obtenerTamano(Lista<Lista<string> > *col){

    string firstLine;
    getline(cin,firstLine);
    int len = firstLine.length();
    int n = 1;

    for(int i=0;i<len;i++){
        char c = firstLine[i];
        if(c == ','){
            n++;
        }
    }
    for(int i=0;i<n;i++){
        Lista<string> sublist;
        col->insertar(sublist,i+1);

    }
}

void leerDatos(Lista<Lista<string> > *col){

    string line,tag;
    while(getline(cin,line)){

        int len = line.length();
        for(int i=0;i<len;i++){
            char c = line[i];
            if(c == ','){
                line[i] = ' ';
            }
        }

        stringstream ss(line);

        for(int i=1;i<=col->getLength();i++){
            ss >> tag;
            Lista<string> sublist = col->consultarPos(i);
            sublist.insertar(tag,sublist.getLength()+1);
            col->modificar(i,sublist);
        }
    }
}

string calcularModa(Lista<string> column){

    Lista<Instancias> diccionary;

    for(int i=1;i<=column.getLength();i++){
        string actual = column.consultarPos(i);
        bool found = false;

        for(int j=1;j<=diccionary.getLength();j++){
            Instancias act = diccionary.consultarPos(j);

            if(act.etiqueta == actual){
                act.cont++;
                diccionary.modificar(j,act);
                found = true;
                break;
            }
        }
        if(!found){
            Instancias nuevo;
            nuevo.etiqueta = actual;
            nuevo.cont = 1;
            diccionary.insertar(nuevo,diccionary.getLength()+1);
        }
    }

    string moda;
    bool empate = false;
    int maxConteo = 0;
    for(int i=1;i<=diccionary.getLength();i++){
        Instancias aux = diccionary.consultarPos(i);
        if(aux.cont > maxConteo){
            maxConteo = aux.cont;
            moda = aux.etiqueta;
            empate = false;
        }
        else if(aux.cont == maxConteo){
            empate = true;
        }
    }
    if(empate || maxConteo == 1){
        return "ninguna";
    }
    else{
        return moda;
    }
}

int main(){
    
    Lista<Lista<string> > columns;
    Lista<Instancias> repetitions;
    obtenerTamano(&columns);
    leerDatos(&columns);

    for(int i=1;i<=columns.getLength();i++){
        Lista<string> sublist = columns.consultarPos(i);
        string moda = calcularModa(sublist);

        cout << moda;
        if(i < columns.getLength()){
            cout << ",";
        }
    }
    cout << endl;
    
    
}