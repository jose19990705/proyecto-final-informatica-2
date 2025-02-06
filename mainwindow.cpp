




//----------------------------------------------------
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

    if (!ui->nivel1 || !ui->nivel2 || !ui->nivel3) {
        qDebug() << "Error: Alguno de los botones (nivel1, nivel2, nivel3) es nullptr.";
        return;
    }
    ui->menu_principal->hide();
    ui->label_poder->hide();
    ui->numero_poder->hide();
    connect(ui->nivel1, &QPushButton::clicked, this, &MainWindow::seleccionarNivel1);
    connect(ui->nivel2, &QPushButton::clicked, this, &MainWindow::seleccionarNivel2);
    connect(ui->nivel3, &QPushButton::clicked, this, &MainWindow::seleccionarlogros);
    connect(ui->menu_principal,&QPushButton::clicked,this,&MainWindow::volver_menu);
//----------------------------------------------------------------------------------
    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout, this, &MainWindow::actualizarMovimiento);
    temporizadorMovimiento->start(16); // Actualizar 60 veces por segundo (~16 ms)

    // Creamos el temporizador para la inmunidad
    temporizadorInmunidad = new QTimer(this);
    connect(temporizadorInmunidad, &QTimer::timeout, this, [&]() {
        if (Homero) {
            Homero->desactivar_inmunidad();
            inmunidadActiva = false;
        }
    });

//--------------------------------------------------------------------------------

    sin_daño=true;
    sin_poder=true;
    //colision= new QTimer(this);
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
    Homero=new Heroe(100,100,0,0,30,350, ":/imagenes/caminar_sin_fondo.png",false,100,10,70,70,escena,2);



    temporizador= new QTimer;
    connect(temporizador, &QTimer::timeout, this, [=]() {
        Homero->set_posicion(); // Actualizar posición según la gravedad y el salto
    });
    temporizador->start(16);

    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout, this, &MainWindow::actualizarMovimiento);
    temporizadorMovimiento->start(16); // Actualizar 60 veces por segundo (~16 ms)



    //Temporizador para verificar los logros.
    connect(temporizador_logros, &QTimer::timeout, this, &MainWindow::verificar_logros);
    temporizador_logros->start(20);



 /*







   // opciones para el menú de juego
    //-------------------------------------------------------------------------------------------------------------








    verificar_logros();
    poner_logro();

*/
    verificar_logros();
    poner_logro();
}





MainWindow::~MainWindow() {
    qDebug() << "Cerrando ventana y liberando memoria...";

    if (Homero) {
        escena->removeItem(Homero);

    }

    if (Burns) {
        escena->removeItem(Burns);
        delete Burns;
        Burns = nullptr;
    }

    for (Villano* villano : villanosEscenario1) {
        if (villano) {
            escena->removeItem(villano);
            delete villano;
        }
    }
    villanosEscenario1.clear();

    delete escena;
    delete temporizador;
    delete temporizadorMovimiento;
    delete temporizador_logros;
    delete temporizadorInmunidad;

    delete ui;  // Esto elimina todo el UI
}

