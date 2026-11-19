template <class Element>
void backtrackDecision(GrafoNoDir<Element>& g,
                       typename list<Element>::iterator it,        // Vértice que toca decidir
                       const typename list<Element>::iterator& fin,// vertices.end()
                       /* 1. MAPAS DE ESTADO (ej. map<Element, int>& marca) */,
                       /* 2. CONTADORES POR REF (ej. int& progreso) */,
                       list<Element>& seleccionAct,
                       list<Element>& mejorSeleccion)
{
    // [A] PODA DE OPTIMIZACIÓN
    if (!mejorSeleccion.empty() && seleccionAct.size() >= mejorSeleccion.size()) {
        return;
    }

    // [B] CASO BASE 1 (Éxito: ya se cumplió el objetivo global)
    if (/* condición de éxito global: ej. progreso == g.getNVertices() */) {
        mejorSeleccion = seleccionAct;
        return;
    }

    // [C] CASO BASE 2 (Fin de los vértices sin lograr el objetivo)
    if (it == fin) {
        return;
    }

    Element v = *it;
    typename list<Element>::iterator sigIt = it;
    ++sigIt; // Apunta al siguiente vértice para la recursión

    // [D] TOMA DE DECISIONES SOBRE EL VÉRTICE 'v'
    // (Si es Subconjunto: son 2 decisiones -> Incluir 'v' vs. No incluir 'v')
    // (Si es Coloreo/Asignación: es un for(int c = 1; c <= M; ++c))

    if (/* ¿Es válido aplicar la decisión a 'v'? */) {
        // [E] HACER (Aplicar decisión a 'v' y/o a g.getVecinos(v))
        seleccionAct.push_back(v);
        /* actualizar mapas/contadores (+1) */

        // [F] RECURSIÓN (Pasar al siguiente vértice 'sigIt')
        backtrackDecision(g, sigIt, fin, /* estados */, seleccionAct, mejorSeleccion);

        // [G] DESHACER / BACKTRACK (Revertir exactamente lo hecho en [E])
        /* revertir mapas/contadores (-1) */
        seleccionAct.pop_back();
    }

    // [H] RAMA DE EXCLUSIÓN (Solo en problemas de Subconjuntos: probar NO elegir 'v')
    backtrackDecision(g, sigIt, fin, /* estados */, seleccionAct, mejorSeleccion);
}

// LANZADOR
template <class Element>
list<Element> resolverProblemaDecision(GrafoNoDir<Element>& g) {
    list<Element> vertices = g.getVertices();
    list<Element> seleccionAct, mejorSeleccion;
    /* declarar mapas de estado y contadores en 0 */

    backtrackDecision(g, vertices.begin(), vertices.end(), /* estados */, seleccionAct, mejorSeleccion);
    return mejorSeleccion;
}