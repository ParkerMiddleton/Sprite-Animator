#include "framewindow.h"
#include "qpixmap.h"
#include <QPainter>
#include <QDebug>
#include <QSizePolicy>
#include "mainwindow.h"
//#include "previewwindow.h"

//Constructor
FrameWindow::FrameWindow(QWidget *parent) :
    QLabel(parent), pressed(0)
{
   // connect(dynamic_cast<MainWindow*>(parent), &MainWindow::colorChanged, this, &FrameWindow::setDrawingColor);

    /*
    Known Issue: We want the label contained within the gridLayout object to match the height and width
    of its parent container. As of now, this isnt working properly. Hard coded pixmap sizes are used below,
    but we should be able to use this->height() and this->width() respectively.
    */

    int frameWidth = 750;
    int frameHeight= 500;

    pixmap = new QPixmap(frameWidth, frameHeight);

    pixmap->fill(Qt::transparent);
    // // Fill the label with an array of transparent pixels
    // pixmap = new QPixmap(frameWidth, frameHeight); // random values here are of the gridlayout's height and width

    // //Fill the map with transparent pixels
    // pixmap->fill(Qt::transparent);

    // //Tells the QPainter object that this is the object we are drawing.
    // QPainter painter (pixmap);

    // //Draw the pixels
    // int checkerSize = 10;
    // for (int y = 0; y < frameHeight; y += checkerSize) { // height
    //     for (int x = 0; x < frameWidth; x += checkerSize) { // width
    //         if ((x / checkerSize + y / checkerSize) % 2 == 0) {
    //             painter.fillRect(x, y, checkerSize, checkerSize, Qt::lightGray);
    //         }else{
    //             painter.fillRect(x, y, checkerSize, checkerSize, QColor::fromRgb(255, 255, 255,255));
    //         }
    //     }
    // }
    // // End painting
    // painter.end();

    // Set the pixmap as the label's pixmap
    setPixmap(*pixmap);

    // Set the default color
    color = Qt::black;
}
//Destructor
FrameWindow::~FrameWindow(){
    if(pixmap){
        delete pixmap;
    }
}

//Paint event
void FrameWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawPixmap(0,0,*pixmap);

    emit sendPixmapData(pixmap);

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
        int x = e->pos().x();
        int y = e->pos().y();

        QPainter painter(pixmap);
        int pixelSize = 10;
        int offSet = pixelSize / 2;
        QColor backGroundColor;

        QPen defaultPen(color,pixelSize);
        defaultPen.setColor(QColor::fromRgb(0,0,0,0));

        painter.setPen(defaultPen);



        /// Tommy's idea here, please dont delete

      //   if((x / 10) % 2 == 0){
      //       if((y/10) % 2 == 0){
      //           backGroundColor = Qt::lightGray;
      //       }
      //       else{
      //           backGroundColor = QColor::fromRgb(255, 255, 255);
      //       }
      //   }
      //   else{
      //       if((y/10) % 2 == 0){
      //           backGroundColor = QColor::fromRgb(255, 255, 255);
      //       }
      //       else{
      //           backGroundColor = Qt::lightGray;
      //       }
      //   }

      //   QPen defaultPen(backGroundColor,pixelSize);
      //   painter.setPen(defaultPen);
        // draw with transparent color
        //QPen defaultPen(Qt::transparent,pixelSize);

        //painter.setPen(defaultPen);


        painter.eraseRect(x - (x % pixelSize) + offSet, y - (y % pixelSize) + offSet,10,10);
        update();
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
