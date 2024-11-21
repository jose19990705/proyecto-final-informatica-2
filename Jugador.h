#ifndef JUGADOR_H
#define JUGADOR_H

#include <QKeyEvent>
#include <QMap>

#include "Personaje.h"

// public QGraphicsPixmapItem

class Jugador : public Personaje {
    bool poder;   // Para controlar el poder especial de Homero
    bool inmune;  // Para gestionar el método "atacar"
public:
    Jugador(const string& nombre, unsigned short vida_Personaje, unsigned short danio, const QString& spriteJugador, int velocidadX, int velocidadY, int posX, int posY);

    void superGolpe();

    // Métodos sobrecargados
    void advance(int phase) override;
    void keyPressEvent(QKeyEvent *evento) override;
    void keyReleaseEvent(QKeyEvent *evento) override;

    QMap<int, bool> teclasPresionadas;  // Mapa de teclas con su estado (presionada o no)
};

#endif // JUGADOR_H
