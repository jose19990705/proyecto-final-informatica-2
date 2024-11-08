#include "Personaje.h"
#include <iostream>
#include <cmath> // Para funciones matemáticas como std::max

// Constructor con lista de inicialización.
Personaje::Personaje(float vida_, const std::string& nombre_)
    : vida_Personaje(vida_), nombre(nombre_), posX(0), posY(0), velocidadX(5), velocidadY(0), salto(false) {
    pixmap= new QPixmap("aca debe ir la dirección del sprite");
}

Personaje::~Personaje() {
    delete pixmap;
}

void Personaje::mover() {
    posX += velocidadX;
   }

void Personaje::saltar() {
    if (!salto) {
        velocidadY = 15;
        salto = true;

    }
}

void cambio_vida(float vida_Personaje){
     vida_Personaje-=5;
}



void Personaje::morir() {
    cout << nombre << "Has muerto" << endl;
    //Falta aún definir el sprite de cuánto muere.
}

// Método para actualizar la posición en el eje Y y simular la gravedad.
void Personaje::actualizarFisica(float deltaTime) {
    if (salto) {
        // Actualizar la posición Y con la velocidad actual.
        posY += velocidadY * deltaTime;
        velocidadY -= 9.8 * deltaTime; // Simular la gravedad.
        if (posY <= 0) {
            posY = 0;  // El personaje toca el suelo.
            salto = false;
            velocidadY = 0; // Detener la caída.
        }
    }
}
//Función friend, esta es encargada de alterar la vida del personaje enemigo,
//esta alterará la vida del personaje.
void atacar(Personaje& atacado){
    atacado.vida_Personaje -=5;
}
