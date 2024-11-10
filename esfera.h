#ifndef ESFERA_H
#define ESFERA_H
#include <QPixmap>
//clase de la esfera del poder.
class esfera
{
private:
    float carga_electrica;
    float radio;
    float masa;
    float *arreglo_velocidades;
    QPixmap *pixmap_esfera;

public:
    esfera(float carga_electrica_, float radio_, float masa_,float *arreglo_velocidades_);
    ~esfera();
    float get_carga_electrica();
    float *get_velocidades();
    unsigned short get_radio();
    unsigned short get_masa();
    void set_velocidad(float carga_homero, float* distancia,
                               unsigned int *tiempo);
};

#endif // ESFERA_H
