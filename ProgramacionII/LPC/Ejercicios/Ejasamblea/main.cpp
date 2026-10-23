#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

void leerEntrada(Lista<Lista<string> > &circulo,int n){

    string entry,name;
    for(int i=1;i<=n;i++){
        Lista<string> auxlist = circulo.consultarPos(i);
        getline(cin,entry);
        stringstream ss(entry);
        while(ss >> name){
            auxlist.insertar(name,auxlist.getLength()+1);
        }
        circulo.modificar(i,auxlist);
    }
        
}

int main(){

    int n;
    string ultDev;
    Lista<Lista<string> > asambleas;

    cin >> n;
    cin.ignore();

    for(int i=1;i<=n;i++){
        Lista<string> asamblea;
        asambleas.insertar(asamblea,i);
    }

    leerEntrada(asambleas,n);

    while(asambleas.getLength() > 1 || asambleas.consultarPos(1).getLength() > 1){
    /* no era necesaria la funcion, la logica del while debe ser asi: */
        for(int i=1;i<=asambleas.getLength();i++){

            
            Lista<string> asambleaActual = asambleas.consultarPos(i);
            if(asambleaActual.getLength() > 1){
                ultDev = asambleaActual.consultarPos(1);
                asambleaActual.insertar(ultDev,asambleas.getLength()+1);
                asambleaActual.eliminar(1);
                asambleaActual.eliminar(1);

                asambleas.modificar(i,asambleaActual);
                /* olvidaste el modificar aca */
                
            }
            /* te falto la logica que dictaba que hacer cuando quedaba un solo miembro */
            if(asambleas.getLength() == 1){
                if(asambleaActual.getLength() == 1){
                    break;
                }
            }
            else{
                asambleas.eliminar(i);
                i--;
            }
            
        }
    }
    Lista<string> circuloGanador = asambleas.consultarPos(1);
    cout << circuloGanador.consultarPos(1) << endl;
    
}