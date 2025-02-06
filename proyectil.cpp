#include "proyectil.h"

#include <QDebug>

short Proyectil::proyectiles_lanzados = 0;

// Asigna a las coordenadas
Proyectil::Proyectil(short x_, short y_, short dx_, bool esDeHeroe_, bool direccion) : x(x_), y(y_), dx(dx_), esDeHeroe(esDeHeroe_) {
    if (direccion) {
        x += 60;
        y += 40;
    } else {
        x -= 30;
        y += 40;
    }
    if (esDeHeroe) {
        // Poner sprite proyectil heroe
        danio = 5;
    } else {
        // Poner sprite proyectil villano
        danio = 2;
    }
    sprite = new QPixmap(R"(://imagenes/Bullet.png)");
    setPixmap(sprite->copy(1, 11, 34, 16).scaled(40, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setPos(x, y);  // Posición inicial donde aparecerá el personaje en la escena
    proyectiles_lanzados += 1;
}

// Destructor del proyectil
Proyectil::~Proyectil(){
    delete sprite;
}

// Obtiene coordenadas en el eje X
short Proyectil::getX() {
    return x;
}

// Si el proyectil sale de la escena, lo elimina
bool Proyectil::estaFueraDeLaEscena() {
    if (x == 0 || x > 1400) {
        proyectiles_lanzados -= 1;
        return true;
    }
    return false;
}

// Método para cuando el proyectil choca con un personaje
bool Proyectil::impactaPersonaje() {
    QList<QGraphicsItem*> colisiones = this->collidingItems();

    // Verificamos si el proyectil ha colisionado con un personaje
    for (auto& item : colisiones) {
        // Intentamos convertir el objeto colisionante en objeto tipo Personaje
        Personaje* personaje = dynamic_cast <Personaje*> (item);
        if (personaje) {
            proyectiles_lanzados -= 1;
            return true;
        }
    }
    return false;
}

// Mueve el proyectil en línea recta
void Proyectil::mover() {
    x += dx;
    this->setPos(x, y);
}