void MainWindow::keyPressEvent(QKeyEvent *i) {
    teclasPresionadas.insert(i->key()); // Agregar la tecla presionada al conjunto

    if (i->key() == Qt::Key_F) {
        Homero->activar_Poder(); // Activar el poder con la tecla F
        if(Homero->get_cant_habilidad()>=0){
            ui->numero_poder->display(Homero->get_cant_habilidad());


        }
    }
    else if (i->key() == Qt::Key_G) {
        Homero->desactivar_Poder(); // Desactivar el poder con la tecla G
    }
    else if (i->key() == Qt::Key_S && !disparando && Proyectil::proyectiles_lanzados < 2) {
        disparando = true;
        if (Homero->get_direccion() == true) {
            Proyectil* proyectil = new Proyectil(Homero->x(), Homero->y(), 10, true, Homero->get_direccion()); // El proyectil se lanza a la derecha
            escena->addItem(proyectil);
        } else {
            Proyectil* proyectil = new Proyectil(Homero->x(), Homero->y(), -10, true, Homero->get_direccion()); // El proyectil se lanza a la izquierda
            escena->addItem(proyectil);
        }
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *i) {
    teclasPresionadas.remove(i->key()); // Eliminar la tecla soltada del conjunto
    if (i->key() == Qt::Key_S) {
        disparando = false;  // Permitir disparar nuevamente cuando se suelta la tecla
    }

    // No desactivamos el poder al soltar la tecla F
}


void MainWindow::actualizarMovimiento() {
    if (!Homero->get_moverse()) {
        return; // No mover al jugador si el poder está activo
    }
    if (teclasPresionadas.contains(Qt::Key_D)) {
        Homero->setX(Homero->x() + 10);
        Homero->actualizar_sprite(R"(://imagenes/Sprite sheet derecha proyecto final info 2.png)");
        Homero->avanza();
        QThread::msleep(10);
        Homero->sprite_derecha(512, 64);
    }
    if (teclasPresionadas.contains(Qt::Key_A)) {
        Homero->setX(Homero->x() - 10);
        Homero->actualizar_sprite(R"(://imagenes/Sprite sheet izquierda proyecto final info 2.png)");
        Homero->retrocede();
        QThread::msleep(10);
        Homero->sprite_izquierda(192, 64);
    }
    if (teclasPresionadas.contains(Qt::Key_Space)) {
        Homero->saltar();
    }
    for (auto item : escena->items()) {
        Proyectil* proyectil = dynamic_cast<Proyectil*>(item);
        if (proyectil) {
            proyectil->mover();  // Llamamos al método mover de cada proyectil
            // Verificamos si el proyectil ha salido de la escena o ha impactado con un personaje
            if (proyectil->estaFueraDeLaEscena() || proyectil->impactaPersonaje()) {
                escena->removeItem(proyectil);
                delete proyectil;
            }
        }
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



void MainWindow::menu() {

    switch (opcion) {
    case 1:
        Homero = new Heroe(64, 64, 0, 0, 30, 350, R"(://imagenes/Sprite sheet derecha proyecto final info 2.png)",
                           false, 100, 10, 80, 80, escena,2);
        escena->addItem(Homero);

        for (int i = 0; i < 6; ++i) {
            QPoint coordenadasVillano = Villano::generarVillanosEscenario1(Homero->x());
            Villano* nuevoVillano = new Villano(100, 100, 0, 0, coordenadasVillano.x(), coordenadasVillano.y(), R"(://imagenes/rata_sin_fondo.png)", false, 10, 1, 80, 80,10);
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
            Villano* nuevoVillano = new Villano(64,64,208,2433, coordenadasVillano.x(), coordenadasVillano.y(), R"(://imagenes/Sprite sheet izquierda proyecto final info 2.png)", false, 10, 8, 80, 80,10);
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

void MainWindow::volver_menu(){
    QPixmap fondoMenu(R"(://imagenes/fondo_menu.jpg)");
    if (!fondoMenu.isNull()) {
        QGraphicsPixmapItem* fondoItem = escena->addPixmap(fondoMenu);
        fondoItem->setPos(0, 0);  // Posicionar el fondo en la esquina superior izquierda
        // Asegurarse de que el fondo esté detrás de todos los demás elementos
        fondoItem->setZValue(-1);
    } else {
        qDebug() << "Error: No se pudo cargar la imagen de fondo del menú.";
    }
    escena->removeItem(Homero);

    for (Villano* villano : villanosEscenario1) {
        if (villano) {
            escena->removeItem(villano);
            //delete villano;
        }
    }


    ui->nivel1->show();
    ui->nivel2->show();
    ui->nivel3->show();
    ui->label_poder->hide();
    ui->numero_poder->hide();
}
void MainWindow::seleccionarNivel1() {



    opcion = 1;
    qDebug()<<"entro a 1";
    menu(); // Llama a la función que inicia el juego con la opción seleccionada
    ui->nivel1->hide();
    ui->nivel2->hide();
    ui->nivel3->hide();
    ui->label_poder->show();
    ui->numero_poder->show();
    ui->numero_poder->display(Homero->get_cant_habilidad());
    ui->menu_principal->show();
    //////////////////////////////////////////////////////////////////

    QPixmap fondoMenu(R"(://imagenes/fondo_juego_1.png)");
    if (!fondoMenu.isNull()) {
        QGraphicsPixmapItem* fondoItem = escena->addPixmap(fondoMenu);
        fondoItem->setPos(0, 0);  // Posicionar el fondo en la esquina superior izquierda
        // Asegurarse de que el fondo esté detrás de todos los demás elementos
        fondoItem->setZValue(-1);
    } else {
        qDebug() << "Error: No se pudo cargar la imagen de fondo del menú.";
    }

}

void MainWindow::seleccionarNivel2() {
    opcion = 2;
     qDebug()<<"entro a 2";
    menu(); // Llama a la función que inicia el juego con la opción seleccionada
     ui->nivel1->hide();
     ui->nivel2->hide();
     ui->nivel3->hide();
     ui->label_poder->show();
     ui->numero_poder->show();
     ui->menu_principal->show();
     ui->numero_poder->display(Homero->get_cant_habilidad());
     ui->menu_principal->show();

}

void MainWindow::seleccionarlogros() {
    opcion = 3;
     qDebug()<<"entro a 3";
    menu(); // Llama a la función que inicia el juego con la opción seleccionada
     ui->nivel1->hide();
     ui->nivel2->hide();
     ui->nivel3->hide();
     ui->menu_principal->show();
     this->imprimir_logros();
}

// Método para verificar las colisiones entre el héroe y los villanos
void MainWindow::verificarColisionesHeroeVillanos(Heroe* heroe){
    if (!heroe) return;  // Comprobar que el puntero no sea nulo
    if (inmunidadActiva) return;  // Para no crear varios temporizadores

    // Obtenemos los elementos que colisionan con el héroe
    QList<QGraphicsItem*> colisiones = heroe->collidingItems();

    // Verificamos si el héroe ha colisionado con algún villano
    for (auto& item : colisiones) {
        Villano* villano = dynamic_cast <Villano*> (item);  // Intentamos convertir el objeto colisionante en villano
        if (villano) {
            heroe->activar_inmunidad();
            heroe->restar_vida(villano->get_danio());
            if (heroe->get_vida() <= 0){
                escena->removeItem(heroe);
                delete heroe;
                qDebug() << "Homero muere";     // --------> Aqui muere, llamar a Menu
                this->volver_menu();
            }

            //qDebug() << "Vida del personaje: " <<
            inmunidadActiva = true;

            // Iniciar el temporizador de inmunidad, lo cual desactivará la inmunidad después de 1 segundo
            temporizadorInmunidad->start(1000);  // 1 segundo
        }
    }
}
