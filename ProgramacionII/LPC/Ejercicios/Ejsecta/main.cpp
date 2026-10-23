#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

void leerEntrada(Lista<Lista<string> > &players,Lista<int> &pasos,int &casos){

    int k;
    string entry,name;
    cin >> casos;
    for(int i=0;i<casos;i++){
        cin >> k;
        pasos.insertar(k,pasos.getLength()+1);
    }

    for(int i=1;i<=casos;i++){
        Lista<string> sublist;
        players.insertar(sublist,i);
    }

    while(getline(cin,entry)){ 
        /*falto envolver getline en un while para que leyera todo el arch*/

        stringstream ss(entry);
        int columna = 1;
        /*columna como sustituto de i, se reinicia en cada linea nueva que se lee*/

        while(ss >> name){  
            /*while en vez de for, para que lea hasta que exista, no hasta un limite definido*/
            Lista<string> auxlist = players.consultarPos(columna);
            auxlist.insertar(name,auxlist.getLength()+1);
            players.modificar(columna,auxlist);
            columna++;
        }
    }
}

void jugarRonda(Lista<string> &players,int k,int &sentido,int &index){
    if(sentido == 1){
    /* if(sentido) se ejecuta con cualquier entero distinto de 0 */
        index = (index + k - 2) % players.getLength() + 1;
    }
    else{
        int L = players.getLength();
        index = ((index - k) % L + L) % L + 1;
        
    }
    players.eliminar(index);
    sentido = sentido * (-1);
}

int main(){

    Lista<Lista<string> > sectas;
    Lista<int> pasos;
    int nCasos;

    leerEntrada(sectas,pasos,nCasos);

    for(int i=1;i<=nCasos;i++){
        Lista<string> ronda = sectas.consultarPos(i);
        int k = pasos.consultarPos(i);
        int sentido = 1;
        int index = 1;
        /* no inicializaste index */
        while(ronda.getLength() > 1){
            jugarRonda(ronda,k,sentido,index);
        }
        cout << ronda.consultarPos(1) << endl;
    }
}