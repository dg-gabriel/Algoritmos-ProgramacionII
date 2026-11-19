#ifndef PLANTILLAS_BACKTRACKING_HPP
#define PLANTILLAS_BACKTRACKING_HPP

// ============================================================================
//  PLANTILLAS DE BACKTRACKING SOBRE GRAFOS  (C++98, solo API publica)
//  Grafo: GrafoNoDir<string>. Para GrafoDir cambia getVecinos por getSucesores
//  en los problemas de CAMINOS (en los de conjuntos, vecinos "en ambos
//  sentidos" suele ser lo correcto).
//
//  ESQUEMA COMUN (siempre igual):
//     1. ELEGIR     -> marcar / sumar / push_back
//     2. CASO BASE  -> ¿solucion completa? guardar copia o actualizar mejor
//     3. EXPLORAR   -> para cada candidato que pase la PODA, recursar
//     4. DESHACER   -> exactamente lo inverso de ELEGIR (mismo orden inverso)
//  Regla de oro: quien hace el push/marca, hace el pop/desmarca (misma funcion).
//
//  INDICE
//   1. todosLosCaminos            todos los caminos simples v -> w
//   2. caminoMasBarato            camino simple de MENOR costo v -> w
//   3. caminoSimpleMasPeligroso   camino simple de MAYOR costo (inicio libre)
//   4. caminoHamiltoniano         camino que pasa por TODOS los vertices (bool)
//   5. conjuntoDominanteMinimo    cada vertice elegido o vecino de uno elegido
//   6. conjuntoIndependienteMax   ningun par de elegidos es adyacente
//   7. cliqueMaxima               todos los elegidos adyacentes entre si
//   8. sePuedeColorear            colorear con k colores sin vecinos iguales
//   9. (comentario) cobertura de vertices minima = complemento de 6.
// ============================================================================

#include "GrafoNoDir.hpp"
#include <string>

// ---------------------------------------------------------------------------
// Auxiliar: suma delta al contador de v y de todos sus vecinos.
// Sirve para "cubiertos" (dominante) y "bloqueados" (independiente).
// Elegir -> delta = +1.  Deshacer -> delta = -1 (siempre el inverso exacto).
// ---------------------------------------------------------------------------
void sumarAVecinos(GrafoNoDir<string> &g,const string &v,int delta,map<string,int> &contador,bool incluirV){
    if(incluirV){
        contador[v] += delta;
    }
    list<string> vecinos = g.getVecinos(v);
    for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
        contador[*it] += delta;
    }
}

// ===========================================================================
// 1. TODOS LOS CAMINOS SIMPLES de origen a destino
//    Estado: vertice actual, camino actual, marcados.  Solucion: act == destino
// ===========================================================================
void caminosAux(GrafoNoDir<string> &g,const string &act,const string &destino,map<string,bool> &enCamino,list<string> &actual,list<list<string> > &todos){
    enCamino[act] = true;                              // ELEGIR
    actual.push_back(act);
    if(act == destino){                                // CASO BASE
        todos.push_back(actual);                       // guardar COPIA
    }
    else{
        list<string> vecinos = g.getVecinos(act);
        for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
            if(!enCamino[*it]){                        // PODA: no repetir vertices
                caminosAux(g,*it,destino,enCamino,actual,todos);   // EXPLORAR
            }
        }
    }
    actual.pop_back();                                 // DESHACER
    enCamino[act] = false;
}

list<list<string> > todosLosCaminos(GrafoNoDir<string> &g,const string &origen,const string &destino){
    list<list<string> > todos;
    if(g.existeVertice(origen) && g.existeVertice(destino)){
        map<string,bool> enCamino;
        list<string> actual;
        caminosAux(g,origen,destino,enCamino,actual,todos);
    }
    return todos;
}

