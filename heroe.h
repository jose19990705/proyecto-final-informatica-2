#ifndef HEROE_H
#define HEROE_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QGraphicsScene>

#include "personaje.h"
#include "esfera.h"

class Heroe: public Personaje {
    Q_OBJECT
private:
    esfera *bola_poder;
    short carga_electrica;
    QTimer *temporizadorPoder;
    bool poderActivado, mover;
    QGraphicsScene *escena_p;

public:
    Heroe (unsigned short wSprite_, unsigned short hSprite_, short x_Sprite_, short y_Sprite_, short posx_, short posy_, const QString &direccion_,
          bool salto_, short vida_, unsigned short velocidadX_, unsigned short wPersonaje_, unsigned short hPersonaje_, QGraphicsScene *escena_);
    ~Heroe();

    // Métodos para la habilidad especial
    void habilidad_especial();
    void activar_Poder();
    void desactivar_Poder();
    int get_posx();
    int get_posy();
    bool get_moverse();
};

#endif // HEROE_H
