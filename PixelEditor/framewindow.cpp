#include "framewindow.h"
#include "qpixmap.h"
#include <QPainter>
#include <QDebug>
#include <QSizePolicy>

//Constructor
FrameWindow::FrameWindow(QWidget *parent) :
    QLabel(parent)
{

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
    QPixmap pixmap (frameWidth, frameHeight); // random values here are of the gridlayout's height and width

    //Fill the map with transparent pixels
    pixmap.fill(Qt::transparent);

    //Tells the QPainter object that this is the object we are drawing.
    QPainter painter (&pixmap);

    //Draw thie pixels
    int checkerSize = 10;
    for (int y = 0; y < frameHeight; y += checkerSize) { // height
        for (int x = 0; x < frameWidth; x += checkerSize) { // width
            if ((x / checkerSize + y / checkerSize) % 2 == 0) {
                painter.fillRect(x, y, checkerSize, checkerSize, Qt::lightGray);
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

    qDebug() << pixmap.height();
    qDebug() << pixmap.width();

    // End painting
    painter.end();
    // Set the pixmap as the label's pixmap
    setPixmap(pixmap);





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
// void FrameWindow::paintEvent(QPaintEvent *e){
//     QPainter p(this);
//     QRect rect = e->rect();
//     p.drawImage(rect, )
// }

