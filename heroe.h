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
   // proyectil *bala;
    esfera *bola_poder;
    short carga_electrica;
    QTimer *temporizadorPoder;
    bool poderActivado, mover;
    unsigned short cantidad_habilidad_especial;
    QGraphicsScene *escena_p;

    bool inmunidad;
    bool adelante;


public:
    Heroe (unsigned short wSprite_, unsigned short hSprite_, short x_Sprite_,
          short y_Sprite_, short posx_, short posy_, const QString &direccion_,
          bool salto_, short vida_, unsigned short velocidadX_,
          unsigned short wPersonaje_, unsigned short hPersonaje_,
          QGraphicsScene *escena_,unsigned short cantidad_habilidad_especial_);
    ~Heroe();

    // Métodos para la habilidad especial
    void habilidad_especial();
    void activar_Poder();
    void desactivar_Poder();
    int get_posx();
    int get_posy();
    bool get_estado_poder();
    bool daño_vida();
    bool get_moverse();
    void set_cant_habilidad();
    unsigned short get_cant_habilidad();

    // Métodos para controlar el estado de inmunidad
    void activar_inmunidad();
    void desactivar_inmunidad();

    // Métodos para cambiar el estado de la variable "adelante" del jugador
    void avanza();
    void retrocede();

    // Método para saber la dirección del jugador
    bool get_direccion();

};

#endif // HEROE_H
