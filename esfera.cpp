/*
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

*/
#include "esfera.h"
#include <QDebug>
#include <cmath>

esfera::esfera(short carga_electrica_, unsigned short w_esfera_,
               unsigned short h_esfera_, const QString &direccion_,
               short pos_x_jugador, short pos_y_jugador)
    : carga_electrica(carga_electrica_), w_esfera(w_esfera_), h_esfera(h_esfera_) {
    // Cargar y escalar la imagen de la esfera
    pixmap = QPixmap(direccion_);
    setPixmap(pixmap.scaled(w_esfera, h_esfera));

    // Inicializar el temporizador
    bola_sprite = new QTimer(this);
    connect(bola_sprite, &QTimer::timeout, this, [=]() {
        aceleracion(pos_x_jugador, pos_y_jugador, carga_electrica); // Llama a aceleracion
    });
    bola_sprite->start(16);
    vx=0;
    vy=0;

    // Establecer la posición inicial de la esfera
    setPos(pos_x_jugador + 300, pos_y_jugador);
}

void esfera::aceleracion(short pos_x_jugador, short pos_y_jugador, short carga_jugador) {
    const unsigned short k = 900; // Constante de Coulomb
    const float velocidadMaxima = 10.0f; // Límite de velocidad
    const float factorEscala = 0.01f; // Factor de escala para la fuerza
    const float distanciaMinima = 2.0f; // Distancia mínima para detenerse

    // Calcula la distancia entre la esfera y el jugador
    short deltaX = pos_x_jugador - x();
    short deltaY = pos_y_jugador - y();

    // Distancia al cuadrado (para evitar la raíz cuadrada innecesaria)
    long long distanciaCuadrada = deltaX * deltaX + deltaY * deltaY;

    // Si la esfera está a menos de 2 píxeles del jugador, detenerse
    if (distanciaCuadrada < distanciaMinima * distanciaMinima) {
        vx = 0; // Detener la velocidad en X
        vy = 0; // Detener la velocidad en Y
        return; // Salir del método sin aplicar más fuerza
    }

    // Fuerza total usando la ley de Coulomb
    long long F = k * carga_electrica * carga_jugador;

    // Calcula las componentes normalizadas de la fuerza
    float Fx = F * deltaX / distanciaCuadrada;
    float Fy = F * deltaY / distanciaCuadrada;

    // Actualiza la velocidad acumulativa
    vx += Fx * factorEscala;
    vy += Fy * factorEscala;

    // Limita la velocidad máxima
    if (vx > velocidadMaxima) vx = velocidadMaxima;
    else if (vx < -velocidadMaxima) vx = -velocidadMaxima;
    if (vy > velocidadMaxima) vy = velocidadMaxima;
    else if (vy < -velocidadMaxima) vy = -velocidadMaxima;

    // Mueve la esfera según la velocidad acumulativa
    setX(x() + vx);
    setY(y() + vy);

    // Depuración: Imprime las posiciones y fuerzas
    qDebug() << "DeltaX:" << deltaX << "DeltaY:" << deltaY;
    qDebug() << "Fx:" << Fx << "Fy:" << Fy;
    qDebug() << "VelocidadX:" << vx << "VelocidadY:" << vy;
    qDebug() << "Nueva posición - X:" << x() << "Y:" << y();
}

esfera::~esfera() {
    // Limpiar recursos
    delete bola_sprite;
}

