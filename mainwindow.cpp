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
    //atributos para los logros obtenidos.
    connect(ui->nivel1, &QPushButton::clicked, this, &MainWindow::seleccionarNivel1);
    connect(ui->nivel2, &QPushButton::clicked, this, &MainWindow::seleccionarNivel2);
    connect(ui->nivel3, &QPushButton::clicked, this, &MainWindow::seleccionarlogros);



    sin_daño=true;
    sin_poder=true;

    temporizador_logros= new QTimer();
    // Crear la escena
    escena = new QGraphicsScene(this);

    // Ajustar la escena y el Q Graphicsview
    escena->setSceneRect(0, 0, ui->escenario->width() - 5, ui->escenario->height() - 5); // Ajustar los bordes de la escena

    ui->escenario->setScene(escena);

    //Fondo menú

    QPixmap fondoMenu(R"(://imagenes/fondo_menu.jpg)");
    if (!fondoMenu.isNull()) {
        QGraphicsPixmapItem* fondoItem = escena->addPixmap(fondoMenu);
        fondoItem->setPos(0, 0);  // Posicionar el fondo en la esquina superior izquierda
        // Asegurarse de que el fondo esté detrás de todos los demás elementos
        fondoItem->setZValue(-1);
    } else {
        qDebug() << "Error: No se pudo cargar la imagen de fondo del menú.";
    }

// aca debe de ir con el widget, este le dará el valor a opcion!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   // opcion=0;

//Temporizador para verificar los logros.
    connect(temporizador_logros, &QTimer::timeout, this, &MainWindow::verificar_logros);
    temporizador_logros->start(20);


   // opciones para el menú de juego
    //-------------------------------------------------------------------------------------------------------------




    temporizador= new QTimer;
    connect(temporizador, &QTimer::timeout, this, [=]() {
        Homero->set_posicion(); // Actualizar posición según la gravedad y el salto
    });
    temporizador->start(16);

    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout, this, &MainWindow::actualizarMovimiento);
    temporizadorMovimiento->start(16); // Actualizar 60 veces por segundo (~16 ms)



    verificar_logros();
    poner_logro();
  //  ~MainWindow();
}

