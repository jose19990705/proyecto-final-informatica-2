#include "mainwindow.h"
#include "ui_mainwindow.h"

// Contenedor QList para los punteros de los villanos del escenario 1
static QList <Villano*> villanosEscenario1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1280, 720);    // Redimensionamos el tamaño del mainWindow

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

    // Creacción del personaje principal (Homero)
    Homero = new Heroe(64, 64, 0, 0, 30, 350, R"(C:\Users\Diego Andrés Pedrozo\Downloads\Sprite sheet derecha proyecto final info 2.png)", false, 100, 10, 80, 80, escena);
    escena->addItem(Homero);

    // Creamos punteros de villanos y los agregamos a un QList, y los ponemos en el escenario
    for (int i = 0; i < 6; ++i) {
        QPoint coordenadasVillano = Villano::generarVillanosEscenario1(Homero->x());
        // Ancho y alto del sprite, coordenadas dentro de la hoja de sprite, posición en el escenario, dirección en memoria del sprite, estado de salto, vida, velocidad horizontal, ancho y alto del personaje en el escenario

        Villano* nuevoVillano = new Villano(100, 100, 0, 0, coordenadasVillano.x(), coordenadasVillano.y(), R"(C:\Users\Diego Andrés Pedrozo\Downloads\Sprites proyecto final info 2\Rata irradiada camina izquierda.png)", false, 10, 2, 80, 80);
        villanosEscenario1.append(nuevoVillano);
        escena->addItem(nuevoVillano);
    }

    // Liberar la memoria de los punteros al destruir los villanos
    /*for (auto villano : villanosEscenario1) {
        delete villano; // Liberar la memoria de los punteros
    }
    villanosEscenario1.clear(); // Limpiar la lista*/
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

    if (i->key() == Qt::Key_F) {
        Homero->activar_Poder(); // Activar el poder con la tecla F
    }
    else if (i->key() == Qt::Key_G) {
        Homero->desactivar_Poder(); // Desactivar el poder con la tecla G
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *i) {
    teclasPresionadas.remove(i->key()); // Eliminar la tecla soltada del conjunto

    // No desactivamos el poder al soltar la tecla F
}

void MainWindow::actualizarMovimiento() {
    if (!Homero->get_moverse()) {
        return; // No mover al jugador si el poder está activo
    }
    if (teclasPresionadas.contains(Qt::Key_D)) {
        Homero->setX(Homero->x() + 10);
        Homero->actualizar_sprite(R"(C:\Users\Diego Andrés Pedrozo\Downloads\Sprite sheet derecha proyecto final info 2.png)");
        QThread::msleep(10);
        Homero->sprite_derecha(512, 64);
    }
    if (teclasPresionadas.contains(Qt::Key_A)) {
        Homero->setX(Homero->x() - 10);
        Homero->actualizar_sprite(R"(C:\Users\Diego Andrés Pedrozo\Downloads\Sprite sheet izquierda proyecto final info 2.png)");
        QThread::msleep(10);
        Homero->sprite_izquierda(192, 64);
    }
    if (teclasPresionadas.contains(Qt::Key_Space)) {
        Homero->saltar();
    }
    for (auto villano : villanosEscenario1) {
        villano->movimiento_villano(Homero->x());
    }
}

