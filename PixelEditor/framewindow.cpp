#include "framewindow.h"
#include "qpixmap.h"
#include <QPainter>
#include <QDebug>
#include <QSizePolicy>
#include "mainwindow.h"
//#include "previewwindow.h"
#include "sprite.h"

//Constructor
FrameWindow::FrameWindow(QWidget *parent) :
    QLabel(parent), pressed(0)
{

    /*
    Known Issue: We want the label contained within the gridLayout object to match the height and width
    of its parent container. As of now, this isnt working properly. Hard coded pixmap sizes are used below,
    but we should be able to use this->height() and this->width() respectively.
    */


    int frameWidth = 750; //75
    int frameHeight= 500; //50
    sprite = new Sprite(frameWidth / 10, frameHeight / 10);

    pixmap = new QPixmap(frameWidth, frameHeight);

    pixmap->fill(Qt::transparent);

    // drawing background using sprite
    setPixmap(*pixmap);
    QPainter painter(pixmap);
    int x = 0;
    int y = 0;
    for(QColor q : sprite->getFrameImage()){
        QPen defaultPen(q,1);
        painter.setPen(defaultPen);
        painter.drawPoint(x,y);
        x++;
        if(x == (frameWidth / 10))
        {
            x = 0;
            y++;
        }
        repaint();
    }
    color = Qt::black;
}
//Destructor
FrameWindow::~FrameWindow(){
    if(pixmap){
        delete pixmap;
    }
    delete sprite;
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

void FrameWindow::drawFrame(int x, int y) {
    int xDIV = x;
    int yDIV = y;

    setPixmap(*pixmap);
    QPainter painter(pixmap);
    QList<QColor> tempList = sprite->getFrameImage();
    QPen defaultPen(tempList[xDIV + (75 * yDIV)],10);
    painter.setPen(defaultPen);
    painter.drawPoint((x * 10) - ((x * 10) % 10 + 5),y * 10 + 5);
    repaint();
}

void FrameWindow::draw(QMouseEvent *e) {
    int mouseX = e->pos().x() /10;
    int mouseY = e->pos().y() /10;

    if (pressed && pencilEnabled && !eraserEnabled) {
        sprite->setPixel(mouseX, mouseY, 10, color);
        drawFrame(mouseX, mouseY);
        //painter.drawPoint(mouseX, mouseY);
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
