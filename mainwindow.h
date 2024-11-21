#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsItem>
#include <QRectF>
#include <QtDebug>
#include <QKeyEvent>
//#include <QtmediaPlayer>
#include <QMessageBox>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene *scene;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
