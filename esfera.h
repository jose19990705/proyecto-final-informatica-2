#ifndef ESFERA_H
#define ESFERA_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QTimer>
class esfera: public QObject, public QGraphicsPixmapItem
{
protected:
    short carga_electrica;
    unsigned short w_esfera,h_esfera; //esta estará en Ucoumlomb
    QPixmap *pixmap;
    QTimer *bola_sprite;

    //short posx, posy;


public:
    esfera(short carga_electrica_, unsigned short w_esfera_,
           unsigned short h_esfera_, const QString &direccion_,
           short pos_x_jugador, short pos_y_jugador);

    void aceleracion(short pos_x_jugador,short pos_y_jugador,short carga_jugador);
    ~esfera();
};

#endif // ESFERA_H
