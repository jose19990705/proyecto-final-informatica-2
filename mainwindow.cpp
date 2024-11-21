#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Jugador.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->score->display(0);
    ui->puntaje_jugador->setText("Tu puntaje");

    // title_pic = new QGraphicsScene;
    // title_pic->setSceneRect(0,0,ui->title->width(),ui->title->height());
    // title_pic->setBackgroundBrush((QPixmap(":/new/prefix1/personajes/titulo_escena.png").scaledToWidth(ui->title->width())));
    //  ui->title->setScene(title_pic);

    //Acaaaaaaaaaaaaaaaaaaaaaa
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0, ui->game_screen->width() - 5, ui->game_screen->height() - 5);
    scene->setBackgroundBrush(QPixmap(":/Escenarios/Escenario1").scaled(ui->game_screen->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    Jugador * jugador = new Jugador("Homero", 100, 20, QString::fromStdString(":/Sprites/SpritesPersonajes/HomeroDerecha.jpg"), 5, 0, 200, 200);
    scene->addItem(jugador);

    ui->game_screen->setScene(scene);
    ui->game_screen->setFocus();

    // Crear un temporizador para actualizar la escena (y llamar a advance) cada 16ms (60 FPS)
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);  // Llamar a advance en cada timeout
    timer->start(16);  // Esto actualiza la escena aproximadamente 60 veces por segundo
}

MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}