// ===========================================================================
// 2. CAMINO MAS BARATO de origen a destino (pesos >= 0)
//    Igual que (1) pero en vez de guardar todos, se queda con el mejor.
//    PODA extra: si el costo acumulado ya no mejora al mejor, no sigas.
//    Para el MAS CARO: quita la poda extra y cambia "<" por ">" (ver 3).
// ===========================================================================
void masBaratoAux(GrafoNoDir<string> &g,const string &act,const string &destino,float costo,map<string,bool> &enCamino,list<string> &actual,float &mejorCosto,list<string> &mejorCamino,bool &hay){
    if(hay && costo >= mejorCosto){                    // PODA: no puede mejorar
        return;
    }
    enCamino[act] = true;                              // ELEGIR
    actual.push_back(act);
    if(act == destino){                                // CASO BASE
        hay = true;
        mejorCosto = costo;
        mejorCamino = actual;
    }
    else{
        list<string> vecinos = g.getVecinos(act);
        for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
            if(!enCamino[*it]){
                masBaratoAux(g,*it,destino,costo + g.getCostoArco(act,*it),enCamino,actual,mejorCosto,mejorCamino,hay);
            }
        }
    }
    actual.pop_back();                                 // DESHACER
    enCamino[act] = false;
}

// retorna el costo; el camino queda en "camino". Si no hay camino: -1 y vacio.
float caminoMasBarato(GrafoNoDir<string> &g,const string &origen,const string &destino,list<string> &camino){
    float mejorCosto = -1;
    bool hay = false;
    camino.clear();
    if(g.existeVertice(origen) && g.existeVertice(destino)){
        map<string,bool> enCamino;
        list<string> actual;
        masBaratoAux(g,origen,destino,0,enCamino,actual,mejorCosto,camino,hay);
    }
    return mejorCosto;
}

// ===========================================================================
// 3. CAMINO SIMPLE DE MAYOR COSTO (empieza en cualquier vertice, sin destino)
//    Todo prefijo es un camino valido -> se compara en CADA llamada.
//    Sin poda de costo (sumar mas siempre puede ayudar).
// ===========================================================================
void masPeligrosoAux(GrafoNoDir<string> &g,const string &act,float suma,map<string,bool> &enCamino,list<string> &actual,float &mejor,list<string> &mejorRuta){
    enCamino[act] = true;                              // ELEGIR
    actual.push_back(act);
    if(suma > mejor){                                  // CASO BASE (en cada nodo)
        mejor = suma;
        mejorRuta = actual;
    }
    list<string> vecinos = g.getVecinos(act);
    for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
        if(!enCamino[*it]){
            masPeligrosoAux(g,*it,suma + g.getCostoArco(act,*it),enCamino,actual,mejor,mejorRuta);
        }
    }
    actual.pop_back();                                 // DESHACER
    enCamino[act] = false;
}

float caminoSimpleMasPeligroso(GrafoNoDir<string> &g,list<string> &mejorRuta){
    float mejor = -1;
    mejorRuta.clear();
    list<string> vertices = g.getVertices();
    map<string,bool> enCamino;                         // se deja limpio tras cada inicio
    list<string> actual;
    for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
        masPeligrosoAux(g,*it,0,enCamino,actual,mejor,mejorRuta);
    }
    return mejor;
}

// ===========================================================================
// 4. CAMINO HAMILTONIANO (pasa por todos los vertices exactamente una vez)
//    Variante "existe?": la funcion devuelve bool y CORTA al primer exito.
//    (Cuando devuelve true, NO se deshace: el camino se queda en "actual").
// ===========================================================================
bool hamiltonianoAux(GrafoNoDir<string> &g,const string &act,int n,map<string,bool> &enCamino,list<string> &actual){
    enCamino[act] = true;                              // ELEGIR
    actual.push_back(act);
    if((int)actual.size() == n){                       // CASO BASE: todos visitados
        return true;
    }
    list<string> vecinos = g.getVecinos(act);
    for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
        if(!enCamino[*it]){
            if(hamiltonianoAux(g,*it,n,enCamino,actual)){
                return true;                           // corte: encontrado
            }
        }
    }
    actual.pop_back();                                 // DESHACER
    enCamino[act] = false;
    return false;
}

