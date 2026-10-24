#include <iostream>
#include <fstream>

using namespace std;

// Genera un árbol binario perfecto de (2^ niveles - 1) nodos
void generarArbolPerfecto(ofstream &out, int nNodos) {
    out << nNodos << "\n";
    for (int i = 1; i <= nNodos; i++) {
        int izq = (2 * i <= nNodos) ? (2 * i) : -1;
        int der = (2 * i + 1 <= nNodos) ? (2 * i + 1) : -1;
        out << i << " " << izq << " " << der << "\n";
    }
}

int main() {
    ofstream out("casos_extremos.txt");
    
    int totalCasos = 18; // 3 casos especiales + 15 árboles masivos = > 1.2 millones de líneas
    out << totalCasos << "\n";

    // CASO 1: El árbol del dibujo de la página 2 del PDF (Respuesta esperada: 5)
    out << "9\n";
    out << "10 20 30\n";
    out << "20 40 50\n";
    out << "30 60 70\n";
    out << "40 -1 -1\n";
    out << "50 80 -1\n";
    out << "60 90 -1\n";
    out << "70 -1 -1\n";
    out << "80 -1 -1\n";
    out << "90 -1 -1\n";

    // CASO 2: Árbol Binario Perfecto de altura 17 -> 131,071 nodos (Respuesta esperada: 131071)
    generarArbolPerfecto(out, 131071);

    // CASO 3: Árbol Zig-Zag / Peine de 100,001 nodos (Respuesta esperada: 50001 hojas)
    int nPeine = 100001;
    out << nPeine << "\n";
    for (int i = 1; i <= nPeine; i++) {
        if (i % 2 == 1 && i + 2 <= nPeine) {
            // Nodo impar: hijo izq es par (hoja), hijo der es el siguiente impar
            out << i << " " << (i + 1) << " " << (i + 2) << "\n";
        } else {
            // Es hoja
            out << i << " -1 -1\n";
        }
    }

    // CASOS 4 al 18: 15 Árboles Perfectos de 65,535 nodos cada uno (~983,000 líneas extra)
    // (Respuesta esperada para cada uno de los 15: 65535)
    for (int k = 0; k < 15; k++) {
        generarArbolPerfecto(out, 65535);
    }

    out.close();
    cout << "Archivo 'casos_extremos.txt' generado con exito (> 1,200,000 lineas)!" << endl;
    return 0;
}