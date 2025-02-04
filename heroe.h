#ifndef HEROE_H
#define HEROE_H
#include <QObject>
#include <QString>
#include <QTimer>
#include "personaje.h"
#include "esfera.h"
#include <QGraphicsScene>

class Heroe: public Personaje
{
    Q_OBJECT
private:
    esfera *bola_poder;
    short carga_electrica;
    QTimer *temporizadorPoder;
    bool poderActivado,mover;
    QGraphicsScene *escena_p;


public:
    Heroe(unsigned short w_, unsigned short h_, short x_s_, short y_s_,
          short posx_, short posy_, const QString &direccion_, bool salto_,
          unsigned short m_, short vida_, unsigned short fuerza_ataque_,QGraphicsScene *escena_);
    ~Heroe();
    //métodos para la habilidad especial
    void habilidad_especial();
    void activar_Poder();
    void desactivar_Poder();
    int get_posx();
    int get_posy();
    bool get_moverse();
};

#endif // HEROE_H
