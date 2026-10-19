#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct NodoGen {
    string id;
    int izq;
    int der;
};

// Convierte un entero a identificador (ej: 1 -> "a" si es pequeño, o "N1", "N2" si es masivo)
string crearId(int num, bool usarLetras) {
    if (usarLetras && num <= 26) {
        string s = "";
        s += (char)('a' + num - 1);
        return s;
    }
    stringstream ss;
    ss << "Est" << num;
    return ss.str();
}

void genPreOrden(int u, const vector<NodoGen>& arbol, vector<string>& res) {
    if (u == -1) return;
    res.push_back(arbol[u].id);
    genPreOrden(arbol[u].izq, arbol, res);
    genPreOrden(arbol[u].der, arbol, res);
}

void genInOrden(int u, const vector<NodoGen>& arbol, vector<string>& res) {
    if (u == -1) return;
    genInOrden(arbol[u].izq, arbol, res);
    res.push_back(arbol[u].id);
    genInOrden(arbol[u].der, arbol, res);
}

void genPostOrden(int u, const vector<NodoGen>& arbol, vector<string>& res) {
    if (u == -1) return;
    genPostOrden(arbol[u].izq, arbol, res);
    genPostOrden(arbol[u].der, arbol, res);
    res.push_back(arbol[u].id);
}

void imprimirLineaRecorrido( ostream& out, const string& etiqueta, const vector<string>& rec) {
    out << etiqueta;
    for (size_t i = 0; i < rec.size(); ++i) {
        out << " " << rec[i];
    }
    out << "\n";
}

// Construye un árbol balanceado recursivamente en el vector
int construirBalanceado(int ini, int fin, vector<NodoGen>& arbol) {
    if (ini > fin) return -1;
    int mid = (ini + fin) / 2;
    arbol[mid].izq = construirBalanceado(ini, mid - 1, arbol);
    arbol[mid].der = construirBalanceado(mid + 1, fin, arbol);
    return mid;
}

void generarGrupo(ostream& out, int numNodos, int numConsultas, int tipoArbol, bool usarNumEnConsulta, bool usarLetras) {
    vector<NodoGen> arbol(numNodos);
    for (int i = 0; i < numNodos; ++i) {
        arbol[i].id = crearId(i + 1, usarLetras);
        arbol[i].izq = -1;
        arbol[i].der = -1;
    }

    int raiz = 0;

    if (tipoArbol == 1) {
        // 1. Degenerado hacia la izquierda: Raíz = último, cada nodo tiene hijo izq al anterior
        raiz = numNodos - 1;
        for (int i = numNodos - 1; i > 0; --i) {
            arbol[i].izq = i - 1;
        }
    } 
    else if (tipoArbol == 2) {
        // 2. Degenerado hacia la derecha: Raíz = 0, cada nodo tiene hijo der al siguiente
        raiz = 0;
        for (int i = 0; i < numNodos - 1; ++i) {
            arbol[i].der = i + 1;
        }
    } 
    else if (tipoArbol == 3) {
        // 3. Árbol Balanceado
        raiz = construirBalanceado(0, numNodos - 1, arbol);
    } 
    else {
        // 4. Zig-Zag patológico (Izquierda - Derecha - Izquierda - Derecha)
        raiz = 0;
        int izqPtr = 0, derPtr = numNodos - 1;
        int actual = 0;
        bool tocaIzq = true;
        while (izqPtr < derPtr) {
            if (tocaIzq) {
                izqPtr++;
                arbol[actual].der = derPtr;
                actual = derPtr;
            } else {
                derPtr--;
                arbol[actual].izq = izqPtr;
                actual = izqPtr;
            }
            tocaIzq = !tocaIzq;
        }
    }

    vector<string> pre, in, post;
    genPreOrden(raiz, arbol, pre);
    genInOrden(raiz, arbol, in);
    genPostOrden(raiz, arbol, post);

    // Alternamos el orden de aparición (INORDEN primero o después, PREORDEN o POSTORDEN)
    if (tipoArbol % 2 == 0) {
        imprimirLineaRecorrido(out, "PREORDEN", pre);
        imprimirLineaRecorrido(out, "INORDEN", in);
    } else {
        imprimirLineaRecorrido(out, "INORDEN", in);
        imprimirLineaRecorrido(out, "POSTORDEN", post);
    }

    // Generar la línea con los m identificadores a consultar (MUP)
    if (numConsultas > numNodos) numConsultas = numNodos;
    for (int i = 0; i < numConsultas; ++i) {
        // Seleccionamos nodos distribuidos (incluyendo los extremos del árbol)
        int idx = (i * (numNodos - 1)) / (numConsultas > 1 ? numConsultas - 1 : 1);
        if (i > 0) out << " ";
        if (usarNumEnConsulta) {
            out << (idx + 1); // Si el problema pide índices 1..N (mapeados)
        } else {
            out << in[idx];   // Si el problema pide los identificadores (strings/chars)
        }
    }
    out << "\n";
}

int main() {
    ofstream archivo("casos_extremos.txt");

    // ================= CONFIGURACIÓN DEL STRESS TEST =================
    int T = 1;                  // Cantidad de casos de prueba
    int N_GRUPOS = 4;           // 4 árboles extremos por caso
    int NODOS_POR_ARBOL = 2000; // Sube esto a 5000 o 10000 para probar Time Limit
    int M_CONSULTAS = 400;      // Cantidad de estudiantes (m) en la línea de consulta
    
    // Pon en 'true' si la línea de consulta lleva números (1 3 5 7) 
    // o en 'false' si lleva los nombres/letras de los estudiantes (Est1 Est5 Est9)
    bool consultaConNumeros = false; 
    
    // Pon en 'true' si quieres un caso chiquito con letras 'a'..'z' (máx 26 nodos)
    bool usarSoloLetras = false;
    // =================================================================

    if (usarSoloLetras && NODOS_POR_ARBOL > 26) {
        NODOS_POR_ARBOL = 26;
    }

    archivo << T << "\n";
    for (int t = 0; t < T; ++t) {
        archivo << N_GRUPOS << "\n";
        for (int g = 1; g <= N_GRUPOS; ++g) {
            generarGrupo(archivo, NODOS_POR_ARBOL, M_CONSULTAS, g, consultaConNumeros, usarSoloLetras);
        }
    }

    archivo.close();
    cout << "Archivo 'casos_extremos.txt' generado con exito (" 
         << NODOS_POR_ARBOL << " nodos por arbol)." << endl;
    return 0;
}