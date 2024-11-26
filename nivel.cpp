#include "nivel.h"

nivel::nivel(unsigned short n_nivel): numero_nivel(n_nivel){}
nivel::~nivel(){}

//métodos principales
void nivel::agregarJugador(const Jugador &jugador_principal){
    jugador.push_back(jugador_principal)
}

void nivel::agregarVillanoPrincipal(const VillanoPrincipal& villano){
    villanos_principales.push_back(villano)
}

void agregarVillanoSecundario(const VillanoSecundario& villanosecu){
    villanos_secundarios.push_back(villanosecu)
}
