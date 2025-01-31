#include "heroe.h"

Heroe::Heroe(unsigned short w_, unsigned short h_, short x_s_, short y_s_,
             short posx_, short posy_, const QString &direccion_,
             bool salto_, unsigned short m_, short vida_, unsigned short fuerza_ataque_,QGraphicsScene *escena_)
    : Personaje(w_, h_, x_s_, y_s_, posx_, posy_, direccion_, salto_, m_, vida_, fuerza_ataque_) {
    bola_poder=new esfera(2,10,10,"://imagenes/bola_sin_fondo.png",posx_,posy_);
    carga_electrica=-1;
    temporizadorPoder= new QTimer(this);
    poderActivado=false;
    escena_-> addItem(bola_poder);
}

void Heroe::activar_Poder(){
    if(!poderActivado){
        poderActivado=true;
        temporizadorPoder->start(20);
    }
}
void Heroe::desactivar_Poder(){
    if(poderActivado){
        poderActivado=false;
        temporizadorPoder->stop();
    }
}
void Heroe::habilidad_especial() {
    // Fue necesario el temporizador para mover continuamente a la esfera con el personaje.
    connect(temporizadorPoder, &QTimer::timeout, this, [=]() {
        bola_poder->aceleracion(x(), y(), carga_electrica);
    });
}

Heroe::~Heroe(){
    delete bola_poder;
    delete temporizadorPoder;
}

