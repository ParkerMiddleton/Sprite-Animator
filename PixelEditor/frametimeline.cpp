#include "frametimeline.h"
#include <QDebug>

FrameTimeline::FrameTimeline(QWidget *parent)
    : QScrollArea{parent}
{

    framesInUse = new QVector<FrameIcon*>();
    qDebug() <<  parent->frameSize();
    layout= new QHBoxLayout();
    this->setLayout(layout);
    addFrame();
}


FrameTimeline::~FrameTimeline(){
    if(framesInUse){
        delete framesInUse;
    }
}


void FrameTimeline::addFrame(){

    ///Get data from backing data structure for FrameIcon ID
    ///Call setID to give it an ID that matches.
    FrameIcon *icon = new FrameIcon();
    ///icon.setID = Sprite.IDforNewFrame <---- or something
    framesInUse->push_back(icon);
    layout->addWidget(icon);


}

void FrameTimeline::removeFrame(){

    //Going to need to get the frame ID for an exisiting frame object
    // this data will come from the sprite model

    //TODO: 1) Get the id of the last frame in the sequence
    //      2) create a Frame Icon object with that same ID but use it to
    //         remove the widget using the layout->removeWidget(someIcon)

}

void FrameTimeline::moveLeft(){
    //TODO: Move an active frame over one poisiton left
    // dont move it left if it's first in the sequence
}

void FrameTimeline::moveRight(){
    //TODO: Move an active frame over one poisiton Right
    // dont move it right if it's at the end of the sequence
}

