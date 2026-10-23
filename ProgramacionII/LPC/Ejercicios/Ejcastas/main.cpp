#include <iostream>
#include <string>
#include <sstream>
#include "lista.hpp"

using namespace std;

typedef struct{
    int casta;
    string nombre;
} miembro;

void leerEntrada(Lista<miembro> *players,int *rango,int *turno,int *cambio){

    string linea;
    cin >> *rango >> *turno >> *cambio;
    cin >> ws;
    getline(cin,linea);
    int len = linea.length();

    for(int i=0;i<len;i++){
        char c = linea[i];
        if(c == '(' || c == ')' || c == '[' || c == ']' || c == ','){
            linea[i] = ' ';     /* ERROR: == en vez de =*/
        }
    }

    stringstream ss(linea);
    string name;
    int value;

    while(ss >> name >> value){

        miembro m;
        m.nombre = name;
        m.casta = value;
        players->insertar(m,players->getLength()+1);
    }

}

bool quedanJugadores(Lista<miembro> *players){
    return players->getLength() > 1;
}

bool consultarMuerte(Lista<miembro> *players,int index,int *contT){

    miembro victima = players->consultarPos(index); 
    /* es mejor traerte el indice como parametro que el miembro como tal*/

    for(int i=1;i<=players->getLength();i++){
        miembro m = players->consultarPos(i);

        if(m.casta > victima.casta){
            return false; // la persona no muere y se reinicia el conteo CONTANDOLA como primera
            /* te enredaste retornando indices */
        }
    }

    players->eliminar(index); // tough luck numbskull
    (*contT)++;
    return true; // se reinicia el contador desde cero
}

void invertirCastas(Lista<miembro> *players){
    for(int i=1;i<=players->getLength();i++){
        miembro m = players->consultarPos(i);
        m.casta = m.casta * (-1);
        players->modificar(i,m);
    }
}

int main(){
    Lista<miembro> players;
    int casos,rango,turnos,cambio;

    cin >> casos;

    for(int i=0;i<casos;i++){ // nro casos de prueba

        leerEntrada(&players,&rango,&turnos,&cambio);

        int contT = 0; // contador para ver si hay que invertir los roles
        int index = 1; // para pasar del ultimo al primero en caso de exceder tamaño de la lista
        
        while(quedanJugadores(&players)){

            for(int pasos=1;pasos<turnos;pasos++){
                index = (index % players.getLength()) + 1; 
                /* no estabas trabajando el index de manera circular correctamente */
            }

            bool murio = consultarMuerte(&players,index,&contT);
            // funcion que elimina al jugador que toco el turno si es elegible
            
            if(contT == cambio){
                invertirCastas(&players);
                contT = 0; /* no reiniciaste contador*/
                // si ha muerto el numero adecuado de personas, invertimos todo
                // los ricos ahora son pobres y pobres ahora son ricos
            }

            if(!murio){
                /* no avanzamos */
            }
            else{
                if(index > players.getLength()){
                    index = 1;
                }
            }
            /* logica distinta y mas pulida para las muertes */
        }
        // para este punto la lista solo deberia tener 1 integrante
        miembro ganador = players.consultarPos(1);
        cout << "Ganador: " << ganador.nombre << endl;
        players.vaciar();
    }
}