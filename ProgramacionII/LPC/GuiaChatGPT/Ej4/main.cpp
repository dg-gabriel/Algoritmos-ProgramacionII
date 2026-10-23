#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

void leerEntrada(Lista<Lista<string> > &reinos,int &k){
    string line,name;
    int filas;
    cin >> k;
    cin >> filas;
    cin.ignore();

    for(int i=0;i<filas;i++){
        Lista<string> instancia;
        reinos.insertar(instancia,reinos.getLength()+1);
    }
    
    for(int i=0;i<filas;i++){   
    // el limite del for era la cantidad de columnas (4 siempre), no las filas que hay en el documento
        getline(cin,line);
        stringstream ss(line);
        int col = 1;
        while(ss >> name){
            Lista<string> sublist = reinos.consultarPos(col);
            sublist.insertar(name,sublist.getLength()+1);
            reinos.modificar(col,sublist);
            col++;
            if(col > 4){
                col = 1;
            }
        }
    }
}

void jugarRonda(Lista<string> &reino,int k,int &index){
    index = (index - 1 + (k - 1)) % reino.getLength() + 1;
    reino.eliminar(index);
}

int main(){
    
    int nCasos;
    cin >> nCasos;
    
    for(int i=1;i<=nCasos;i++){
        Lista<Lista<string> > reinos;
        int k;
        leerEntrada(reinos,k);
        int L = reinos.getLength();
        for(int j=1;j<=L;j++){
            Lista<string> reino = reinos.consultarPos(1);
            reinos.eliminar(1);
            int index = 1;
            //cout << reino.getLength() << " " << reino.consultarPos(1) << endl;
            while(reino.getLength() > 1){
                jugarRonda(reino,k,index);
            }
            cout << reino.consultarPos(1) << endl;
        }
    }

    
}