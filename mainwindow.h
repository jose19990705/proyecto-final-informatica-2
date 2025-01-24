#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "personaje.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QThread>
#include <QTimer>

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
    Personaje *Homero;       // Personaje principal
private:
    QSet<int> teclasPresionadas; // Para rastrear teclas activas
    QTimer *temporizadorMovimiento; // Para manejar el movimiento continuo

};

#endif // MAINWINDOW_H
