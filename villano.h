#ifndef VILLANO_H
#define VILLANO_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <random>

#include "personaje.h"

using namespace std;

class Villano : public Personaje {
    unsigned short direction;   // Dirección en la cual se da el movimiento
    unsigned short steps = 0;   // Contador de pasos dados en determinada dirección
    QPoint toMove;                  // Guarda información sobre la dirección y la cantidad de pixeles a mover
public:
    // Al constructor se le entregan valores para el ancho, alto, coordenadas, posición, dirección en memoria del sprite, estado de salto, masa, vida y fuerza de ataque
    Villano (unsigned short wSprite_, unsigned short hSprite_, short x_sprite_, short y_sprite_, short posx_, short posy_, const QString &direccion_,
            bool salto_, short vida_, unsigned short velocidadX_, unsigned short wPersonaje, unsigned short hPersonaje);

    // Generador de villanos para el escenario 1
    static QPoint generarVillanosEscenario1(short coordenadasInicialesHomero);

    // Para el movimiento automático de los villanos
    QPoint determinarMovimientoAleatorio();
    void movimiento_villano(unsigned short coordenadasJugadorX);

    ~Villano();
};

#endif // VILLANO_H
