#include <vector>

#ifndef NIVEL_H
#define NIVEL_H


using namespace std ;
class nivel
{
    unsigned short numero_nivel;

    // Vectores para almacenar las instancias
    vector<VillanoPrincipal> villanos_principales;
    vector<VillanoSecundario> villanos_secundarios;
    vector<Jugador> jugador;

public:
     nivel(unsigned short n_nivel);
    ~nivel();

    // Métodos
    void agregarJugador(const Jugador &jugador_principal);
    void agregarVillanoPrincipal(const VillanoPrincipal& villano);
    void agregarVillanoSecundario(const VillanoSecundario& villanosecu);
};

#endif // NIVEL_
