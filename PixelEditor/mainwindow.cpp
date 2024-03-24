#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
//#include "framewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Window title
    setWindowTitle("Segmentation Fault Pixel Editor");

    //Pencil Button Image
    QPixmap pencilPixmap(":/Images/pencil.png");
    QSize pencilImageSize(50,50);
    ui->PencilButton->setIcon(pencilPixmap);
    ui->PencilButton->setIconSize(pencilImageSize);

    //Eraser Button Image
    QPixmap eraserPixmap(":/Images/eraser.png");
    QSize eraserImageSize(40,40);
    ui->EraserButton->setIcon(eraserPixmap);
    ui->EraserButton->setIconSize(eraserImageSize);

}

MainWindow::~MainWindow()
{
    delete ui;
}

