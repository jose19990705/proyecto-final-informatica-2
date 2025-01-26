#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QString>
#include <QTimer>
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
    unsigned short m; //Masa delpersonaje. En base a esta será el retroceso del golpe (F=ma)
    short vida; //será la vida del personaje.
    unsigned short fuerza_ataque; //atributo de la fuerza de ataque del personaje.

public:
    Personaje(unsigned short w_, unsigned short h_, short x_s_,
              short y_s_,short posx_,short posy_,
              const QString &direccion_, bool salto_,
              unsigned short m_,short vida_,unsigned short fuerza_ataque_);
    ~Personaje();
    void actualizar_pixmap(const QString &direccion_);
    void sprite_derecha();
    void sprite_izquierda();
    short get_posx();
    short get_posy();


    //métodos para el salto
    void saltar();
    void set_posicion();

public:

    void set_fuerza(unsigned short magnitud_fuerza);

    //Método encargado para el retroceso.
    void retroceso(unsigned short fuerza_golpe, bool golpe_derecha);

    //Métodos para el ataque y lo relacionado a la vida.
    void restar_vida(unsigned short daño);

    //void sprite_izquierda();
};

#endif // PERSONAJE_H
