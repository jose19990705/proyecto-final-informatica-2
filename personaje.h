#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPainter>
#include <QThread>
#include <string>
using namespace std;
class Personaje
{
private:
    float vida_Personaje;
    string nombre;
    //Para generar saltos de tiro parabólico, se busca generar dos velocidades.
    //Una en X y otra en Y.
    float posX;      // Posición en el eje X.
    float posY;      // Posición en el eje Y.
    float velocidadX; // Velocidad en el eje X.
    float velocidadY; // Velocidad en el eje Y.
    bool salto;   // Estado para saber si está saltando.
    QPixmap *pixmap;

public:
    // Constructor y destructor.
    Personaje(float vida_, const string& nombre_);
    ~Personaje();

    // Métodos principales.
    void mover();
    void cambio_vida(float vida_Personaje);
    void saltar();
    void morir();
    void actualizarFisica(float deltaTime);
    //Función amiga, esta buscará que el jugador pueda atacar.
    friend void atacar(Personaje& atacado);
};

#endif // PERSONAJE_H
