#ifndef ESFERA_H
#define ESFERA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QTimer>

class esfera : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

protected:
    short carga_electrica;
    unsigned short w_esfera, h_esfera; // Tamaño de la esfera
    QPixmap pixmap; // Imagen de la esfera
    QTimer *bola_sprite;
    float vx,vy;
    bool disparo; // Esta variable booleana será para conocer si ya se encuentra disponible o no el disparo.

public:
    esfera(short carga_electrica_, unsigned short w_esfera_,
           unsigned short h_esfera_, const QString &direccion_,
           short pos_x_jugador, short pos_y_jugador);

    void aceleracion(short pos_x_jugador, short pos_y_jugador, short carga_jugador);
    void disparar_esfera();
    void setVisible(bool visible);

    ~esfera();
};

#endif // ESFERA_H
