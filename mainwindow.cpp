#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear la escena
    escena = new QGraphicsScene(this);

    // Ajustar la escena y el Q Graphicsview

    escena->setSceneRect(0, 0, ui->escenario->width() - 5, ui->escenario->height() - 5); // Ajustar los bordes de la escena

    ui->escenario->setScene(escena);
    temporizador= new QTimer;
    connect(temporizador, &QTimer::timeout, this, [=]() {
        Homero->set_posicion(); // Actualizar posición según la gravedad y el salto
    });
    temporizador->start(16);

    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout, this, &MainWindow::actualizarMovimiento);
    temporizadorMovimiento->start(16); // Actualizar 60 veces por segundo (~16 ms)


    // Crear el personaje y añadirlo a la escena
    Homero = new Personaje(100, 100, 0, 0, 30, 350, ":/imagenes/caminar_sin_fondo.png", false,20,100,5);
    escena->addItem(Homero);

    // Ajustar posición inicial del personaje
    Homero->setPos(30, 350); // Cambiar según dónde quieras que aparezca






}

MainWindow::~MainWindow() {
    delete Homero;
    delete escena;
    delete temporizador;
    delete temporizadorMovimiento;
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *i) {
    teclasPresionadas.insert(i->key()); // Agregar la tecla presionada al conjunto
}

void MainWindow::keyReleaseEvent(QKeyEvent *i) {
    teclasPresionadas.remove(i->key()); // Eliminar la tecla soltada del conjunto
}




void MainWindow::actualizarMovimiento() {
    if (teclasPresionadas.contains(Qt::Key_D)) {
        Homero->setX(Homero->x() + 10);
        Homero->actualizar_pixmap(":/imagenes/caminar_sin_fondo.png");
        QThread::msleep(10);
        Homero->sprite_derecha();
    }
    if (teclasPresionadas.contains(Qt::Key_A)) {
        Homero->setX(Homero->x() - 10);
        Homero->actualizar_pixmap("://imagenes/caminar_izq_sin_fondo.png");
        QThread::msleep(10);
        Homero->sprite_derecha();
    }
    if (teclasPresionadas.contains(Qt::Key_Space)) {
        Homero->saltar();
    }
}



