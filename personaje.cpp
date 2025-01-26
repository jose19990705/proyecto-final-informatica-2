#include "personaje.h"

Personaje::Personaje(unsigned short w_, unsigned short h_, short x_s_, short y_s_,
                     short posx_, short posy_, const QString &direccion_,
                     bool salto_,unsigned short m_,short vida_,unsigned short fuerza_ataque_)
    : w(w_), h(h_), x_s(x_s_), y_s(y_s_), posx(posx_), posy(posy_),
    salto(salto_),m(m_),vida(vida_),fuerza_ataque(fuerza_ataque_) {
    pixmap = new QPixmap(direccion_);

    v0y = 0;  // Sin movimiento inicial en el eje Y
    gravedad = 10;         // Gravedad constante que afectará al personaje

    // Establecer el pixmap inicial
    setPixmap(pixmap->copy(x_s, y_s, w, h).scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

Personaje::~Personaje() {
    delete pixmap;
}

void Personaje::sprite_derecha() {
    x_s += 100;
    if (x_s >= 800) {
        x_s = 0;
    }
    setPixmap(pixmap->copy(x_s, y_s, w, h).scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Personaje::sprite_izquierda(){
    x_s -= 100;
    if (x_s <= 0) {
        x_s = 800;
    }
    setPixmap(pixmap->copy(x_s, y_s, w, h).scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

short Personaje::get_posx(){
    return posx;
}
short Personaje::get_posy(){
    return posy;
}




//Sprite para el movimiento del personaje a la izquierda.

void Personaje::actualizar_pixmap(const QString &direccion_){
    pixmap->load(direccion_);
}



//Control del salto y atributos encargados de ello.
void Personaje::saltar() {
    if (!salto) {               // Solo permite saltar si no está en el aire
        v0y = -50; // Velocidad inicial hacia arriba
        salto = true;            // Ahora el personaje está en el aire
    }
}

void Personaje::set_posicion() {

    float delta_t = 0.3; // Tiempo en segundos (16 ms)

    // Calcular nueva velocidad vertical (v = v0 + a * t)
    v0y += gravedad * delta_t;

    // Calcular nueva posición vertical (y = y0 + v0 * t + 0.5 * a * t^2)
    posy += v0y * delta_t + 0.5 * gravedad * delta_t * delta_t;

    // Actualizar gráficamente la posición del personaje
    setY(posy);

    // Si el personaje toca el suelo, detener el salto
    if (posy >= 350) {
        posy = 350;            // Ajustar al nivel del suelo
        v0y = 0; // Detener movimiento vertical
        salto = false;         // Permitir que salte nuevamente
    }

}

void Personaje::set_fuerza(unsigned short magnitud_fuerza){
    fuerza_ataque=magnitud_fuerza;
}
void Personaje::restar_vida(unsigned short daño){
    vida-=daño;
}


//Método para el retroceso del golpe.
void Personaje::retroceso(unsigned short fuerza_golpe, bool golpe_derecha) {
    // Calcular aceleración inicial usando F = m * a
    float aceleracion = static_cast<float>(fuerza_golpe/ m) ; // m es la masa del personaje
    float friccion = 10.0; // Coeficiente de fricción que reduce la velocidad
    float velocidad = golpe_derecha ? aceleracion : -aceleracion; // Velocidad inicial basada en la dirección
    float dt = 0.1; //Delta de tiempo para los eventos de la fuerza. Se debe aún revisar sus efectos.

    // Crear un temporizador para animar el retroceso
    QTimer *temporizadorRetroceso = new QTimer(this);

    connect(temporizadorRetroceso, &QTimer::timeout, this, [=]() mutable {
        // Reducir la velocidad por la fricción
        if (velocidad > 0) {
            velocidad -= friccion * dt;
            if (velocidad < 0) velocidad = 0; // Detener el movimiento hacia la derecha
        } else if (velocidad < 0) {
            velocidad += friccion * dt;
            if (velocidad > 0) velocidad = 0; // Detener el movimiento hacia la izquierda
        }

        // Actualizar la posición del personaje
        setX(x() + velocidad * dt);

        // Detener el temporizador si la velocidad es 0
        if (velocidad == 0) {
            temporizadorRetroceso->stop();
            temporizadorRetroceso->deleteLater(); // Liberar memoria del temporizador
        }
    });

    // Iniciar el temporizador para actualizar cada 20 ms. De esta manera se controla el movimiento del retroceso.
    temporizadorRetroceso->start(20);
}









