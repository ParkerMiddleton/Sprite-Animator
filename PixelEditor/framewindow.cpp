#include "framewindow.h"
#include "qpixmap.h"
#include <QPainter>
#include <QDebug>
#include <QSizePolicy>
#include "mainwindow.h"

//Constructor
FrameWindow::FrameWindow(QWidget *parent) :
    QLabel(parent), pressed(0)
{
    connect(dynamic_cast<MainWindow*>(parent), &MainWindow::colorChanged, this, &FrameWindow::setDrawingColor);

    /*
    Known Issue: We want the label contained within the gridLayout object to match the height and width
    of its parent container. As of now, this isnt working properly. Hard coded pixmap sizes are used below,
    but we should be able to use this->height() and this->width() respectively.
    */

    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);


    // remove when bug is fixed.
    qDebug() << sizePolicy();
    qDebug() << height();
    qDebug() << width();


    int frameWidth = 750;
    int frameHeight= 500;

    // Fill the label with an array of transparent pixels
    pixmap = new QPixmap(frameWidth, frameHeight); // random values here are of the gridlayout's height and width

    //Fill the map with transparent pixels
    pixmap->fill(Qt::transparent);

    //Tells the QPainter object that this is the object we are drawing.
    QPainter painter (pixmap);

    //Draw the pixels
    int checkerSize = 10;
    for (int y = 0; y < frameHeight; y += checkerSize) { // height
        for (int x = 0; x < frameWidth; x += checkerSize) { // width
            if ((x / checkerSize + y / checkerSize) % 2 == 0) {
                //painter.fillRect(x, y, checkerSize, checkerSize, Qt::lightGray);
            }
        }
    }

    /*
    Note: The "checkerSize" doesnt actually indicate a pixel, but rather what we define as a pixel
    if you set checerSize to 1, it will actually be pixel sized. Obviously we cant work with pixels of that size,
    so they are blown up by a factor of 10.

    Another Note: The checkered background doesn't mean that thats explicitly where workable pixels are.
    The code above pixmap.fill(Qt::Transparent) makes every pixel in the label container transparent.
    */

    qDebug() << pixmap->height();
    qDebug() << pixmap->width();

    // End painting
    painter.end();
    // Set the pixmap as the label's pixmap
    setPixmap(*pixmap);

    color = Qt::black;





    // //For loading an image on creation
    // QPixmap pixmap(":/Images/transparent.jpg");
    // // setPixmap(pixmap);
    // // setMask(pixmap.mask());
    // QColor color = Qt::black;

}
//Destructor
FrameWindow::~FrameWindow(){

}

//Paint event
void FrameWindow::paintEvent(QPaintEvent *e){
    QPainter p(this);
    //The following line will copy all actions
    //of the user on a different position of the canvas
    //p.drawPixmap(0,0,pixmap->scaled(240,240));
    p.drawPixmap(0,0,*pixmap);

}

void FrameWindow::mousePressEvent(QMouseEvent *e) {

    pressed = 1;
    draw(e);
}

void FrameWindow::mouseReleaseEvent(QMouseEvent *){pressed = 0;}

void FrameWindow::mouseMoveEvent(QMouseEvent *e) { draw(e); }

void FrameWindow::draw(QMouseEvent *e) {
    if (pressed && pencilEnabled && !eraserEnabled) {
        QPainter painter(pixmap);
        int pixelSize = 10;
        int offSet = pixelSize / 2;
        QPen defaultPen(color,pixelSize);

        painter.setPen(defaultPen);
        int x = e->pos().x();
        int y = e->pos().y();

        painter.drawPoint(x - (x % pixelSize) + offSet, y - (y % pixelSize) + offSet);
        repaint();
    }
    // eraser
    else if(pressed && !pencilEnabled && eraserEnabled) {
        QPainter painter(pixmap);
        int pixelSize = 10;
        int offSet = pixelSize / 2;
        // draw with transparent color
        //QPen defaultPen(Qt::transparent,pixelSize);

        //painter.setPen(defaultPen);
        int x = e->pos().x();
        int y = e->pos().y();

        painter.eraseRect(x - (x % pixelSize) + offSet, y - (y % pixelSize) + offSet,10 , 10);
        repaint();
    }
}

void FrameWindow::setDrawingColor(const QColor &newColor) {
    //qDebug() << newColor;
    color = newColor;
}

void FrameWindow::setBrushEnabled(){
    if(pencilEnabled){
        pencilEnabled = false;
    }else{
        pencilEnabled = true;
        eraserEnabled = false;
    }
}

void FrameWindow::setEraserEnabled(){
    if(eraserEnabled){
        eraserEnabled = false;
    }else{
        eraserEnabled = true;
        pencilEnabled = false;
    }
}