bool caminoHamiltoniano(GrafoNoDir<string> &g,list<string> &camino){
    camino.clear();
    list<string> vertices = g.getVertices();
    int n = (int)vertices.size();
    for(list<string>::iterator it = vertices.begin();it != vertices.end();++it){
        map<string,bool> enCamino;
        list<string> actual;
        if(hamiltonianoAux(g,*it,n,enCamino,actual)){
            camino = actual;
            return true;
        }
    }
    return false;
}

// ===========================================================================
// 5. CONJUNTO DOMINANTE MINIMO
//    Estado: res (elegidos) y cubierto[v] = cuantos elegidos cubren a v
//    (un elegido se cubre a si mismo y a sus vecinos). Contador, NO bool.
//    Ramificacion: el primer vertice sin cubrir DEBE cubrirlo el o un vecino.
//    PODA: si res ya es tan grande como mejor, no sigas.
// ===========================================================================
void dominanteAux(GrafoNoDir<string> &g,list<string> &vertices,map<string,int> &cubierto,list<string> &res,list<string> &mejor){
    if(res.size() >= mejor.size()){                    // PODA
        return;
    }
    string sinCubrir = "";
    bool hay = false;
    for(list<string>::iterator it = vertices.begin();it != vertices.end() && !hay;++it){
        if(cubierto[*it] == 0){
            sinCubrir = *it;
            hay = true;
        }
    }
    if(!hay){                                          // CASO BASE: todos cubiertos
        mejor = res;
        return;
    }
    list<string> candidatos = g.getVecinos(sinCubrir);
    candidatos.push_front(sinCubrir);                  // el o uno de sus vecinos
    for(list<string>::iterator it = candidatos.begin();it != candidatos.end();++it){
        res.push_back(*it);                            // ELEGIR
        sumarAVecinos(g,*it,1,cubierto,true);
        dominanteAux(g,vertices,cubierto,res,mejor);   // EXPLORAR
        sumarAVecinos(g,*it,-1,cubierto,true);         // DESHACER
        res.pop_back();
    }
}

list<string> conjuntoDominanteMinimo(GrafoNoDir<string> &g){
    list<string> vertices = g.getVertices();
    list<string> mejor = vertices;                     // "todos" siempre es valido
    list<string> res;
    map<string,int> cubierto;
    dominanteAux(g,vertices,cubierto,res,mejor);
    mejor.sort();                                      // salida alfabetica
    return mejor;
}

// ===========================================================================
// 6. CONJUNTO INDEPENDIENTE MAXIMO  (patron "incluir / no incluir")
//    Se decide vertice por vertice. bloqueado[v] = cuantos elegidos son
//    vecinos de v: solo se puede incluir v si bloqueado[v] == 0.
//    PODA: res + restantes no supera al mejor -> cortar.
// ===========================================================================
void independienteAux(GrafoNoDir<string> &g,list<string>::iterator act,list<string>::iterator fin,int restantes,map<string,int> &bloqueado,list<string> &res,list<string> &mejor){
    if(res.size() + restantes <= mejor.size()){        // PODA
        return;
    }
    if(act == fin){                                    // CASO BASE
        mejor = res;                                   // (si llego aqui, es mayor)
        return;
    }
    string v = *act;
    list<string>::iterator sig = act;
    ++sig;
    if(bloqueado[v] == 0){                             // opcion 1: INCLUIR v
        res.push_back(v);                              // ELEGIR
        sumarAVecinos(g,v,1,bloqueado,false);
        independienteAux(g,sig,fin,restantes - 1,bloqueado,res,mejor);
        sumarAVecinos(g,v,-1,bloqueado,false);         // DESHACER
        res.pop_back();
    }
    independienteAux(g,sig,fin,restantes - 1,bloqueado,res,mejor);  // opcion 2: NO incluir
}

list<string> conjuntoIndependienteMaximo(GrafoNoDir<string> &g){
    list<string> vertices = g.getVertices();
    list<string> res,mejor;
    map<string,int> bloqueado;
    independienteAux(g,vertices.begin(),vertices.end(),(int)vertices.size(),bloqueado,res,mejor);
    mejor.sort();
    return mejor;
}

