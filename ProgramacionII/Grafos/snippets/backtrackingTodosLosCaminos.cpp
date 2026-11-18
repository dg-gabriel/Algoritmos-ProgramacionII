#include <iostream>

void backtrack(/* estado actual */ /* acumuladores de la solución */){

    // 1. CASO BASE: ¿el estado actual es una solución completa?
    if(esSolucion(estado)){
        guardarOActualizarMejor(estado);   // guardar COPIA
        return;                            // (o seguir, si extender sigue siendo valido)
    }

    // 2. CANDIDATOS: ¿qué opciones tengo desde aquí?
    for(cada candidato c){

        // 3. PODA: ¿vale la pena probar c?
        if(!esValido(c, estado)) continue;
        // (poda extra opcional: si ya no puede mejorar al mejor, continue)

        // 4. ELEGIR: aplicar c al estado
        marcar(c); agregar(c);

        // 5. EXPLORAR: recursar con el estado nuevo
        backtrack(/* estado con c */);

        // 6. DESHACER: dejar el estado exactamente como estaba
        desagregar(c); desmarcar(c);
    }
}

int main(){

}