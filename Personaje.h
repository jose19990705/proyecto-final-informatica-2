#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QThread>
#include <string>

using namespace std;

class Personaje : public QGraphicsPixmapItem {
protected:
    string nombre;

    // Cada personaje posee un valor único de daño y de vida, a excepción de Homero
    unsigned short vida_Personaje;
    unsigned short danio;

    //Para generar movimientos de tiro parabólico, se busca generar dos velocidades: una en X y otra en Y
    int velocidadX;  // Velocidad en el eje X
    int velocidadY;  // Velocidad en el eje Y

    float posX;  // Posición en el eje X
    float posY;  // Posición en el eje Y

    bool salto;  // Estado para saber si está saltando
    bool avanza;  // Para saber en qué dirección se mueve el personaje, y gestionar los ataques
    QPixmap *spritePersonaje;
public:

    // Constructor y destructor
    Personaje(const string& nombre_, unsigned short vida_, unsigned short danio_, const QString& spriteInicial,
              int velocidadX = 0, int velocidadY = 0, int posX = 0, int posY = 0);  // Valores por defecto para los personajes
    ~Personaje();

    // Métodos principales
    void moverHorizontal();
    void cambioVida();
    void saltar();
    void morir();
    void actualizarFisicaSalto(float deltaTime);

    //Función amiga, esta buscará que el jugador pueda atacar
    friend void atacar(Personaje& atacado);
};

#endif // PERSONAJE_H
