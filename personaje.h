#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QString>

class Personaje : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

protected:
    unsigned short w, h;    // Ancho y alto del sprite
    short x_s, y_s;         // Coordenadas del sprite
    short posx, posy;       // posición del personaje
    QPixmap *pixmap;        // Pixmap para el sprite
    bool salto;
    float v0y; // Velocidad vertical para el salto
    float gravedad;          // Gravedad que afecta al personaje

public:
    Personaje(unsigned short w_, unsigned short h_, short x_s_, short y_s_,short posx_,short posy_, const QString &direccion_, bool salto_);
    ~Personaje();
    void actualizar_pixmap(const QString &direccion_);
    void sprite_derecha();
    void sprite_izquierda();
    short get_posx();
    short get_posy();


    //métodos para el salto
     void saltar();
    void set_posicion();

    //void sprite_izquierda();
};

#endif // PERSONAJE_H
