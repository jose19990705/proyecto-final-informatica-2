#include "heroe.h"

Heroe::Heroe(unsigned short w_, unsigned short h_, short x_s_, short y_s_,
             short posx_, short posy_, const QString &direccion_,
             bool salto_, unsigned short m_, short vida_, unsigned short fuerza_ataque_)
    : Personaje(w_, h_, x_s_, y_s_, posx_, posy_, direccion_, salto_, m_, vida_, fuerza_ataque_) {
    bola_poder=new esfera(1,10,10,"://imagenes/bola_sin_fondo.png",posx_,posy_);
    carga_electrica=-1;
}


void Heroe::habilidad_especial(){
    bola_poder->aceleracion(x(),y(),carga_electrica);
}

Heroe::~Heroe(){
    delete bola_poder;
}
