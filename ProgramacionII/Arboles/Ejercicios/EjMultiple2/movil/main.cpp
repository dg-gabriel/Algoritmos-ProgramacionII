#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include "ArbolBin.hpp"

using namespace std;

void leerEntrada(ArbolBin<int> &a){
    list<int> preorden,inorden;
    string line;
    for(int i=0;i<2;i++){
        getline(cin,line);
        stringstream ss(line);
        int num;
        while(ss >> num){
            if(i == 0){
                preorden.push_back(num);
            }
            else{
                inorden.push_back(num);
            }
        }
    }
    a.llenarPreIn(preorden,inorden);
}

bool esMovil(ArbolBin<int> &a){
    
}

int main(){
    ArbolBin<int> arbol;
    leerEntrada(arbol);
    
}