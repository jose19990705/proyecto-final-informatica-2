#ifndef HEROE_H
#define HEROE_H
#include <QObject>
#include <QString>
#include <QTimer>
#include "personaje.h"
#include "esfera.h"


class Heroe: public Personaje
{

private:
    esfera *bola_poder;
    short carga_electrica;
public:
    Heroe(unsigned short w_, unsigned short h_, short x_s_, short y_s_,
          short posx_, short posy_, const QString &direccion_, bool salto_,
          unsigned short m_, short vida_, unsigned short fuerza_ataque_);
    ~Heroe();
    void habilidad_especial();
};

#endif // HEROE_H
