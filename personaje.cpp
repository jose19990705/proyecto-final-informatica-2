#include "personaje.h"

Personaje::Personaje (unsigned short wSprite_, unsigned short hSprite_, short x_sprite_, short y_sprite_, short posx_, short posy_, const QString &direccion_,
                     bool salto_,short vida_, unsigned short velocidadX_, unsigned short wPersonaje_, unsigned short hPersonaje_)
    : wSprite(wSprite_), hSprite(hSprite_), x_sprite(x_sprite_), y_sprite(y_sprite_), posx(posx_), posy(posy_), salto(salto_), vida(vida_),
    velocidadX(velocidadX_), wPersonaje(wPersonaje_), hPersonaje(hPersonaje_) {

    sprite = new QPixmap(direccion_);

    v0y = 0;            // Sin movimiento inicial en el eje Y, sobre el suelo
    gravedad = 10;      // Gravedad constante que afecta al personaje

    // Establecer el pixmap inicial
    setPixmap(sprite->copy(x_sprite, y_sprite, wSprite, hSprite).scaled(wPersonaje_, hPersonaje_, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setPos(posx_, posy_);  // Posición inicial donde aparecerá el personaje en la escena
}

Personaje::~Personaje() {
    delete sprite;
}

// Recibe las coordenadas que delimitan el acceso a la región para la animación del personaje
void Personaje::sprite_derecha(short x_sprite_max, short y_sprite) {
    x_sprite += 64;
    if (x_sprite >= x_sprite_max) {
        x_sprite = 0;
    }
    setPixmap(sprite->copy(x_sprite, y_sprite, wSprite, hSprite).scaled(wPersonaje, hPersonaje, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// Recibe las coordenadas que delimitan el acceso a la región para la animación del personaje
void Personaje::sprite_izquierda(short x_sprite_min, short y_sprite) {
    if (x_sprite <= x_sprite_min) {
        x_sprite = 704;
    }
    x_sprite -= 64;
    setPixmap(sprite->copy(x_sprite, y_sprite, wSprite, hSprite).scaled(wPersonaje, hPersonaje, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

unsigned short Personaje::get_velocidadX() {
    return velocidadX;
}

short Personaje::get_posx(){
    return posx = x();
}
short Personaje::get_posy(){
    return posy = y();
}

// Actualiza el cambio de hoja de sprites al haber un cambio de dirección izq - der
void Personaje::actualizar_sprite(const QString &direccion_){
    sprite->load(direccion_);
}

//Control del salto y atributos encargados de ello
void Personaje::saltar() {
    if (!salto) {        // Solo permite saltar si no está en el aire
        v0y = -50;       // Velocidad inicial hacia arriba
        salto = true;    // Ahora el personaje está en el aire
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
        posy = 350;        // Ajustar al nivel del suelo
        v0y = 0;           // Detener movimiento vertical
        salto = false;     // Permitir que salte nuevamente
    }
}

void Personaje::restar_vida(unsigned short danio){
    vida -= danio;
}
