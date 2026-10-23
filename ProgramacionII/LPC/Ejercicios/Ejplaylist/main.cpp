#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "lista.hpp"

using namespace std;

typedef struct{
    string name,auth;
    float duration;
} song;

void loadPlaylist(Lista<song> *play){

    ifstream archivo("Playlist.txt");
    string linea;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        string nameStr,artStr,durStr;

        getline(ss,nameStr,'-');
        getline(ss,artStr,'-');
        getline(ss,durStr,'-');

        song newsong;
        newsong.name = nameStr;
        newsong.auth = artStr;
        newsong.duration = stof(durStr);

        play->insertar(newsong,play->getLength()+1);

    }
    archivo.close();   
}

void showPlaylist(Lista<song> play){
    for(int i=0;i<play.getLength();i++){
        song aux = play.consultarPos(i+1);
        cout << aux.name << " " << aux.auth << " " << aux.duration << endl;
    }
}

void addSong(Lista<song> *play){

    cout << "Ingrese nombreCancion - autor - duracion\nEj. Song - John Singer - 1.00" << endl;
    string linea;
    getline(cin,linea);
    stringstream ss(linea);
    string nameStr,artStr,durStr;

    getline(ss,nameStr,'-');
    getline(ss,artStr,'-');
    getline(ss,durStr,'-');

    song newsong;
    newsong.name = nameStr;
    newsong.auth = artStr;
    newsong.duration = stof(durStr);

    play->insertar(newsong,play->getLength()+1);
    
}

void deleteSong(Lista<song> *play){
    cout << "Ingrese el nombre de la cancion a borrar" << endl;
    string name;
    getline(cin,name);
    for(int i=1;i<=play->getLength();i++){
        song aux = play->consultarPos(i);
        if(name == aux.name){
            play->eliminar(i);
            return;
        }
    }
    cout << "Cancion no encontrada" << endl;
}

void searchSong(Lista<song> play){
    cout << "Ingrese el nombre de la cancion que busca" << endl;
    string name;
    getline(cin,name);
    for(int i=1;i<play.getLength();i++){
        song aux = play.consultarPos(i);
        if(name == aux.name){
            cout << "Cancion encontrada\n" << aux.name << " " << aux.auth << " " << aux.duration << endl;
            return;
        }
    }
    cout << "No hubo coincidencia de nombre exacta" << endl;
}

void saveAndExit(Lista<song> play){

    ofstream file("Playlist.txt");
    for(int i=1;i<=play.getLength();i++){
        song aux = play.consultarPos(i);
        file << aux.name << "-" << aux.auth << "-" << aux.duration << endl; 
    }
    file.close();
}

int main(){
    Lista<song> playlist;
    loadPlaylist(&playlist);

    int opt;
    do{
        cout << "-MENU DE OPCIONES-\n1- Mostrar Playlist\n2- Agregar Cancion\n3- Eliminar cancion\n4- Buscar cancion\n5- Ordenar playlist\n6- Guardar y salir\nSeleccione una opcion: ";
        cin >> opt;
        cin.ignore();
        switch(opt){
            case 1:
                showPlaylist(playlist);
                break;
            case 2:
                addSong(&playlist);
                break;
            case 3:
                deleteSong(&playlist);
                break;
            case 4:
                searchSong(playlist);
                break;
            case 5:

                break;
            case 6:
                saveAndExit(playlist);
                cout << "Gracias por utilizar el programa" << endl;  
                break;
        }
    }
    while(opt != 6);
}
