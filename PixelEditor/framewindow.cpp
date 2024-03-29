#include "framewindow.h"
#include "qpixmap.h"
#include <QPainter>
#include <QDebug>
#include <QSizePolicy>
//#include "previewwindow.h"
#include "sprite.h"

//Constructor
FrameWindow::FrameWindow(QWidget *parent) :
    QLabel(parent), pressed(0)
{
    eraserEnabled = false;
    pencilEnabled = true;
    frameWidth = 750 / 10;
    frameHeight= 500 / 10;
    sprite = new Sprite(frameWidth, frameHeight);
    spriteName = "sprite_" + QString::number(sprites.size());
    sprites.insert(spriteName, sprite);

    // test loop to fill sprite
    //for (int var = 0; var < 100; ++var) {
    //sprite->setPixel(var, var, 0, Qt::blue);
    //}

    pixmap = new QPixmap(750, 500);

    pixmap->fill(Qt::transparent);

    // drawing background using sprite
    //loadFrame();
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

    // make sure this doesnt get emitted when a bool playbuttonclicked is true.
    //otherwise... horrible, undefined behavior.
    emit sendPixmapData(pixmap);


}

void FrameWindow::mousePressEvent(QMouseEvent *e) {

    pressed = 1;
    draw(e);
}

void FrameWindow::mouseReleaseEvent(QMouseEvent *){pressed = 0;}

void FrameWindow::mouseMoveEvent(QMouseEvent *e) { draw(e); }

void FrameWindow::loadFrame() {
    setPixmap(*pixmap);
    QPainter painter(pixmap);
    int x = 0;
    int y = 0;
    for(QColor q : sprite->getFrameImage()){
        // only draw pixels that are needed
        QPen defaultPen(q,10);
        int pixelSize = 10;
        int offSet = pixelSize / 2;
        painter.setPen(defaultPen);
        painter.drawPoint(x * 10 - (x * 10 % pixelSize) + 1 + offSet, y * 10 - (y * 10 % pixelSize) + offSet);
        x++;
        if(x == frameWidth)
        {
            x = 0;
            y++;
        }
    }
    repaint();
}

void FrameWindow::drawFrame(int x, int y, int spriteX, int spriteY) {
    setPixmap(*pixmap);
    QPainter painter(pixmap);
    QList<QColor> tempList = sprite->getFrameImage();
    int pixelSize = 10;
    int offSet = (pixelSize / 2);
    QPen defaultPen(tempList[spriteX + (frameWidth * spriteY)],10);
    painter.setPen(defaultPen);
    painter.drawPoint(x - (x % pixelSize) + offSet + 1, y - (y % pixelSize) + offSet);
    repaint();
}

void FrameWindow::erase(int x, int y) {
    int pixelSize = 10;
    int offSet = (pixelSize / 2);
    QColor backGroundColor = Qt::transparent;
    QPainter painter(pixmap);
    if((x / 10) % 2 == 0){
        if((y/10) % 2 == 0){
            backGroundColor = Qt::lightGray;
        }
        else{
            backGroundColor = QColor::fromRgb(255, 255, 255, 255);
        }
    }
    else{
        if((y/10) % 2 == 0){
            backGroundColor = QColor::fromRgb(255, 255, 255, 255);
        }
        else{
            backGroundColor = Qt::lightGray;
        }
    }
    QPen defaultPen(backGroundColor,10);
    painter.setPen(defaultPen);
    painter.drawPoint(x - (x % pixelSize) + offSet + 1, y - (y % pixelSize) + offSet);
    //draw with transparent color
    repaint();
}

void FrameWindow::draw(QMouseEvent *e) {
    int mouseX = e->pos().x();
    int mouseY = e->pos().y();

    int spriteX = mouseX / 10;
    int spriteY = mouseY / 10;

    if (pressed == 1 && pencilEnabled && !eraserEnabled) {
        if (mouseX >= 0 && mouseX <= frameWidth * 10 && mouseY >= 0 && mouseY <= frameHeight * 10) {
            sprite->setPixel(spriteX, spriteY, 10, color);
            drawFrame(mouseX, mouseY, spriteX, spriteY);
        }
    }
    // eraser
    else if(pressed == 1 && !pencilEnabled && eraserEnabled) {
        if (mouseX >= 0 && mouseX <= frameWidth * 10 && mouseY >= 0 && mouseY <= frameHeight * 10) {
            QColor transparent = QColor(0, 0, 0, 0);
            sprite->setPixel(spriteX, spriteY, 10, transparent);
            drawFrame(mouseX, mouseY, spriteX, spriteY);
            erase(mouseX, mouseY);
        }
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

void FrameWindow::newFrame() {
    // add new frame
    sprite->addFrame();
    // fill pix map transparent
    pixmap->fill(Qt::transparent);
    // increment frame
   // sprite->nextFrame();
    // load new frame
    loadFrame();
}

void FrameWindow::loadPreviousFrame() {
    sprite->previousFrame();
    pixmap->fill(Qt::transparent);
    loadFrame();
}

void FrameWindow::displayActiveFrame(int id){

    qDebug() << id;

    sprite->setFrameID(id);
    pixmap->fill(Qt::transparent);
    loadFrame();

}

void FrameWindow::sendSprite(){
    //playbutton clicked = true
    emit sendData(sprite);
}
