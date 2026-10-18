#include "ArbolBin.hpp"
#include <iostream>
#include <sstream>
#include <list>

using namespace std;

void leerEntrada(ArbolBin<int> &tree){
    list<int> in,pre;
    string line1,line2;
    while(getline(cin,line1)){
        getline(cin,line2);
        stringstream ss1(line1);
        stringstream ss2(line2);
        int data;
        while(ss1 >> data){
            in.push_back(data);
        }
        while(ss2 >> data){
            pre.push_back(data);
        }
    }
    tree.llenarPreIn(pre,in);
}

int main(){
    ArbolBin<int> sacrificio;
    leerEntrada(sacrificio);
    cout << "leyo el arbol" << endl;
    cout << sacrificio.getAltura() << endl;
}