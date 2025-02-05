#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "heroe.h"
#include "villano.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QThread>
#include <QTimer>
#include "villano.h"
#include "heroe.h"
#include <vector>
#include <fstream>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *i);
    void keyReleaseEvent(QKeyEvent *i);
    void actualizarMovimiento();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;  // Escena para contener los elementos gráficos
    QTimer *temporizador;
    Heroe *Homero;       // Personaje principal
    vector<Villano*> villanos;
    unsigned short opcion;
    Villano *Burns;
    bool sin_daño,sin_poder;

private:
    QSet<int> teclasPresionadas; // Para rastrear teclas activas
    QTimer *temporizadorMovimiento; // Para manejar el movimiento continuo
    QTimer *temporizador_logros;


private slots:
    void seleccionarNivel1();
    void seleccionarNivel2();
    void seleccionarlogros();
    void menu();


public:
    void verificar_logros();
    void logros();
    void poner_logro();
    void imprimir_logros();

};

#endif // MAINWINDOW_H
