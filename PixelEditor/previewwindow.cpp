#include "previewwindow.h"

PreviewWindow::PreviewWindow(QWidget *parent)
    : QLabel{parent}
{
    // CURRENT PROBLEM: Need to decide on the side of pixmap here that is why there is a elongated appearance at the moment.
    currentPixmap = new QPixmap(256, 256);
    currentPixmap->fill(Qt::transparent);
    if (currentPixmap != nullptr)
	{
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
        p.drawPixmap(0,0,currentPixmap->scaled(250,150)); // unsure on sizing here
        update();
    }
}

void PreviewWindow::recieveSpriteData(Sprite *s){
    sprite = s;
}

void PreviewWindow::playAnimation(){

    //int fps = sprite->getFPS();

    //for(int i = 0; i < fps; i++){

    //}



}

