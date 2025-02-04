#include "Villano.h"

static random_device random;
static mt19937 gen(random());

#include <QDebug>

Villano::Villano(unsigned short wSprite_, unsigned short hSprite_, short x_sprite_, short y_sprite_, short posx_, short posy_, const QString &direccion_, bool salto_, short vida_, unsigned short velocidadX_, unsigned short wPersonaje_, unsigned short hPersonaje_)
    : Personaje(wSprite_, hSprite_, x_sprite_, y_sprite_, posx_, posy_, direccion_, salto_, vida_, velocidadX_, wPersonaje_, hPersonaje_) {
}

QPoint Villano::generarVillanosEscenario1(short coordenadasInicialesHomero) {
    // Fijamos los límites del escenario
    int Xmin = 20, Xmax = 1000;

    // Generamos coordenadas aleatorias para posicionar al villano en el escenario
    uniform_int_distribution<> distributionX(Xmin, Xmax);
    int xRandom = distributionX(gen);

    // Evitamos que se creen villanos a una distancia horizontal villano - jugador menor a 200 pixeles
    while (abs(coordenadasInicialesHomero - xRandom) < 200) {
        xRandom = distributionX(gen);
    }

    // El valor fijo para Y debe ser el suelo del juego
    QPoint coordenadasEnemigo(xRandom, 368);
    return coordenadasEnemigo;
}

// Define una dirección y una cantidad de pasos en esa dirección que debe dar el villano
QPoint Villano::determinarMovimientoAleatorio() {
    unsigned short int izquierda = 0, derecha = 1;
    unsigned short int retrocede = 100, avanza = 200;

    uniform_int_distribution<> distributionDirection(izquierda, derecha);
    uniform_int_distribution<> distributionSteps(retrocede, avanza);

    unsigned short int directionRandom = distributionDirection(gen);
    unsigned short int stepsRandom = distributionSteps(gen);

    if (stepsRandom % 2 != 0) {
        stepsRandom += 1;
    }

    QPoint move (directionRandom, stepsRandom);
    return move;
}

void Villano::movimiento_villano(unsigned short coordenadasJugadorX) {
    // Si el villano está cerca del jugador, lo sigue
    if (abs(coordenadasJugadorX - this->x()) < 200 || abs(coordenadasJugadorX - this->x()) == 0) {
        if (coordenadasJugadorX < this->x()) {          //  Si el villano está a la derecha del jugador
            this->setX(this->x() - velocidadX);
        } else if (coordenadasJugadorX > this->x()) {   // Entonces si está a la izquierda del jugador
            this->setX(this->x() + velocidadX);
        }
    } else {    // Si no está cerca del jugador, se mueve de forma aleatoria
        if (steps == 0) {
            QPoint toMove = determinarMovimientoAleatorio();
            direction = toMove.x();
            steps = toMove.y();
        }

        // Verificamos si el próximo movimiento del villano saldrá del escenario
        unsigned short nuevaPosX = (direction == 0) ? this->x() - velocidadX : this->x() + velocidadX;

        // Si la nueva posición está fuera de los límites, generamos un nuevo movimiento
        if (nuevaPosX == 0 || nuevaPosX > 1280) {
            steps = 0;
        } else {
            this->setX(nuevaPosX);
            steps -= velocidadX;
        }
    }
}

Villano::~Villano(){
}
