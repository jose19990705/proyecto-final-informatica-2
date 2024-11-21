#include "Jugador.h"
#include "Personaje.h"

#include <QDebug>

using namespace std;

Jugador::Jugador(const string& nombre, unsigned short vida_Personaje, unsigned short danio, const QString& spriteJugador, int velocidadX, int velocidadY, int posX, int posY)
    : Personaje(nombre, vida_Personaje, danio, spriteJugador, velocidadX, velocidadY, posX, posY), poder(false), inmune(false){

    *spritePersonaje = spritePersonaje->scaled(50, 80, Qt::KeepAspectRatioByExpanding);  // Definir tamaño del jugador
    setPixmap(*spritePersonaje);  // Asignamos el sprite al jugador
    setPos(posX, posY);  // Posición donde se crea el jugador (por defecto 0,0)

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}

void Jugador::keyPressEvent(QKeyEvent *evento){
    if (evento->key() == Qt::Key_W) {  // Si el jugador presiona la tecla para saltar
        if (avanza) {

        }
    }
    teclasPresionadas[evento->key()] = true;  // Marca la tecla como presionada
}

void Jugador::keyReleaseEvent(QKeyEvent *evento){
    teclasPresionadas[evento->key()] = false;  // Marca la tecla como liberada
}

void Jugador::advance(int phase){
    if (!phase) return;  // Solo avanzamos en cada actualización de la escena

    if (teclasPresionadas.value(Qt::Key_A, false)) {  // Para mover el jugador hacia la izquierda
        avanza = false;
        moverHorizontal();
        // Implementar condicional para verificar la colisión entre el jugador y otros objetos
    }
    else if (teclasPresionadas.value(Qt::Key_D, false)) {  // Para mover el jugador hacia la derecha
        avanza = true;
        moverHorizontal();
        // Implementar condicional para verificar la colisión entre el jugador y otros objetos
    }
}

void Jugador::superGolpe(){
    if (poder) {
        // Definir mecánica del super golpe
    }
}





