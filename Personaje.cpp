#include "Personaje.h"
#include <iostream>
#include <cmath> // Para funciones matemáticas como std::max

using namespace std;

// Constructor con lista de inicialización.
Personaje::Personaje(const string& nombre_, unsigned short vida_, unsigned short danio_, const QString& spriteInicial,
                     int velocidadX, int velocidadY, int posX, int posY)
    : nombre(nombre_), vida_Personaje(vida_), danio(danio_), velocidadX(velocidadX), velocidadY(velocidadY), posX(posX), posY(posY), salto(false), avanza(false){

    spritePersonaje = new QPixmap(spriteInicial);  // Quitar comillas para ejecutar correctamente
}

Personaje::~Personaje(){
    delete spritePersonaje;
}

void Personaje::moverHorizontal(){  // Para desplazamiento horizontal
    if (avanza){
        // Implementar el signal / slot para el cambio de spriters durante el movimiento
        posX += velocidadX;
    } else {
        // Implementar el signal / slot para el cambio de spriters durante el movimiento
        posX -= velocidadX;
    }
    setPos(posX, posY);
}

void Personaje::saltar(){
    if (!salto) {
        velocidadY = 15;
        salto = true;
    }
}

void Personaje::cambioVida(){
    vida_Personaje -= 5;
}

void Personaje::morir(){
    cout << nombre << " has muerto" << endl;
    // Falta aún definir el sprite de cuando muere.
}

// Método para actualizar la posición en el eje Y y simular la gravedad
void Personaje::actualizarFisicaSalto(float deltaTime){
    if (salto) {
        // Actualizar la posición Y con la velocidad actual
        posY -= velocidadY * deltaTime;  // "-", para que el personaje pueda subir en el eje Y
        velocidadY += 9.8 * deltaTime; // Simular la gravedad
        if (posY >= 280) {  // Tenemos en cuenta el suelo del escenario según el sistema coordenado
            posY = 280;  // El personaje toca el suelo
            salto = false;
            velocidadY = 0; // Detener la caída
        }
    }
}
//Función friend, esta es encargada de alterar la vida del personaje enemigo,
//esta alterará la vida del personaje.
void atacar(Personaje& atacado){
    atacado.vida_Personaje -= 5;
}



