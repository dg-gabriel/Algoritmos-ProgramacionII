#include <iostream>
#include <string>
#include <sstream>
#include "pila.hpp"
#include "cola.hpp"

using namespace std;

typedef struct{
    string name;
    int cantMer;
    int cantEsp;
} Comerciante;

void leerEntrada(Cola<Comerciante> &comerciantes){
    string line;
    int L;
    cin >> L;
    cin.ignore();
    //cout << "DEBUG: L: " << L << endl;

    for(int i=0;i<L;i++){

        getline(cin,line);
        //cout << "DEBUG: LINE " << line << endl;
        int nroEntradas = 0,len = line.length();

        for(int j=0;j<len;j++){
            char c = line[j];
            if(c == ','){
                line[j] = ' ';
            }
            if(c == ':'){
                line[j] = ' ';
                nroEntradas++;
            }
        }
        //cout << "DEBUG: LINE POST PARSE: " << line << endl;
        //cout << "DEBUG: nroEntradas: " << nroEntradas << endl;
        if(nroEntradas > 1){

            string product,subLine;

            stringstream ss(line);
            
            while(getline(ss,subLine,';')){
                Comerciante nuevo;
                nuevo.cantMer = 0;
                nuevo.cantEsp = 0;
                //cout << "DEBUG: SUBLINE " << subLine << endl;
                stringstream ss2(subLine);
                if(ss2 >> nuevo.name){
                    //cout << "DEBUG: Nombre procesado: " << nuevo.name << endl;
                    while(ss2 >> product){
                        //cout << "DEBUG: Mercancia procesada: " << product <<  endl;
                        if(product == "especia"){
                            nuevo.cantEsp++;
                        }
                        nuevo.cantMer++;
                    }
                }
                comerciantes.encolar(nuevo);  
            }
            
            
        }
        else{
            Comerciante nuevo;
            nuevo.cantMer = 0;
            nuevo.cantEsp = 0;
            string product,subLine;

            stringstream ss3(line);

            if(ss3 >> nuevo.name){
                //cout << "DEBUG: Nombre procesado: " << nuevo.name << endl;
                while(ss3 >> product){
                    //cout << "DEBUG: Mercancia procesada: " << product <<  endl;
                    if(product == "especia"){
                        nuevo.cantEsp++;
                    }
                    nuevo.cantMer++;
                }
                comerciantes.encolar(nuevo);
            }
            

        }
        

    }
    
}

void procesarComerciantes(Cola<Comerciante> &comerciantes){
    Pila<string> confiscacion;
    Cola<Comerciante> exitosos;
    while(!comerciantes.esVacia()){
        Comerciante actual = comerciantes.getHead();
        comerciantes.desencolar();
        //cout << "DEBUG: ACTUAL COMERCIANTE SIENDO PROCESADO: " << actual.name << " CANT MERCANCIA: " << actual.cantMer <<
        //" CANT ESPECIAS: " << actual.cantEsp << endl;
        if(actual.cantEsp > 0){
            //cout << "DEBUG: " << actual.name << " TIENE: " << actual.cantEsp <<  " ESPECIAS, CONFISCANDO" << endl;
            confiscacion.apilar(actual.name);
            actual.cantMer -= actual.cantEsp;
            if(actual.cantMer == 0){
                //cout << "DEBUG: " << actual.name << " ESTA SIENDO DETENIDO POR POSESION EXCLUSIVA DE ESPECIAS" << endl;
                //ingatumai
            }
            else{
                exitosos.encolar(actual);
                //cout << "DEBUG: " << actual.name << " FUE PROCESADO CON EXITO" << endl;
            }
        }
        else{
            exitosos.encolar(actual);
            //cout << "DEBUG: " << actual.name << " FUE PROCESADO CON EXITO" << endl;
        }
    }
    while(!exitosos.esVacia()){
        cout << exitosos.getHead().name << " (" << exitosos.getHead().cantMer << ")";
        if(exitosos.getLength() > 1){
            cout << " ";
        }
        exitosos.desencolar();
    }
    cout << endl;
    if(!confiscacion.esVacia()){
        cout << "Contrabando: " << confiscacion.getLength() << " Unidades." << " Ultimo infractor: " << confiscacion.getTop() << endl;
    }
    else{
        cout << "Aduana Limpia" << endl;
    }
}

int main(){
    int nCasos;
    cin >> nCasos;
    for(int i=0;i<nCasos;i++){
        Cola<Comerciante> comerciantes;
        leerEntrada(comerciantes);
        procesarComerciantes(comerciantes);
    }
}