#include "previewwindow.h"
#include "QDebug"

PreviewWindow::PreviewWindow(QWidget *parent)
    : QLabel{parent}
{
    if(currentPixmap != nullptr){
        setPixmap(*currentPixmap);
    }



}

//Slot: Get data from the canvas
void PreviewWindow::recievePixmapData(QPixmap *sentPixmap){
    currentPixmap = sentPixmap;

}


//Paint event
void PreviewWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    if(currentPixmap != nullptr ){
        p.drawPixmap(0,0,currentPixmap->scaled(250,150));
        update();
    }
}

void PreviewWindow::recieveSpriteData(Sprite *s){
    sprite = s;
}

void PreviewWindow::playAnimation(){

    int fps = sprite->getFPS();

    for(int i = 0; i < fps; i++){

    }



}
