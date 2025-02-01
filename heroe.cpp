#include "heroe.h"

Heroe::Heroe(unsigned short w_, unsigned short h_, short x_s_, short y_s_,
             short posx_, short posy_, const QString &direccion_, bool salto_,
             unsigned short m_, short vida_, unsigned short fuerza_ataque_, QGraphicsScene *escena_)
    : Personaje(w_, h_, x_s_, y_s_, posx_, posy_, direccion_, salto_, m_, vida_, fuerza_ataque_) {
    bola_poder = nullptr; // Inicialmente, no hay esfera
    carga_electrica = -1;
    temporizadorPoder = new QTimer(this);
    poderActivado = false;
    mover = true; // El jugador puede moverse inicialmente
    escena_p=escena_;
}

void Heroe::activar_Poder() {
    if (!poderActivado) {
        poderActivado = true;
        mover = false; // Bloquear el movimiento del jugador

        // Crear la esfera solo cuando se activa el poder
        bola_poder = new esfera(2, 10, 10, "://imagenes/bola_sin_fondo.png", this->x(), this->y());
        bola_poder->setVisible(true); // Hacer visible la esfera
        escena_p->addItem(bola_poder); // Añadir la esfera a la escena

        this->habilidad_especial(); // Conectar el temporizador
        temporizadorPoder->start(20);
    }
}
void Heroe::habilidad_especial() {
    // Conectar el temporizador para mover la esfera con el personaje
    connect(temporizadorPoder, &QTimer::timeout, this, [=]() {
        if (bola_poder) {
            bola_poder->aceleracion(this->x(), this->y(), carga_electrica);
        }
    });
}
void Heroe::desactivar_Poder() {
    if (poderActivado) {
        poderActivado = false;
        mover = true; // Permitir el movimiento del jugador nuevamente
        temporizadorPoder->stop();

        if (bola_poder) {
            bola_poder->disparar_esfera(); // Disparar la esfera hacia la derecha
        }
    }
}

bool Heroe::get_moverse()  {
    return mover;
}
Heroe::~Heroe(){
    delete bola_poder;

    delete temporizadorPoder;

    delete escena_p;

}
