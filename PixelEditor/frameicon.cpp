#include "frameicon.h"

FrameIcon::FrameIcon(QWidget *parent)
    : QPushButton{parent}
{
    //button attributes
    this->setFixedHeight(100);
    this->setFixedHeight(25);
}

FrameIcon::~FrameIcon(){

}

int FrameIcon::getID(){

    return frameID;
}

void FrameIcon::setID(int id){
    QString numAsString = QString::number(id);
    this->setText(numAsString);
}

