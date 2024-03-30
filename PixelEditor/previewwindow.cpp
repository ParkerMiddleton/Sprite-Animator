#include "previewwindow.h"

PreviewWindow::PreviewWindow(QWidget *parent)
    : QLabel{parent}
{
	/*if (currentPixmap != nullptr)
	{
        setPixmap(*currentPixmap);
	}*/
}

//Slot: Get data from the canvas
void PreviewWindow::recievePixmapData(QPixmap *sentPixmap){
	//currentPixmap = sentPixmap;
}


//Paint event
void PreviewWindow::paintEvent(QPaintEvent *){
	/*QPainter p(this);
    if(currentPixmap != nullptr ){
        p.drawPixmap(0,0,currentPixmap->scaled(250,150));
        update();
	}*/
}
