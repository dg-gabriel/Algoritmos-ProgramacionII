
void backtrackRuta(GrafoNoDir<Element>& g,          // O GrafoDir<Element>&
                   const Element& act,              // Vértice donde estás parado
                   /* 1. PARÁMETROS DE META/LÍMITE (ej. destino, presupuestoMax) */,
                   map<Element, bool>& visitado,    // O map<Element, int> si permite repetir/cubrir
                   list<Element>& estadoAct,        // Camino o recolección actual
                   /* 2. ACUMULADORES ACTUALES (ej. float costoAct, int pasosAct) */,
                   list<Element>& mejorSolucion     // O list<list<Element> >& todasLasSoluciones
                   /* 3. RÉCORD GLOBAL POR REF (ej. float& mejorCosto) */)
{
    // [A] PODA DE OPTIMIZACIÓN (Opcional: solo si buscas mínimo/máximo)
    // Si el estadoAct ya es peor que mejorSolucion, abortar rama:
    if (/* condición de que ya empeoraste el récord o excediste un límite */) {
        return;
    }

    // [B] CASO BASE (Condición de Éxito / Meta)
    if (/* llegaste al destino, o estadoAct.size() == g.getNVertices(), etc. */) {
        // Guardar o actualizar la solución:
        mejorSolucion = estadoAct; // (O todasLasSoluciones.push_back(estadoAct))
        /* actualizar mejorCosto = costoAct; */
        return; // (OJO: si puedes seguir caminando tras cumplir meta, no pongas return)
    }

    // [C] EXPLORACIÓN DE ADYACENTES
    list<Element> ady = g.getVecinos(act); // Usar g.getSucesores(act) en GrafoDir
    typename list<Element>::iterator it;

    for (it = ady.begin(); it != ady.end(); ++it) {
        Element sig = *it;
        float peso = g.getCostoArco(act, sig); // Solo si el grafo es ponderado

        // [D] FILTRO DE VALIDEZ (¿Puedo saltar a 'sig'?)
        if (!visitado[sig] && /* otras reglas: ej. peso <= X, esSeguro(...) */) {

            // [E] HACER (Registrar el paso hacia 'sig')
            visitado[sig] = true;
            estadoAct.push_back(sig);
            /* modificar acumuladores: ej. costoAct += peso; */

            // [F] RECURSIÓN (Hundirse al vecino 'sig')
            backtrackRuta(g, sig, /* metas */, visitado, estadoAct, /* acum */, mejorSolucion);

            // [G] DESHACER / BACKTRACK (Dejar todo EXACTAMENTE como estaba antes de [E])
            /* revertir acumuladores: ej. costoAct -= peso; */
            estadoAct.pop_back();
            visitado[sig] = false;
        }
    }
}

// LANZADOR (En el main o función envolvente)
template <class Element>
list<Element> resolverProblemaRuta(GrafoNoDir<Element>& g, const Element& origen) {
    list<Element> estadoAct, mejorSolucion;
    map<Element, bool> visitado;
    /* inicializar récord global: ej. float mejorCosto = -1.0f; */

    // OBLIGATORIO si empiezas en un origen fijo: marcar el origen ANTES de llamar
    visitado[origen] = true;
    estadoAct.push_back(origen);

    backtrackRuta(g, origen, /* metas */, visitado, estadoAct, /* acum inicial 0 */, mejorSolucion);
    return mejorSolucion;
}