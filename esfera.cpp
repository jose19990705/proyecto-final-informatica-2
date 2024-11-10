#include "esfera.h"
#include <iostream>
#include <cmath>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPainter>
#include <QThread>
//#include <string>
// yaa
esfera::esfera(float carga_electrica_, float radio_, float masa_,float *arreglo_velocidades_)
    :carga_electrica(carga_electrica_),radio(radio_),masa(masa_), arreglo_velocidades(arreglo_velocidades_){
    pixmap_esfera= new QPixmap("dirección o ruta de la imagen de la esfera");
}
esfera::~esfera(){
    delete pixmap_esfera;
}
//Métodos de la clase.
float esfera::get_carga_electrica(){
    return carga_electrica;
}
unsigned short esfera::get_masa(){
    return masa;
}

unsigned short esfera::get_radio(){
    return radio;
}
void esfera::set_velocidad(float carga_homero, float* distancia,
                             unsigned int *tiempo) {
    // Constante de Coulomb
    unsigned long long K = 9000000000;
    // Obtener la masa de la esfera
    unsigned short m = get_masa();
    float carga_esfera = get_carga_electrica();
    float velocidad=0;
    for (unsigned int i = 0; i < 500; i++) {
        // Distancia en el tiempo actual
       // float distancia = distancia_array[i];

        //Fuerza usando ley de Coumlob.
        float F = -K * carga_esfera * carga_homero / ((*(distancia+i))*(*(distancia+i)));
        // Cálculo de la aceleración de la masa.
        float aceleracion = F / m;

        // actualizacion de la velocidad, velocidad= aceleracion * tiempo[i]
        // Actualizamos la velocidad
        velocidad += aceleracion *(*(tiempo+i));

        // Guardamos la velocidad en el arreglo
        *(arreglo_velocidades+i) = velocidad;
    }

}

float * esfera::get_velocidades(){
    return arreglo_velocidades;
}

