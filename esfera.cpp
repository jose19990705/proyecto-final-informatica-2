#include "esfera.h"

esfera::esfera(short carga_electrica_, unsigned short w_esfera_,
               unsigned short h_esfera_, const QString &direccion_,
               short pos_x_jugador, short pos_y_jugador)
    : carga_electrica(carga_electrica_), w_esfera(w_esfera_), h_esfera(h_esfera_) {
    pixmap = new QPixmap(direccion_);

    // Inicializa la posición de la esfera a 20 píxeles a la derecha del jugador.
    setPos(pos_x_jugador + 20, pos_y_jugador);
}




//meotodos del comportamiento de la esfera.
void esfera::aceleracion(short pos_x_jugador, short pos_y_jugador, short carga_jugador) {
    const unsigned short k = 9000; // Constante de Coulomb multiplicada por un microcoumlomb.

    // Calcula la distancia entre la esfera y el jugador.
    short deltaX = pos_x_jugador - x(); // Diferencia en X.
    short deltaY = pos_y_jugador - y(); // Diferencia en Y.

    // Distancia al cuadrado (para evitar la raíz cuadrada innecesaria por ahora).
    long long distanciaCuadrada = deltaX * deltaX + deltaY * deltaY;
    if (distanciaCuadrada < 1) return; // Si ya está sobre el jugador, no hacemos nada.

    // Fuerza total usando la ley de Coulomb.
    long long F = k * carga_electrica * carga_jugador / distanciaCuadrada;

    // Distancia real.
    float distancia = sqrt(distanciaCuadrada);

    // Calcula las componentes normalizadas de la fuerza.
    float Fx = F * (deltaX / distancia);
    float Fy = F * (deltaY / distancia);

    // Mueve la esfera hacia el jugador (usa una escala pequeña para controlar la velocidad).
    setX(x() + Fx * 0.01); // Escala para suavizar el movimiento.
    setY(y() + Fy * 0.01);
}



esfera::~esfera(){
    delete pixmap;
    delete bola_sprite;
}



