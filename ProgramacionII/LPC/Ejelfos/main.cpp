#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

typedef struct{
    string name;
    int posicion;
} niño;

void leerEntrada(Lista<Lista<niño> > &list,int n){
    string entry,name;
    
    for(int i=1;i<=n;i++){
        Lista<niño> sublist;
        list.insertar(sublist,list.getLength()+1);
    }

    while(getline(cin,entry)){

        stringstream ss(entry);
        int col = 1;

        while(ss >> name){
            Lista<niño> auxlist = list.consultarPos(col);
            niño subject;
            subject.name = name;
            subject.posicion = auxlist.getLength()+1;
            auxlist.insertar(subject,auxlist.getLength()+1);
            list.modificar(col,auxlist);
            col++;
        }

    }
}

int buscarMemoria(Lista<niño> &memory,string name){
    for(int i=1;i<=memory.getLength();i++){
        niño consult = memory.consultarPos(i);
        if(consult.name == name){
            return i;
        }
    }
    return -1;
}

int calcularPaliza(Lista<niño> &list){

    int suma = 0;
    niño subject;
    Lista<niño> recordados;

    for(int i=1;i<=list.getLength();i++){
        string nombreAct = list.consultarPos(i).name;

        int posEnRecordados = buscarMemoria(recordados,nombreAct);

        if(posEnRecordados != -1){
            niño m = recordados.consultarPos(posEnRecordados);
            suma += (i - m.posicion) - 1;
            recordados.eliminar(posEnRecordados);
        }
        else{
            niño nuevo;
            nuevo.name = nombreAct;
            nuevo.posicion = i;
            recordados.insertar(nuevo,recordados.getLength()+1);
        }

    }


    return suma;
}

int main(){
    Lista<Lista<niño> > list;
    int nCasos;

    cin >> nCasos;
    cin.ignore();

    leerEntrada(list,nCasos);

    for(int i=1;i<=nCasos;i++){
        Lista<niño> aux = list.consultarPos(i);
        int paliza = calcularPaliza(aux);
        cout << paliza << endl;
    }

    return 0;

}