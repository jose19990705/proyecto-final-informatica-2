#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QString>
#include <QTimer>

class Personaje : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

protected:
    unsigned short wSprite, hSprite;    // Ancho y alto del sprite
    short x_sprite, y_sprite;         // Coordenadas dentro de la hoja de sprites
    short posx, posy;       // posición del personaje
    QPixmap *sprite;        // Pixmap para el sprite
    bool salto;
    float v0y;         // Velocidad vertical para el salto
    float gravedad;    // Gravedad que afecta al personaje
    short vida;        // Vida del personaje.
    unsigned short velocidadX;    // Velocidad horizontal del personaje
    unsigned short wPersonaje, hPersonaje;  // Ancho y alto del personaje en el escenario
public:
    // Ancho y alto del sprite, coordenadas dentro de la hoja de sprite, posición en el escenario, dirección en memoria del sprite, estado de salto, vida, velocidad horizontal, ancho y alto del personaje en el escenario
    Personaje(unsigned short wSprite_, unsigned short hSprite_, short x_sprite_,
              short y_sprite_, short posx_, short posy_, const QString &direccion_,
              bool salto_, short vida_, unsigned short velocidadX_, unsigned short wPersonaje,
              unsigned short hPersonaje);
    ~Personaje();

    // Métodos para la animación de los personajes mediante el cambio de sprites
    void actualizar_sprite(const QString &direccion_);
    void sprite_derecha(short x_sprite_max, short y_sprite);
    void sprite_izquierda(short x_sprite_min, short y_sprite);

    unsigned short get_velocidadX();

    short get_posx();
    short get_posy();

    //métodos para el salto
    void saltar();
    void set_posicion();

    //Métodos para el ataque y lo relacionado a la vida.
    void restar_vida(unsigned short daño);
};

#endif // PERSONAJE_H