// ===========================================================================
// 7. CLIQUE MAXIMA (mismo patron incluir / no incluir)
//    Se puede incluir v solo si es vecino de TODOS los ya elegidos:
//    adyacentes[v] == res.size().  Aqui el contador cuenta elegidos vecinos.
// ===========================================================================
void cliqueAux(GrafoNoDir<string> &g,list<string>::iterator act,list<string>::iterator fin,int restantes,map<string,int> &adyacentes,list<string> &res,list<string> &mejor){
    if(res.size() + restantes <= mejor.size()){        // PODA
        return;
    }
    if(act == fin){                                    // CASO BASE
        mejor = res;
        return;
    }
    string v = *act;
    list<string>::iterator sig = act;
    ++sig;
    if(adyacentes[v] == (int)res.size()){              // v conectado con todos los elegidos
        res.push_back(v);                              // ELEGIR
        sumarAVecinos(g,v,1,adyacentes,false);
        cliqueAux(g,sig,fin,restantes - 1,adyacentes,res,mejor);
        sumarAVecinos(g,v,-1,adyacentes,false);        // DESHACER
        res.pop_back();
    }
    cliqueAux(g,sig,fin,restantes - 1,adyacentes,res,mejor);
}

list<string> cliqueMaxima(GrafoNoDir<string> &g){
    list<string> vertices = g.getVertices();
    list<string> res,mejor;
    map<string,int> adyacentes;
    cliqueAux(g,vertices.begin(),vertices.end(),(int)vertices.size(),adyacentes,res,mejor);
    mejor.sort();
    return mejor;
}

// ===========================================================================
// 8. COLOREADO CON k COLORES (decision: ¿se puede?)
//    Se colorea vertice por vertice; para cada uno se prueba color 1..k.
//    PODA: el color no puede coincidir con el de un vecino ya coloreado.
//    color[v] == 0 significa "sin colorear".  Devuelve true y deja los colores.
// ===========================================================================
bool colorearAux(GrafoNoDir<string> &g,list<string>::iterator act,list<string>::iterator fin,int k,map<string,int> &color){
    if(act == fin){                                    // CASO BASE: todos coloreados
        return true;
    }
    string v = *act;
    list<string>::iterator sig = act;
    ++sig;
    list<string> vecinos = g.getVecinos(v);
    for(int c = 1;c <= k;c++){
        bool libre = true;                             // PODA: ningun vecino con color c
        for(list<string>::iterator it = vecinos.begin();it != vecinos.end();++it){
            if(color[*it] == c){
                libre = false;
            }
        }
        if(libre){
            color[v] = c;                              // ELEGIR
            if(colorearAux(g,sig,fin,k,color)){        // EXPLORAR
                return true;
            }
            color[v] = 0;                              // DESHACER
        }
    }
    return false;
}

bool sePuedeColorear(GrafoNoDir<string> &g,int k,map<string,int> &color){
    list<string> vertices = g.getVertices();
    color.clear();
    return colorearAux(g,vertices.begin(),vertices.end(),k,color);
}

// ===========================================================================
// 9. COBERTURA DE VERTICES MINIMA (toda arista tiene un extremo elegido)
//    No necesita codigo nuevo: es el COMPLEMENTO del independiente maximo.
//       cobertura = vertices \ conjuntoIndependienteMaximo(g)
// ===========================================================================

// ===========================================================================
// ESQUELETO "SUBCONJUNTO" PARA PROBLEMAS NUEVOS (incluir / no incluir):
//
//   void aux(g, act, fin, restantes, estadoAuxiliar, res, mejor){
//       if(res.size() + restantes <= mejor.size()) return;   // poda de tamano
//       if(act == fin){ mejor = res; return; }               // caso base
//       v = *act; sig = act+1;
//       if(puedoIncluir(v)){            // poda de validez
//           elegir(v); aux(... sig ...); deshacer(v);        // rama "incluir"
//       }
//       aux(... sig ...);               // rama "no incluir"
//   }
//   Para MINIMIZAR (dominante, cobertura): cambia a "res.size() >= mejor.size()"
//   y inicializa mejor con TODOS los vertices.
// ===========================================================================

#endif