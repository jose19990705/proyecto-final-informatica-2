#include "esfera.h"
#include <QDebug>
#include <cmath>

esfera::esfera(short carga_electrica_, unsigned short w_esfera_,
               unsigned short h_esfera_, const QString &direccion_,
               short pos_x_jugador, short pos_y_jugador,unsigned short fuerza_ataque_, unsigned short masa_esfera_)
    : carga_electrica(carga_electrica_), w_esfera(w_esfera_), h_esfera(h_esfera_),
    fuerza_ataque(fuerza_ataque_), masa_esfera(masa_esfera_) {
    // Cargar y escalar la imagen de la esfera
    pixmap = QPixmap(direccion_);
    setPixmap(pixmap.scaled(w_esfera, h_esfera));
    disparo=false;

    // Inicializar el temporizador
    bola_sprite = new QTimer(this);
    connect(bola_sprite, &QTimer::timeout, this, [=]() {
        aceleracion(pos_x_jugador, pos_y_jugador, carga_electrica); // Llama a aceleracion
    });
    bola_sprite->start(16);
    vx=0;
    vy=0;

    // Establecer la posición inicial de la esfera
    setPos(pos_x_jugador + 350, pos_y_jugador);
}

unsigned short esfera::get_fuerzaDeAataque(){
    return fuerza_ataque;
}


void esfera::disparar_esfera(){
    disparo=true;
    vx=10;
    vy=0;
}




void esfera::aceleracion(short pos_x_jugador, short pos_y_jugador, short carga_jugador) {
    if (disparo) {
        // Si está en modo disparo, mover la esfera hacia la derecha
        setX(x() + vx);
        return;
    }

    const unsigned short k = 90; // Constante de Coulomb
    const float velocidadMaxima = 5.0f; // Reducir la velocidad máxima para mayor suavidad
    const float factorEscala = 0.01f; // Factor de escala para la fuerza
    const float distanciaMinima = 10; // Aumentar la distancia mínima para evitar oscilaciones

    // Calcula la distancia entre la esfera y el jugador
    short deltaX = pos_x_jugador - x();
    short deltaY = pos_y_jugador - y();

    // Distancia al cuadrado (para evitar la raíz cuadrada innecesaria)
    long long distanciaCuadrada = deltaX * deltaX + deltaY * deltaY;

    // Si la esfera está a menos de la distancia mínima, detenerse
    if (distanciaCuadrada < distanciaMinima * distanciaMinima) {
        vx = 0;
        vy = 0;
        return;
    }

    // Calcula las componentes normalizadas de la fuerza (con la ley de Coulomb)
    float Fx = k * carga_electrica * carga_jugador * deltaX / distanciaCuadrada;
    float Fy = k * carga_electrica * carga_jugador * deltaY / distanciaCuadrada;

    // Actualiza la velocidad acumulativa
   // vx += Fx * factorEscala;
   // vy += Fy * factorEscala;
    float ax=Fx/masa_esfera;
    float ay=Fy/masa_esfera;
    vx+= ax*factorEscala;
    vy+= ay*factorEscala;
    // Limita la velocidad máxima
    if (vx > velocidadMaxima) vx = velocidadMaxima;
    else if (vx < -velocidadMaxima) vx = -velocidadMaxima;
    if (vy > velocidadMaxima) vy = velocidadMaxima;
    else if (vy < -velocidadMaxima) vy = -velocidadMaxima;

    // Movimiento de la esfera según la aceleración
    setX(x() + vx);
    setY(y() + vy);
    qDebug() << "Posición del héroe:" << pos_x_jugador << pos_y_jugador;
    qDebug() << "Posición de la esfera:" << x() << y();
    qDebug() << "Velocidad de la esfera:" << vx << vy;

}


void esfera::setVisible(bool visible) {
    QGraphicsPixmapItem::setVisible(visible);
}




esfera::~esfera() {
    delete bola_sprite;
}