MainWindow::~MainWindow() {
    delete Homero;
    delete escena;
    delete temporizador;
    delete temporizadorMovimiento;
    delete Burns;
    delete temporizador_logros;
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
        Homero->actualizar_sprite(R"(://imagenes/Sprite sheet derecha proyecto final info 2.png)");
        QThread::msleep(10);
        Homero->sprite_derecha(512, 64);
    }
    if (teclasPresionadas.contains(Qt::Key_A)) {
        Homero->setX(Homero->x() - 10);
        Homero->actualizar_sprite(R"(://imagenes/Sprite sheet izquierda proyecto final info 2.png)");
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
//----------------------------------------------------------------
void MainWindow::verificar_logros(){
    if(Homero->get_estado_poder()){
        sin_poder=false;
    }
    if(Homero->daño_vida()){
        sin_daño=false;
    }
}

void MainWindow::poner_logro() {
    try {
        std::ofstream archivo_logros("logros.txt", std::ios::app); // Abrir en modo añadir

        if (!archivo_logros.is_open()) {
            throw std::ios_base::failure("Error al abrir el archivo de logros.");
        }

        if (sin_daño) {
            archivo_logros << "No recibiste daños en la última partida. ¡Muy bien!\n";
        } else {
            archivo_logros << "Recibiste daños, logro no otorgado.\n";
        }

        if (sin_poder) {
            archivo_logros << "No usaste el poder en la última partida. ¡Muy bien!\n";
        } else {
            archivo_logros << "Usaste el poder, logro no otorgado.\n";
        }

        archivo_logros.close();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Ocurrió un error desconocido al escribir en el archivo." << std::endl;
    }
}

void MainWindow::imprimir_logros() {
    try {
        std::ifstream archivo_logros("logros.txt"); // Abrir el archivo en modo lectura

        if (!archivo_logros.is_open()) {
            throw std::ios_base::failure("Error al abrir el archivo de logros.");
        }

        std::string linea;
        std::cout << "--- Logros Registrados ---" << std::endl;

        while (std::getline(archivo_logros, linea)) {
            std::cout << linea << std::endl;
        }

        archivo_logros.close();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Ocurrió un error desconocido al leer el archivo." << std::endl;
    }
}


/*
void MainWindow::menu(){
    switch (opcion) {
    case 1:
        // Creacción del personaje principal (Homero)
        Homero = new Heroe(64, 64, 0, 0, 30, 350, R"(://imagenes/Sprite sheet derecha proyecto final info 2.png)",
                           false, 100, 10, 80, 80, escena,2);
        escena->addItem(Homero);

        // Creamos punteros de villanos y los agregamos a un QList, y los ponemos en el escenario
        for (int i = 0; i < 6; ++i) {
            QPoint coordenadasVillano = Villano::generarVillanosEscenario1(Homero->x());
            // Ancho y alto del sprite, coordenadas dentro de la hoja de sprite, posición en el escenario, dirección en memoria del sprite, estado de salto, vida, velocidad horizontal, ancho y alto del personaje en el escenario

            Villano* nuevoVillano = new Villano(100, 100, 0, 0, coordenadasVillano.x(), coordenadasVillano.y(), R"(://imagenes/rata_sin_fondo.png)", false, 10, 2, 80, 80);
            villanosEscenario1.append(nuevoVillano);
            escena->addItem(nuevoVillano);
        }
        Burns=nullptr;
        break;
    case 2:
        Homero = new Heroe(64, 64, 0, 0, 30, 350, R"(://imagenes/Sprite sheet derecha proyecto final info 2.png)",
                           false, 100, 10, 80, 80, escena,5);
        for (int i = 0; i < 6; ++i) {
            QPoint coordenadasVillano = Villano::generarVillanosEscenario1(Homero->x());
            // Ancho y alto del sprite, coordenadas dentro de la hoja de sprite, posición en el escenario, dirección en memoria del sprite, estado de salto, vida, velocidad horizontal, ancho y alto del personaje en el escenario

            Villano* nuevoVillano = new Villano(100, 100, 0, 0, coordenadasVillano.x(), coordenadasVillano.y(), R"(://imagenes/rata_sin_fondo.png)", false, 10, 2, 80, 80);
            villanosEscenario1.append(nuevoVillano);
            escena->addItem(nuevoVillano);
        }
        //--------------------------acá se inicializarán los atributos de burns.-------------------------------------------------------------------------
        Burns= nullptr;
        break;



    case 3:
        this->imprimir_logros();
        break;
    default:
        break;
    }

}
*/

void MainWindow::menu(){
    // Liberar memoria de Homero y Burns antes de asignar nuevos valores
    if (Homero) {
        escena->removeItem(Homero);
        delete Homero;
        Homero = nullptr;
    }

    if (Burns) {
        escena->removeItem(Burns);
        delete Burns;
        Burns = nullptr;
    }

    // Liberar memoria de los villanos
    for (Villano* villano : villanosEscenario1) {
        escena->removeItem(villano);
        delete villano;
    }
    villanosEscenario1.clear(); // Vaciar la lista

    // Ahora creamos nuevos objetos según el nivel
    switch (opcion) {
    case 1:
        Homero = new Heroe(64, 64, 0, 0, 30, 350, R"(://imagenes/Sprite sheet derecha proyecto final info 2.png)",
                           false, 100, 10, 80, 80, escena,2);
        escena->addItem(Homero);

        for (int i = 0; i < 6; ++i) {
            QPoint coordenadasVillano = Villano::generarVillanosEscenario1(Homero->x());
            Villano* nuevoVillano = new Villano(100, 100, 0, 0, coordenadasVillano.x(), coordenadasVillano.y(), R"(://imagenes/rata_sin_fondo.png)", false, 10, 2, 80, 80);
            villanosEscenario1.append(nuevoVillano);
            escena->addItem(nuevoVillano);
        }
        Burns = nullptr;
        break;

    case 2:
        Homero = new Heroe(64, 64, 0, 0, 30, 350, R"(://imagenes/Sprite sheet derecha proyecto final info 2.png)",
                           false, 100, 10, 80, 80, escena,5);
        escena->addItem(Homero);

        for (int i = 0; i < 6; ++i) {
            QPoint coordenadasVillano = Villano::generarVillanosEscenario1(Homero->x());
            Villano* nuevoVillano = new Villano(100, 100, 0, 0, coordenadasVillano.x(), coordenadasVillano.y(), R"(://imagenes/rata_sin_fondo.png)", false, 10, 2, 80, 80);
            villanosEscenario1.append(nuevoVillano);
            escena->addItem(nuevoVillano);
        }
        Burns = nullptr;
        break;

    case 3:
        this->imprimir_logros();
        break;
    default:
        break;
    }
}


void MainWindow::seleccionarNivel1() {
    opcion = 1;
    menu(); // Llama a la función que inicia el juego con la opción seleccionada
}

void MainWindow::seleccionarNivel2() {
    opcion = 2;
    menu(); // Llama a la función que inicia el juego con la opción seleccionada
}

void MainWindow::seleccionarlogros() {
    opcion = 3;
    menu(); // Llama a la función que inicia el juego con la opción seleccionada
}
